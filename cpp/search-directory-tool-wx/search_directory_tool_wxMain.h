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
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
//*)

#include <regex>
#include <windows.h>

#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>
#include <wx/valtext.h>

#include "include/concurrency.h"
#include "include/cmdline.h"
#include "include/search.h"
#include "RecordsDispatcher.h"

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
        void OnTimer1Trigger(wxTimerEvent& event);
        //*)

        void selectRow();
        void selectRowWithMouse();
        wxThread::ExitCode Entry();
        void setPercentage(pair<PercentageType, int> percentage);

        //(*Identifiers(search_directory_tool_wxFrame)
        static const wxWindowID ID_STATICTEXTSD;
        static const wxWindowID ID_TEXTCTRLCOMMAND;
        static const wxWindowID ID_STATICTEXTPLACEHOLDER1;
        static const wxWindowID ID_STATICTEXTPATHESLABEL;
        static const wxWindowID ID_TEXTCTRLPATHES;
        static const wxWindowID ID_TIMER1;
        static const wxWindowID ID_STATUSBAR1;
        //*)

        //(*Declarations(search_directory_tool_wxFrame)
        wxStaticText* StaticTextPathesLabel;
        wxStaticText* StaticTextPlaceholder1;
        wxStaticText* StaticTextSd;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlCommand;
        wxTextCtrl* TextCtrlPathes;
        wxTimer Timer1;
        //*)

        int MATCH_MISS = 0, MATCH_SUCCEED = 1, MATCH_POSSIBLE = 2;
        int selectedRow = -1;
        long long exchangeVersion = -1;
        long long messagesCount = 0;
        long long threadUpdatesCount = 0;
        long MAX_PATHES_COUNT = 147;
        long pathesCount = 0;
        wxString exePath = wxStandardPaths::Get().GetExecutablePath();
        bool isFirstInPathes = true;
        CmdLineParser cmdLineParser = CmdLineParser(vector<CmdLineFlag>(), {CmdLineOption(true, "t", true, "time")});
        int aliasPercentage, relativePercentage, absolutePercentage;
        clock_t findFileDuration = 0;

    public:

        DECLARE_EVENT_TABLE()
};

#endif // SEARCH_DIRECTORY_TOOL_WXMAIN_H
