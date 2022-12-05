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

package texedit.web;

import java.awt.Desktop;
import java.net.URI;

/**
 * Class for interfacing with online GitHub repository
 */
public class Repository {
    public static final String githubRepositoryLink = "https://github.com/kosude/texedit";

    /**
     * Open the GitHub repository in the default browser
     */
    public static void openGitHubRepository() {
        Desktop desktop = java.awt.Desktop.getDesktop();
        try {
            desktop.browse(new URI(githubRepositoryLink));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
