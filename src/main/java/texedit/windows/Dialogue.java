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

import javax.swing.JDialog;

/**
 * An abstract dialogue window class
 */
public abstract class Dialogue extends JDialog {
    /**
     * Create the TexEdit dialogue
     */
    public Dialogue(Window parent, String name, int width, int height) {
        super(parent);

        setTitle(name);
        setSize(width, height);

        setResizable(false);
        setModal(true);
        setLocationRelativeTo(parent);

        setDefaultCloseOperation(HIDE_ON_CLOSE);

        constructGui();
    }

    /**
     * Construct the dialogue GUI
     */
    protected abstract void constructGui();
}
