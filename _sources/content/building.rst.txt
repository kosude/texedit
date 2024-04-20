Building from source
====================


This page describes TexEdit's build process, and how you can compile it from source for your platform.


Prerequisites
-------------

TexEdit is compiled using `GNU Make <https://www.gnu.org/software/make/>`_, as well as various other build tools due to the multi-language nature of
the codebase. The total list of dependencies can be found below:

    * **GNU Make**
    * -- *When building* ``tecomp`` --
        * **Cargo** *(and a rustc installation)* - `link <https://doc.rust-lang.org/cargo/getting-started/installation.html>`__
    * -- *When building* ``texedit`` --
        * **CMake** - `link <https://cmake.org/download/>`__
        * **wxWidgets** - `link <https://docs.wxwidgets.org/latest/overview_install.html>`__
    * -- *When building* ``tepdfserver`` --
        * **Bun** - `link <https://bun.sh/docs/installation>`__
    * -- *When building* ``docs`` --
        * *Sphinx and other dependencies can be installed from pip via the* ``docs/requirements.txt`` *file provided.*

*(As always, if you're on Linux or macOS, you should install these via your package manager whenever possible.)*

Each sub-list pertains to a particular Make target, which are themselves listed in the Compilation section below. **You don't necessarily need
everything listed above!** For example, if you don't need to build the documentation, you don't need Python or pip or anything necessary for that
target. For full functionality, however, you will likely want to build at least ``tecomp``, ``texedit``, and ``tepdfserver``.


Compilation
-----------

As mentioned in the Prerequisites section, TexEdit's runtime is split up into multiple isolated binaries. Usually, you will want to have all of them
available, but you *can* build them separately if you want.

Building is done as follows:

.. code-block:: bash

    # what you'll probably want - this builds everything necessary for
    # a standard TexEdit distribution
    $ make

    # build tepdfserver on its own, for example
    $ make tepdfserver

    # build the HTML documentation - this is not done by default.
    $ make docs


``texedit``
^^^^^^^^^^^

The GUI frontend to TexEdit, and the program that should be executed for standard full functionality - it will run and manage the other programs as
necessary in the background.


``tecomp``
^^^^^^^^^^

A program to manage TeX compilation in a cross-platform way. This is run as a backend by the TexEdit application to provide a constantly updated PDF
as the source is updated, via its watch functionality. A full CLI is provided, so you can compile it on its own and use it *without* the rest of
TexEdit if you want.


``tepdfserver``
^^^^^^^^^^^^^^^

A locally hosted webserver via which a preview of a PDF can be rendered. This is run in the background by the TexEdit application to provide the
live PDF preview. Due to the way it works, this preview can be accessed from any web browser.


``docs``
^^^^^^^^

The HTML documentation you're currently reading, *not* built by the default make target.
