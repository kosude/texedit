import os


# -- Project information -----------------------------------------------------

project = "TexEdit Manual"
copyright = "2024 Jack Bennett"
author = "Jack Bennett"

release = os.getenv("CONFPY_VERSION")
version = release


# -- General configuration ---------------------------------------------------

extension = [
    "sphinx_design"
]

templates_path = ["templates"]
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]

master_doc = "index"


# -- Options for HTML output -------------------------------------------------

html_static_path = ["static"]

html_title = "TexEdit Manual"
html_favicon = "static/img/favicon.png"

html_theme_options = {
    "logo": "img/logo-transparent.svg",

    "description": version,

    "github_button": True,
    "github_type": "star",
    "github_repo": "texedit",
    "github_user": "kosude"
}

html_css_files = [
    "css/sidebar.css",
    "css/link-consist.css"
]
