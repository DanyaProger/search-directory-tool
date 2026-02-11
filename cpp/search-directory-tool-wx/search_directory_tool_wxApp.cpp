#include "search_directory_tool_wxApp.h"

//(*AppHeaders
#include "search_directory_tool_wxMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(search_directory_tool_wxApp);

bool search_directory_tool_wxApp::OnInit()
{
    defaultLocale.Init();
    if (wxApp::argc > 1)
    {
        gui = false;
        changers[TerminalChangerType::Bash] = &bashChanger;
        changers[TerminalChangerType::Cmd] = &cmdChanger;
        changers[TerminalChangerType::Explorer] = &explorerChanger;
        changers[TerminalChangerType::Far] = &farChanger;
        changers[TerminalChangerType::Powershell] = &powershellChanger;
        changers[TerminalChangerType::TotalCommander] = &totalCommanderChanger;
    }
    else
    {
        gui = true;
        //(*AppInitialize
        wxInitAllImageHandlers();
        search_directory_tool_wxFrame* Frame = new search_directory_tool_wxFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
        //*)
    }
    return true;
}

wxString prepareDirFromPath1(wxString path, bool isDir)
{
    wxString result;
    if (!isDir)
    {
        size_t pos = path.Last('\\');
        result = path.SubString(0, pos);
    } else
    {
        result = path;
        if (!path.EndsWith("\\"))
            result.Append('\\');
    }
    return result;
}

int search_directory_tool_wxApp::OnRun()
{
    if (gui)
        return wxApp::OnRun();
    else
    {
        CmdLineArgs parsed = cmdLineParser.parse(wxApp::argv.GetArguments());
        if (parsed.isFlag("help"))
        {
            HelpDialog helpDialog("sd help ru");
            helpDialog.ShowModal();
        }
        else if (parsed.isFlag("help-en"))
        {
            HelpDialog helpDialog("sd help en");
            helpDialog.ShowModal();
        }
        else if (parsed.isFlag("path"))
        {
            winApiController.addSdDirectoryToPath();
        }
        else if (parsed.isFlag("remove-path"))
        {
            winApiController.removeSdDirectoryFromPath();
        }
        else if (parsed.isFlag("fill-dirs.txt"))
        {
            winApiController.fillDirsTxt();
        }
        else if (parsed.isFlag("parent"))
        {
            DWORD pid = winApiController.getParentProcessId(GetCurrentProcessId());
            wxString fileName = winApiController.getProcessName(pid);
            ParentDialog parentDialog(pid, fileName);
            parentDialog.ShowModal();
        }
        else
        {
            TerminalChangerType cType = TerminalChangerType::None;
            bool isBack = false;
            double time = 3;
            bool isAlias = false;
            wxString dir;
            if (parsed.isFlag("back"))
            {
                isBack = true;
            }
            if (parsed.isFlag("bash"))
            {
                cType = TerminalChangerType::Bash;
            }
            if (parsed.isFlag("cmd"))
            {
                cType = TerminalChangerType::Cmd;
            }
            if (parsed.isFlag("explorer"))
            {
                cType = TerminalChangerType::Explorer;
            }
            if (parsed.isFlag("far"))
            {
                cType = TerminalChangerType::Far;
            }
            if (parsed.isFlag("powershell"))
            {
                cType = TerminalChangerType::Powershell;
            }
            if (parsed.isFlag("totalcmd"))
            {
                cType = TerminalChangerType::TotalCommander;
            }
            if (parsed.isOption("alias"))
            {
                isAlias = true;
            }
            if (parsed.isOption("time"))
            {
                wxString timeStr = parsed.getOption("time");
                wchar_t* e;
                time = wcstod(timeStr, &e);
                if (e - timeStr.c_str() != timeStr.length())
                    time = 3;
            }

            winApiController.saveForegroundWindow();
            if (cType == TerminalChangerType::None)
                cType = winApiController.getParentProcessType();
            if (cType != TerminalChangerType::None)
            {
                if (isBack)
                {
                    wxString dirsPath = wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\');
                    dirsPath.Append("\\dirs.txt");
                    RecordsDispatcher dirs(dirsPath.ToStdWstring());
                    dirs.load_dirs();
                    wstring prev_path;
                    if (dirs.get_variable(L"back", prev_path))
                    {
                        wxString cwd = wxFileName::GetCwd();
                        dirs.set_variable(L"back", cwd.ToStdWstring());
                        if (isAlias)
                        {
                            dirs.update_record_with_path_and_alias(prev_path, parsed.getOption("alias").ToStdWstring());
                        }
                        winApiController.focusForegroundWindow();
                        changers[cType]->change_directory(prev_path);
                    }
                    dirs.save_dirs();
                }
                else
                {
                    TerminalBfsSearcher searcher;
                    wxString sdToken = parsed.argsSize() == 0 ? "" : parsed.arg(0);
                    long long version = -1;
                    searcher.search(sdToken, version, time, nullptr);
                    if (searcher.isResult() && winApiController.checkForegroundWindow() && winApiController.checkParentProcess())
                    {
                        dir = prepareDirFromPath1(searcher.getResult().fullPath, searcher.getResult().isDir);
                        wxString dirsPath = wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\');
                        dirsPath.Append("\\dirs.txt");
                        RecordsDispatcher dirs(dirsPath.ToStdWstring());
                        dirs.load_dirs();
                        if (isAlias)
                        {
                            dirs.update_record_with_path_and_alias(dir.ToStdWstring(), parsed.getOption("alias").ToStdWstring());
                        }
                        dirs.set_variable(L"back", wxFileName::GetCwd().ToStdWstring());
                        dirs.save_dirs();
                        winApiController.focusForegroundWindow();
                        changers[cType]->change_directory(dir.ToStdWstring());
                    }
                }
            }
        }
        return 0;
    }
}
