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
#include "RecordsDispatcher.h"

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
        void OnTimer1Trigger(wxTimerEvent& event);
        //*)

        void selectRow();
        void selectRowWithMouse();
        wxThread::ExitCode Entry();
        void splitOnTokens(wxString sdToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes);
        void setPercentage(pair<PercentageType, int> percentage);
        DfsMatchExitCode dfsMatch(int iToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes, wxString& currentPath, bool isSearch, bool isDir, clock_t& lastTime, long long &version, wxString& sdToken, double& time);
        DfsMatchExitCode dfsMatch2(wxString& currentPath, wxString& currentPathLower, long iLastProcessedCurrentPathChar,
                                   vector<wxString>&tokens, vector<SdTokenType>& tokensTypes,
                                   int iFirstTokenOfSlashOrSubstringSuffix, int iFirstNotMatchedToken, int& iFirstToken,
                                   bool isSearch, bool isDir,
                                   clock_t lastTime, double percentageStart, double percentageEnd, PercentageType& pType,
                                   long long& version, wxString& sdToken, double& time);

        //(*Identifiers(search_directory_tool_wxFrame)
        static const wxWindowID ID_STATICTEXTSD;
        static const wxWindowID ID_TEXTCTRLCOMMAND;
        static const wxWindowID ID_STATICTEXTPLACEHOLDER1;
        static const wxWindowID ID_STATICTEXTPATHESLABEL;
        static const wxWindowID ID_STATICTEXTALIAS;
        static const wxWindowID ID_STATICTEXTALIASPERCENTAGE;
        static const wxWindowID ID_STATICTEXTREL;
        static const wxWindowID ID_STATICTEXTRELPERCENTAGE;
        static const wxWindowID ID_STATICTEXTABS;
        static const wxWindowID ID_STATICTEXTABSPERCENTAGE;
        static const wxWindowID ID_TEXTCTRLPATHES;
        static const wxWindowID ID_TIMER1;
        //*)

        //(*Declarations(search_directory_tool_wxFrame)
        wxStaticText* StaticTextAbs;
        wxStaticText* StaticTextAbsPercentage;
        wxStaticText* StaticTextAlias;
        wxStaticText* StaticTextAliasPercentage;
        wxStaticText* StaticTextPathesLabel;
        wxStaticText* StaticTextPlaceholder1;
        wxStaticText* StaticTextRel;
        wxStaticText* StaticTextRelPercentage;
        wxStaticText* StaticTextSd;
        wxTextCtrl* TextCtrlCommand;
        wxTextCtrl* TextCtrlPathes;
        wxTimer Timer1;
        //*)

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

    public:

        DECLARE_EVENT_TABLE()
};

#endif // SEARCH_DIRECTORY_TOOL_WXMAIN_H
