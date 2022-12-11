/* *************************************************************************************** */
/* Copyright (c) 2022 Jack Bennett                                                         */
/* --------------------------------------------------------------------------------------- */
/* THE  SOFTWARE IS  PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND, EXPRESS  OR IMPLIED, */
/* INCLUDING  BUT  NOT  LIMITED  TO  THE  WARRANTIES  OF  MERCHANTABILITY,  FITNESS FOR  A */
/* PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN  NO EVENT SHALL  THE  AUTHORS  OR COPYRIGHT */
/* HOLDERS  BE  LIABLE  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF */
/* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR */
/* THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                              */
/* *************************************************************************************** */

package texedit.pane;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;

import texedit.file.FileTree;
import texedit.file.FileTreeNode;
import texedit.file.Loader;
import texedit.windows.EditorWindow;

/**
 * Class to represent the file tree pane within a TexEdit editor window.
 */
public class FilePane extends JPanel {
    private JTree fileTree;
    private JScrollPane scrollPane;

    // button only shows when no folder is currently open
    private JButton openFolderButton;
    private Box openButtonBox;

    /**
     * Construct the file tree pane from the given root directory
     */
    public FilePane(EditorWindow editorWindow) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(300, 0));
        setMinimumSize(new Dimension(100, 0));

        // initialise the tree
        fileTree = new JTree();
        fileTree.setShowsRootHandles(true);

        // initialise parent scroll pane
        scrollPane = new JScrollPane(fileTree);

        // initialise open-folder button
        openFolderButton = new JButton("Open folder...");
        openFolderButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                Loader.loadFolder(Loader.promptFolder(editorWindow), editorWindow);
            }
        });

        updateRootFolder(null);

        // add event listener for node double-clicks
        fileTree.addMouseListener(new MouseAdapter() {
            // open the selected file if double clicked
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    FileTreeNode node = (FileTreeNode) fileTree.getLastSelectedPathComponent();

                    if (node == null) {
                        return;
                    }

                    if (node.getFile().isFile()) {
                        Loader.loadFile(node.getFile(), editorWindow);
                    }
                }
            }
        });
    }

    /**
     * Change the root dir of the file tree
     */
    public void updateRootFolder(File rootDir) {
        if (rootDir == null) {
            hide();
            return;
        }

        FileTree treeStructure = new FileTree(rootDir, new FileTreeNode(rootDir));
        fileTree.setModel(treeStructure);
        show();
    }

    /**
     * Show the file tree
     */
    public void show() {
        remove(openButtonBox);

        add(scrollPane, BorderLayout.CENTER);

        validate();
        repaint();
    }
    /**
     * Hide the file tree
     */
    public void hide() {
        remove(scrollPane);

        openFolderButton.setSize(160, 40);

        Box vBox = Box.createVerticalBox();
        openButtonBox = Box.createHorizontalBox();

        vBox.add(Box.createVerticalGlue());
        vBox.add(openFolderButton);
        vBox.add(Box.createVerticalGlue());

        openButtonBox.add(Box.createHorizontalGlue());
        openButtonBox.add(vBox);
        openButtonBox.add(Box.createHorizontalGlue());

        add(openButtonBox);

        validate();
    }
}
