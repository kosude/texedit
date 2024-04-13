/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

#include <wx/wx.h>

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);


class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent &ev);
    void OnExit(wxCommandEvent &ev);
    void OnAbout(wxCommandEvent &ev);
};


enum {
    ID_Hello = 1
};


bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show();
    return true;
}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello World") {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl+H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to this wxWidgets window test");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnHello(wxCommandEvent &ev) {
    wxLogMessage("Hello world from wxWidgets");
}

void MyFrame::OnExit(wxCommandEvent &ev) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &ev) {
    wxMessageBox("This is a wxWidgets hello world example", "About Hello World", wxOK | wxICON_INFORMATION);
}
