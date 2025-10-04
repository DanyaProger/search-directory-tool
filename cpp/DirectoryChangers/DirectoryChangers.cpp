#include <windows.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#include "DirectoryChangers.h"

using namespace std;

void DirectoryChanger::change_directory(wstring path) {
}

TerminalDirectoryChanger::TerminalDirectoryChanger(int delay)
{
    this->delay = delay;
}

TerminalDirectoryChanger::TerminalDirectoryChanger(wstring exe_path, int delay)
    :TerminalDirectoryChanger(delay)
{
    this->exe_path = exe_path;
}

int TerminalDirectoryChanger::get_delay()
{
    return this->delay;
}

wstring TerminalDirectoryChanger::path_to_cd_command(wstring path){}

void TerminalDirectoryChanger::change_directory(wstring path)
{
    DWORD pid = GetCurrentProcessId();
    filesystem::path EXE_DIR = filesystem::path(exe_path).parent_path();

    PROCESS_INFORMATION processInformation;
    STARTUPINFOW info = {sizeof(info)};

    wstring command = path_to_cd_command(path);
    wstring prepared_command;
    for (int i = 0; i < command.size(); i++)
        if (command[i] != L'\"')
            prepared_command.push_back(command[i]);
        else
        {
            prepared_command.push_back(L'\\');
            prepared_command.push_back(L'\"');
        }
    prepared_command = L"\"" + prepared_command + L"\"";
    if (prepared_command[prepared_command.size() - 2] == L'\\')
    {
        prepared_command[prepared_command.size() - 2] = L'\"';
        prepared_command[prepared_command.size() - 1] = L'\\';
    }

    wstring commandLine = to_wstring(pid) + L" -d " + to_wstring(get_delay()) + L" -t " + prepared_command + L" -kd " + to_wstring(VK_RETURN) + L" -ku " + to_wstring(VK_RETURN);
    wstring terminal_sender = (EXE_DIR/L"terminal-sender"/L"terminal-sender.exe").wstring();
    commandLine = terminal_sender + L" " + commandLine;
    CreateProcessW(terminal_sender.c_str(), const_cast<wchar_t*>(commandLine.c_str()), NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &info, &processInformation);
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);
}


CmdDirectoryChanger::CmdDirectoryChanger() : TerminalDirectoryChanger(0){}
CmdDirectoryChanger::CmdDirectoryChanger(wstring exe_path) : TerminalDirectoryChanger(exe_path, 0){}

wstring CmdDirectoryChanger::path_to_cd_command(wstring path)
{
    if (towlower(filesystem::current_path().wstring()[0]) == towlower(path[0]))
    {
        return L"cd " + path;
    }
    else
    {
        return L"cd /D " + path;
    }
}


PowerShellDirectoryChanger::PowerShellDirectoryChanger() : TerminalDirectoryChanger(0){}
PowerShellDirectoryChanger::PowerShellDirectoryChanger(wstring exe_path) : TerminalDirectoryChanger(exe_path, 0){}

wstring PowerShellDirectoryChanger::path_to_cd_command(wstring path)
{
    return L"cd \"" + path + L"\"";
}

BashDirectoryChanger::BashDirectoryChanger() : TerminalDirectoryChanger(200) {}
BashDirectoryChanger::BashDirectoryChanger(wstring exe_path) : TerminalDirectoryChanger(exe_path, 200) {}

wstring BashDirectoryChanger::path_to_cd_command(wstring path)
{
    return L"cd \'" + path + L"\'";
}


TotalCommanderDirectoryChanger::TotalCommanderDirectoryChanger() : TerminalDirectoryChanger(0) {}

wstring TotalCommanderDirectoryChanger::path_to_cd_command(wstring path)
{
    return L"cd \"" + path + L"\"";
}

void TotalCommanderDirectoryChanger::change_directory(wstring path)
{
    wstring COMMANDER_EXE = _wgetenv(L"COMMANDER_EXE");

    PROCESS_INFORMATION processInformation;
    STARTUPINFOW info = {sizeof(info)};
    wstring commandLine = COMMANDER_EXE + L" /S /O \"" + path + L"\"";
    CreateProcessW(COMMANDER_EXE.c_str(), const_cast<wchar_t*>(commandLine.c_str()), NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &info, &processInformation);

    WaitForSingleObject(processInformation.hProcess, 100000);
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);
}

ExplorerDirectoryChanger::ExplorerDirectoryChanger() : TerminalDirectoryChanger(0) {}

ExplorerDirectoryChanger::ExplorerDirectoryChanger(wstring exe_path) : TerminalDirectoryChanger(exe_path, 0) {}

wstring ExplorerDirectoryChanger::path_to_cd_command(wstring path)
{
    return path;
}

void ExplorerDirectoryChanger::change_directory(wstring path)
{
    DWORD pid = GetCurrentProcessId();
    filesystem::path EXE_DIR = filesystem::path(exe_path).parent_path();

    PROCESS_INFORMATION processInformation;
    STARTUPINFOW info = {sizeof(info)};

    wstring command = path_to_cd_command(path);
    wstring prepared_command;
    for (int i = 0; i < command.size(); i++)
        if (command[i] != L'\"')
            prepared_command.push_back(command[i]);
        else
        {
            prepared_command.push_back(L'\\');
            prepared_command.push_back(L'\"');
        }
    prepared_command = L"\"" + prepared_command + L"\"";
    if (prepared_command[prepared_command.size() - 2] == L'\\')
    {
        prepared_command[prepared_command.size() - 2] = L'\"';
        prepared_command[prepared_command.size() - 1] = L'\\';
    }

    wstring commandLine = to_wstring(pid) + L" -d " + to_wstring(get_delay())
                         + L" -kd " + to_wstring(VK_CONTROL) + L" -kd " + to_wstring(int('A')) + L" -ku " + to_wstring(VK_CONTROL) + L" -ku " + to_wstring(int('A'))
                         + L" -t " + prepared_command + L" -kd " + to_wstring(VK_RETURN) + L" -ku " + to_wstring(VK_RETURN);
    wstring terminal_sender = (EXE_DIR/L"terminal-sender"/L"terminal-sender.exe").wstring();
    commandLine = terminal_sender + L" " + commandLine;
    CreateProcessW(terminal_sender.c_str(), const_cast<wchar_t*>(commandLine.c_str()), NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &info, &processInformation);
    CloseHandle(processInformation.hProcess);
    CloseHandle(processInformation.hThread);
}

FarDirectoryChanger::FarDirectoryChanger() : TerminalDirectoryChanger(0){}
FarDirectoryChanger::FarDirectoryChanger(wstring exe_path) : TerminalDirectoryChanger(exe_path, 0){}

wstring FarDirectoryChanger::path_to_cd_command(wstring path)
{
    return L"cd " + path;
}
