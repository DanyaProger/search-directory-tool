#ifndef SEARCH_DIRECTORY_TOOL_WXPARENT_H_INCLUDED
#define SEARCH_DIRECTORY_TOOL_WXPARENT_H_INCLUDED

#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/event.h>

#include <string>

using namespace std;

class ParentDialog : public wxDialog
{
private:
    wxTextCtrl* TextCtrlText;
    bool closed = false;

    void OnClose(wxCloseEvent& event)
    {
        Close();
    }

public:
    ParentDialog(DWORD pid, wxString fileName): wxDialog(NULL, -1, L"sd parent process info", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, wxDialogNameStr)
    {
        wxBoxSizer* BoxSizer;
        BoxSizer = new wxBoxSizer(wxVERTICAL);

        TextCtrlText = new wxTextCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxSize(300, -1), wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL, wxDefaultValidator, _T("ID_TEXTCTRLTEXT1"));
        wxFont TextCtrlTextFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
        TextCtrlText->SetFont(TextCtrlTextFont);

        TextCtrlText->AppendText("pid=" + to_string(pid) + " filename=" + fileName);

        BoxSizer->Add(TextCtrlText, 1, wxEXPAND, 0);

        Bind(wxEVT_CLOSE_WINDOW, &ParentDialog::OnClose, this);

        SetSizerAndFit(BoxSizer);
    }

    void Close()
    {
        closed = true;
        if (IsModal())
            EndModal(wxOK);
        else
            Hide();
    }

    bool isClosed()
    {
        return closed;
    }
};

#endif // SEARCH_DIRECTORY_TOOL_WXPARENT_H_INCLUDED
