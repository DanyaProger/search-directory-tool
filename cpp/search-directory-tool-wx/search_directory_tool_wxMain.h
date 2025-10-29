/***************************************************************
 * Name:      search_directory_tool_wxMain.h
 * Purpose:   Defines Application Frame
 * Author:    Danila Maiseyenkau ()
 * Created:   2025-10-13
 * Copyright: Danila Maiseyenkau ()
 * License:
 **************************************************************/

#ifndef SEARCH_DIRECTORY_TOOL_WXMAIN_H
#define SEARCH_DIRECTORY_TOOL_WXMAIN_H

//(*Headers(search_directory_tool_wxFrame)
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include <windows.h>

#include <wx/msgdlg.h>

#include "include/concurrency.h"
#include "include/cmdline.h"

enum class SdTokenType {Slash, Asterisk, SubString};
enum class DfsMatchExitCode {Success, Delete, Update};

class search_directory_tool_wxFrame: public wxFrame, public wxThreadHelper
{
    public:

        search_directory_tool_wxFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~search_directory_tool_wxFrame();

    private:

        //(*Handlers(search_directory_tool_wxFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnCommandKeyDown(wxKeyEvent& event);
        void OnPathesKeyDown(wxKeyEvent& event);
        void OnChar(wxKeyEvent& event);
        void OnCommandLeftDown(wxMouseEvent& event);
        void OnPathesLeftDown(wxMouseEvent& event);
        void OnPathesLeftUp(wxMouseEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        void OnTextCtrlCommandText(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnThreadUpdate(wxThreadEvent& event);
        void OnPathesEnter(wxCommandEvent& event);
        //*)

        void selectRow();
        void selectRowWithMouse();
        void processCommand();
        wxThread::ExitCode Entry();
        void splitOnTokens(wxString sdToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes);
        DfsMatchExitCode dfsMatch(int iToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes, wxString& currentPath, bool isSearch, bool isDir, clock_t& lastTime, long long &version, wxString& sdToken, double& time);
        //(*Identifiers(search_directory_tool_wxFrame)
        static const wxWindowID ID_STATICTEXTSD;
        static const wxWindowID ID_TEXTCTRLCOMMAND;
        static const wxWindowID ID_STATICTEXTPLACEHOLDER1;
        static const wxWindowID ID_STATICTEXTPATHESLABEL;
        static const wxWindowID ID_TEXTCTRLPATHES;
        //*)

        //(*Declarations(search_directory_tool_wxFrame)
        wxStaticText* StaticTextPathesLabel;
        wxStaticText* StaticTextPlaceholder1;
        wxStaticText* StaticTextSd;
        wxTextCtrl* TextCtrlCommand;
        wxTextCtrl* TextCtrlPathes;
        //*)

        int selectedRow = -1;
        long long exchangeVersion = -1;
        CmdLineParser cmdLineParser = CmdLineParser(vector<CmdLineFlag>(), {CmdLineOption(true, "t", true, "time")});

    public:

        DECLARE_EVENT_TABLE()
};

#endif // SEARCH_DIRECTORY_TOOL_WXMAIN_H
