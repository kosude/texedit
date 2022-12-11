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

package texedit.file;

import java.io.File;
import java.util.Arrays;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

/**
 * File tree structure class
 */
public class FileTree extends DefaultTreeModel {
    private FileTreeNode rootNode;
    private File root;

    /**
     * Populate the file tree with the given root path
     */
    public FileTree(File root, FileTreeNode rootNode) {
        super(rootNode);

        this.root = root;
        this.rootNode = rootNode;

        populate(this.root, this.rootNode);
    }

    /**
     * Recursively populate the given node with the given file root
     */
    private void populate(File file, DefaultMutableTreeNode node) {
        if (file.isHidden() || !file.canRead() || !file.canWrite()) {
            return;
        }

        File[] files = file.listFiles();
        Arrays.sort(files);

        if (files == null) {
            return;
        }

        for (File f : files) {
            DefaultMutableTreeNode child = new FileTreeNode(f);

            if (!f.isHidden()) {
                node.add(child);
            }

            if (f.isDirectory()) {
                populate(f, child);
            }
        }
    }
}
