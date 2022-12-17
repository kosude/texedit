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

package texedit.windows;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.io.File;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JSplitPane;

import texedit.file.Loader;
import texedit.pane.EditorPane;
import texedit.pane.FilePane;
import texedit.pane.PreviewPane;
import texedit.pane.StatusBar;
import texedit.web.Repository;

/**
 * A basic TexEdit window class
 */
public class EditorWindow extends Window {
    private StatusBar statusBar;
    private MenuBar menuBar;

    private FilePane filePane;
    private EditorPane editorPane;
    private PreviewPane previewPane;

    private File currentFile, currentFolder;

    /**
     * Create a TexEdit editor window
     */
    public EditorWindow() {
        super("TexEdit", 1280, 760);

        statusBar = new StatusBar();
        menuBar = new MenuBar();

        filePane = new FilePane(this);
        editorPane = new EditorPane();
        previewPane = new PreviewPane();

        setCurrentFile(null);
        setCurrentFolder(null);

        setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        constructGui();
    }

    @Override
    protected void constructGui() {
        // set menu bar
        setJMenuBar(menuBar);

        // set status bar
        add(statusBar, BorderLayout.SOUTH);

        // construct panes

        // parent SplitPane (file tree + editor/preview)
        JSplitPane parentPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        parentPane.setContinuousLayout(true);
        parentPane.setOneTouchExpandable(true);

        parentPane.setLeftComponent(filePane);

        // child SplitPane (editor + preview)
        JSplitPane childPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        childPane.setContinuousLayout(true);
        childPane.setResizeWeight(0.5);

        childPane.setLeftComponent(editorPane);
        childPane.setRightComponent(previewPane);

        parentPane.setRightComponent(childPane);

        add(parentPane);
    }

    @Override
    public void windowClosed(WindowEvent arg0) {
        dispose();
        System.exit(0);

        super.windowClosed(arg0);
    }

    public StatusBar getStatusBar() {
        return statusBar;
    }
    public FilePane getFilePane() {
        return filePane;
    }
    public EditorPane getEditorPane() {
        return editorPane;
    }
    public PreviewPane getPreviewPane() {
        return previewPane;
    }

    /**
     * Set the current file and update any GUI elements to reflect it
     */
    public void setCurrentFile(File val) {
        currentFile = val;

        updateTitle();

        if (val != null) {
            statusBar.setStatus(val.getAbsolutePath());
            menuBar.closeFileMenuItem.setEnabled(true);
        } else {
            statusBar.setStatus("Ready");
            menuBar.closeFileMenuItem.setEnabled(false);
        }
    }
    /**
     * Set the current folder and update any GUI elements to reflect it
     */
    public void setCurrentFolder(File val) {
        currentFolder = val;
        updateTitle();

        if (val != null) {
            menuBar.closeFolderMenuItem.setEnabled(true);
        } else {
            menuBar.closeFolderMenuItem.setEnabled(false);
        }
    }

    /**
     * Update the title to contain the current file and folder names
     */
    private void updateTitle() {
        String buffer = "";

        if (currentFile != null) {
            buffer += currentFile.getName() + " - ";
        }
        if (currentFolder != null) {
            buffer += currentFolder.getName() + " - ";
        }
        buffer += "TexEdit";

        setTitle(buffer);
    }

    /**
     * The menu bar of the editor window
     */
    private class MenuBar extends JMenuBar {
        public final JMenu fileMenu;
        public final JMenu helpMenu;

        private final MenuItemListener menuItemListener;

        // menu items within the File section
        public JMenuItem
            openFileMenuItem,
            openFolderMenuItem,
            closeFileMenuItem,
            closeFolderMenuItem,
            quitMenuItem;

        // menu items within the Help section
        public JMenuItem
            repoMenuItem,
            aboutMenuItem;

        /**
         * Construct the menu bar
         */
        public MenuBar() {
            fileMenu = new JMenu("File");
            helpMenu = new JMenu("Help");
            menuItemListener = new MenuItemListener();

            //
            // [file] menu items
            //

            // open file...
            openFileMenuItem = new JMenuItem("Open file...");
            openFileMenuItem.setActionCommand("open-file");
            openFileMenuItem.addActionListener(menuItemListener);
            fileMenu.add(openFileMenuItem);

            // open folder...
            openFolderMenuItem = new JMenuItem("Open folder...");
            openFolderMenuItem.setActionCommand("open-folder");
            openFolderMenuItem.addActionListener(menuItemListener);
            fileMenu.add(openFolderMenuItem);

            fileMenu.addSeparator();

            // close current file
            closeFileMenuItem = new JMenuItem("Close current file");
            closeFileMenuItem.setActionCommand("close-file");
            closeFileMenuItem.addActionListener(menuItemListener);
            fileMenu.add(closeFileMenuItem);

            // close current folder
            closeFolderMenuItem = new JMenuItem("Close current folder");
            closeFolderMenuItem.setActionCommand("close-folder");
            closeFolderMenuItem.addActionListener(menuItemListener);
            fileMenu.add(closeFolderMenuItem);

            fileMenu.addSeparator();

            // quit
            quitMenuItem = new JMenuItem("Quit");
            quitMenuItem.setActionCommand("quit");
            quitMenuItem.addActionListener(menuItemListener);
            fileMenu.add(quitMenuItem);

            //
            // [help] menu items
            //

            // git repository...
            repoMenuItem = new JMenuItem("Git repository...");
            repoMenuItem.setActionCommand("open-repo");
            repoMenuItem.addActionListener(menuItemListener);
            helpMenu.add(repoMenuItem);

            helpMenu.addSeparator();

            // about texedit...
            aboutMenuItem = new JMenuItem("About TexEdit...");
            aboutMenuItem.setActionCommand("about");
            aboutMenuItem.addActionListener(menuItemListener);
            helpMenu.add(aboutMenuItem);

            add(fileMenu);
            add(helpMenu);
        }

        /**
         * Class to handle menu item events
         */
        private class MenuItemListener implements ActionListener {
            public void actionPerformed(ActionEvent e) {
                switch (e.getActionCommand()) {
                    // FILE MENU

                    case "open-file":
                        Loader.loadFile(Loader.promptFile(EditorWindow.this), EditorWindow.this);

                        return;
                    case "open-folder":
                        Loader.loadFolder(Loader.promptFolder(EditorWindow.this), EditorWindow.this);

                        return;
                    case "close-file":
                        Loader.loadFile(null, EditorWindow.this);
                        setCurrentFile(null);

                        return;
                    case "close-folder":
                        Loader.loadFile(null, EditorWindow.this);
                        filePane.updateRootFolder(null);

                        setCurrentFile(null);
                        setCurrentFolder(null);

                        return;
                    case "quit":
                        // dispatch event to parent editor window to be closed
                        EditorWindow.this.dispatchEvent(
                            new WindowEvent(EditorWindow.this, WindowEvent.WINDOW_CLOSING)
                        );

                        return;

                    // HELP MENU

                    case "about":
                        new AboutDialogue(EditorWindow.this).setVisible(true);

                        return;
                    case "open-repo":
                        Repository.openGitHubRepository();

                        return;

                    default:
                        System.out.println(String.format("Invalid menu item action command \"%s\"", e.getActionCommand()));

                        return;
                }
            }
        }
    }
}
