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

import java.awt.Color;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.BevelBorder;

/**
 * Class to represent the document preview pane within a TexEdit editor window.
 */
public class PreviewPane extends JPanel {
    /**
     * Initialise the preview pane
     */
    public PreviewPane() {
        setMinimumSize(new Dimension(100, 0));
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        add(new ControlsPane());
        add(new ViewPane());
    }

    /**
     * Pane to hold the LaTeX output view
     */
    private class ViewPane extends JPanel {
        /**
         * Construct a view pane
         */
        public ViewPane() {
            setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));

            add(new JLabel("View panel"));
            setBackground(Color.YELLOW);
        }
    }

    /**
     * Pane to hold compilation and preview controls
     */
    private class ControlsPane extends JPanel {
        /**
         * Construct a controls pane
         */
        public ControlsPane() {
            setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
            setMaximumSize(new Dimension(Integer.MAX_VALUE, 500));

            add(new JLabel("Controls pane"));
            setBackground(Color.GREEN);
        }
    }
}
