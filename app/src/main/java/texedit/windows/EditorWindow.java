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

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;

/**
 * A basic TexEdit window class
 */
public class EditorWindow extends Window {
    MenuBar menuBar;

    /**
     * Create a TexEdit editor window
     */
    public EditorWindow() {
        super("TexEdit", 1280, 760);

        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    @Override
    protected void constructGui() {
        // set menu bar
        setJMenuBar(new MenuBar());
    }

    @Override
    public void windowClosed(WindowEvent arg0) {
        dispose();
        System.exit(0);

        super.windowClosed(arg0);
    }

    /**
     * The menu bar of the editor window
     */
    private class MenuBar extends JMenuBar {
        public final JMenu fileMenu;
        public final JMenu helpMenu;

        private final MenuItemListener menuItemListener;

        /**
         * Construct the menu bar
         */
        public MenuBar() {
            fileMenu = new JMenu("File");
            helpMenu = new JMenu("Help");
            menuItemListener = new MenuItemListener();

            // [file] menu items

            JMenuItem quitMenuItem = new JMenuItem("Quit");
            quitMenuItem.setActionCommand("quit");
            quitMenuItem.addActionListener(menuItemListener);
            fileMenu.add(quitMenuItem);

            add(fileMenu);
            add(helpMenu);
        }

        /**
         * Class to handle menu item events
         */
        private class MenuItemListener implements ActionListener {
            public void actionPerformed(ActionEvent e) {
                switch (e.getActionCommand()) {
                    case "quit":
                        // dispatch event to parent editor window to be closed
                        EditorWindow.this.dispatchEvent(
                            new WindowEvent(EditorWindow.this, WindowEvent.WINDOW_CLOSING)
                        );

                        return;

                    default:
                        System.out.println(String.format("Invalid menu item action command \"%s\"", e.getActionCommand()));

                        return;
                }
            }
        }
    }
}
