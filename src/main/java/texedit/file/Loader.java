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
import java.util.Scanner;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import texedit.windows.EditorWindow;
import texedit.windows.Window;

/**
 * A class to handle file saving and loading
 */
public class Loader {
    /**
     * Prompt the user to choose a file
     */
    public static File promptFile(Window parent) {
        JFileChooser chooser = new JFileChooser();

        chooser.setDialogTitle("Open file...");
        chooser.addChoosableFileFilter(new FileNameExtensionFilter("TeX Source Files", "tex"));
        chooser.setAcceptAllFileFilterUsed(true);

        File file;

        if (chooser.showOpenDialog(parent) == JFileChooser.APPROVE_OPTION) {
            file = chooser.getSelectedFile();
        } else {
            file = null;
        }

        return file;
    }
    /**
     * Prompt the user to open a folder
     */
    public static File promptFolder(Window parent) {
        JFileChooser chooser = new JFileChooser();

        chooser.setDialogTitle("Open folder...");
        chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

        File file;

        if (chooser.showOpenDialog(parent) == JFileChooser.APPROVE_OPTION) {
            file = chooser.getSelectedFile();
        } else {
            file = null;
        }

        return file;
    }

    /**
     * Read the contents of the given file and return the results
     */
    public static String readFile(File file) {
        String str = "";

        try {
            Scanner reader = new Scanner(file);

            while (reader.hasNextLine()) {
                str += reader.nextLine() + System.lineSeparator();
            }

            reader.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        return str;
    }

    /**
     * Load the given file into an editor window
     */
    public static void loadFile(File file, EditorWindow editor) {
        if (file == null) {
            editor.getEditorPane().editor.setText("");;
            return;
        }

        String contents = Loader.readFile(file);
        editor.getEditorPane().editor.setText(contents);
        editor.getEditorPane().editor.setCaretPosition(0);

        editor.setCurrentFile(file);
    }

    /**
     * Load the given folder into an editor window
     */
    public static void loadFolder(File dir, EditorWindow editor) {
        if (dir == null) {
            return;
        }

        editor.getFilePane().updateRootFolder(dir);

        // set status and title
        editor.setCurrentFolder(dir);
    }
}
