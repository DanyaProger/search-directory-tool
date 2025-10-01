#ifndef TERMINALDISPATCHER_H_INCLUDED
#define TERMINALDISPATCHER_H_INCLUDED

#include <string>
#include <map>
#include <windows.h>

#include "processes_helper.h"
#include "DirectoryChangers.h"

using namespace std;

extern wstring exe_path;

class TerminalDispatcher
{
private:
    TotalCommanderDirectoryChanger changer1;
    CmdDirectoryChanger changer2;
    PowerShellDirectoryChanger changer3;
    BashDirectoryChanger changer4;
    ExplorerDirectoryChanger changer5;
    map<wstring, DirectoryChanger*> parent_process_name_to_DirectoryChanger;

public:
    TerminalDispatcher()
    {
        changer1 = TotalCommanderDirectoryChanger();
        changer2 = CmdDirectoryChanger(exe_path);
        changer3 = PowerShellDirectoryChanger(exe_path);
        changer4 = BashDirectoryChanger(exe_path);
        changer5 = ExplorerDirectoryChanger(exe_path);

        parent_process_name_to_DirectoryChanger.insert(make_pair(L"TOTALCMD64.EXE", &changer1));
        parent_process_name_to_DirectoryChanger.insert(make_pair(L"cmd.exe", &changer2));
        parent_process_name_to_DirectoryChanger.insert(make_pair(L"powershell.exe", &changer3));
        parent_process_name_to_DirectoryChanger.insert(make_pair(L"bash.exe", &changer4));
        parent_process_name_to_DirectoryChanger.insert(make_pair(L"explorer.exe", &changer5));
    }

    void change_directory(wstring full_path)
    {
        wstring process_name = get_process_name(get_parent_process_id(GetCurrentProcessId()));
        DirectoryChanger* directoryChanger;
        if (parent_process_name_to_DirectoryChanger.count(process_name) != 0)
        {
            directoryChanger = parent_process_name_to_DirectoryChanger[process_name];
        }
        else
        {
            return;
        }

        directoryChanger->change_directory(full_path);
    }
};

#endif // TERMINALDISPATCHER_H_INCLUDED
