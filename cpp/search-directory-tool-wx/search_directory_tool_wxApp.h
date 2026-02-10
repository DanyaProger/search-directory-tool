/***************************************************************
 * Name:      search_directory_tool_wxApp.h
 * Purpose:   Defines Application Class
 * Author:    Danila Maiseyenkau ()
 * Created:   2025-10-13
 * Copyright: Danila Maiseyenkau ()
 * License:
 **************************************************************/

#ifndef SEARCH_DIRECTORY_TOOL_WXAPP_H
#define SEARCH_DIRECTORY_TOOL_WXAPP_H

#include <locale>

#include <wx/app.h>

#include "include/search.h"
#include "include/cmdline.h"
#include "include/winapi_controller.h"
#include "DirectoryChangers.h"
#include "RecordsDispatcher.h"

class search_directory_tool_wxApp : public wxApp
{
    public:
        virtual bool OnInit();
        virtual int OnRun();
        wxLocale defaultLocale;
        bool gui;
        CmdLineParser cmdLineParser = CmdLineParser({CmdLineFlag(false, "", true, "path"),
                                     CmdLineFlag(false, "", true, "remove-path"),
                                     CmdLineFlag(false, "", true, "fill-dirs.txt"),
                                     CmdLineFlag(false, "", true, "parent"),
                                     CmdLineFlag(true, "b", true, "bash"),
                                     CmdLineFlag(true, "c", true, "cmd"),
                                     CmdLineFlag(true, "e", true, "explorer"),
                                     CmdLineFlag(true, "f", true, "far"),
                                     CmdLineFlag(true, "p", true, "powershell"),
                                     CmdLineFlag(true, "t", true, "totalcmd"),
                                     CmdLineFlag(true, "h", true, "help"),
                                     CmdLineFlag(false, "", true, "back")},
                                    {CmdLineOption(false, "", true, "alias"),
                                     CmdLineOption(false, "", true, "time")});
        map<TerminalChangerType, TerminalDirectoryChanger*> changers;
        BashDirectoryChanger bashChanger = BashDirectoryChanger(wxStandardPaths::Get().GetExecutablePath().ToStdWstring());
        CmdDirectoryChanger cmdChanger = CmdDirectoryChanger(wxStandardPaths::Get().GetExecutablePath().ToStdWstring());
        ExplorerDirectoryChanger explorerChanger = ExplorerDirectoryChanger(wxStandardPaths::Get().GetExecutablePath().ToStdWstring(), false);
        FarDirectoryChanger farChanger = FarDirectoryChanger(wxStandardPaths::Get().GetExecutablePath().ToStdWstring());
        PowerShellDirectoryChanger powershellChanger = PowerShellDirectoryChanger(wxStandardPaths::Get().GetExecutablePath().ToStdWstring());
        TotalCommanderDirectoryChanger totalCommanderChanger;

        WinApiController winApiController;
};

DECLARE_APP(search_directory_tool_wxApp)

#endif // SEARCH_DIRECTORY_TOOL_WXAPP_H
