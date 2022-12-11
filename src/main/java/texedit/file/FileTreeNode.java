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

import javax.swing.tree.DefaultMutableTreeNode;

/**
 * Node in a file tree structure
 */
public class FileTreeNode extends DefaultMutableTreeNode {
    private File file;

    /**
     * Construct the node
     */
    public FileTreeNode(File file) {
        this.file = file;
    }

    /**
     * Get the contained file
     */
    public File getFile() {
        return file;
    }

    @Override
    public String toString() {
        String name = file.getName();

        if (name == "") {
            return file.getAbsolutePath();
        } else {
            return name;
        }
    }
}
