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

import java.awt.Font;

import javax.swing.Box;
import javax.swing.JLabel;
import javax.swing.border.EmptyBorder;

/**
 * An about dialogue window
 */
public class AboutDialogue extends Dialogue {
    /**
     * Create a TexEdit editor window
     */
    public AboutDialogue(Window parent) {
        super(parent, "About TexEdit", 280, 360);
    }

    @Override
    protected void constructGui() {
        Box vBox = Box.createVerticalBox();

        // spacing
        vBox.add(Box.createVerticalGlue());

        // Application name and description

        JLabel programName = new JLabel("TexEdit", JLabel.CENTER);
        programName.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        programName.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 25));
        programName.setBorder(new EmptyBorder(0, 0, 7, 0));
        vBox.add(programName);

        JLabel programBrief = new JLabel("<html><body style='text-align: center'>Integrated editor and viewer for<br>LaTeX documents", JLabel.CENTER);
        programBrief.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        programBrief.setFont(new Font(Font.SANS_SERIF, Font.BOLD | Font.ITALIC, 12));
        vBox.add(programBrief);

        // spacing
        vBox.add(Box.createVerticalGlue());

        // Copyright and non-affiliation notice

        JLabel copyright = new JLabel("(c) 2022 Jack Bennett", JLabel.CENTER);
        copyright.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        copyright.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 11));
        vBox.add(copyright);

        JLabel affiliation = new JLabel("Not affiliated with the LaTeX project", JLabel.CENTER);
        affiliation.setAlignmentX(JLabel.CENTER_ALIGNMENT);
        affiliation.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 11));
        vBox.add(affiliation);

        // spacing
        vBox.add(Box.createVerticalGlue());

        add(vBox);
    }
}
