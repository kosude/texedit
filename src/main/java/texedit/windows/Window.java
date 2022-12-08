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

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JFrame;

/**
 * An abstract TexEdit window class
 */
public abstract class Window extends JFrame implements WindowListener {
    /**
     * Create the TexEdit window
     */
    public Window(String name, int width, int height) {
        setTitle(name);
        setSize(width, height);
    }

    /**
     * Construct the window GUI
     */
    protected abstract void constructGui();

    @Override
    public void windowActivated(WindowEvent arg0) {
    }
    @Override
    public void windowClosed(WindowEvent arg0) {
    }
    @Override
    public void windowClosing(WindowEvent arg0) {
    }
    @Override
    public void windowDeactivated(WindowEvent arg0) {
    }
    @Override
    public void windowDeiconified(WindowEvent arg0) {
    }
    @Override
    public void windowIconified(WindowEvent arg0) {
    }
    @Override
    public void windowOpened(WindowEvent arg0) {
    }
}
