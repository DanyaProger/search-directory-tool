#ifndef WINAPI_CONTROLLER_H_INCLUDED
#define WINAPI_CONTROLLER_H_INCLUDED

#include <wx/string.h>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#include "types.h"

using namespace std;

class WinApiController
{
private:
    HWND foregroundWindowHandle = NULL;
    DWORD foregroundWindowPid;
    wxString foregroundWindowFileName;
    DWORD parentPid;
    wxString parentProcessName;

public:
    DWORD getParentProcessId(DWORD pid)
    {
        HANDLE hSnapshot;
        PROCESSENTRY32 pe32;
        DWORD ppid = 0;

        hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
        if( hSnapshot == INVALID_HANDLE_VALUE ) return -1;

        ZeroMemory( &pe32, sizeof( pe32 ) );
        pe32.dwSize = sizeof( pe32 );
        if( !Process32First( hSnapshot, &pe32 ) ) return -2;

        do{
            if( pe32.th32ProcessID == pid ){
                ppid = pe32.th32ParentProcessID;
                break;
            }
        }while( Process32Next( hSnapshot, &pe32 ) );
        if( hSnapshot != INVALID_HANDLE_VALUE ) CloseHandle( hSnapshot );

        return ppid;
    }

    wxString getProcessName(DWORD pid)
    {
        HANDLE Handle = OpenProcess(
            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE,
            pid
        );
        if (Handle)
        {
            int BufferSize = 100;
            wchar_t* Buffer = new wchar_t[BufferSize];
            while (true)
            {
                Buffer[BufferSize - 1] = !NULL;
                if (!GetModuleFileNameExW(Handle, 0, Buffer, BufferSize))
                {
                    delete[] Buffer;
                    CloseHandle(Handle);
                    return "";
                }
                if (Buffer[BufferSize - 1] != (wchar_t)NULL)
                    break;
                delete[] Buffer;
                BufferSize *= 2;
                Buffer = new wchar_t[BufferSize];
            }
            wstring path(Buffer);

            delete[] Buffer;
            CloseHandle(Handle);

            return wxFileName(path).GetFullName();
        }
        return "";
    }

    void saveParentProcess()
    {
        DWORD pid = GetCurrentProcessId();
        parentPid = getParentProcessId(pid);
        parentProcessName = getProcessName(parentPid);
    }

    void saveForegroundWindow()
    {
        foregroundWindowHandle = GetForegroundWindow();
        if (foregroundWindowHandle != NULL)
        {
            GetWindowThreadProcessId(foregroundWindowHandle, &foregroundWindowPid);
            if (foregroundWindowPid == 0)
            {
                foregroundWindowHandle = NULL;
                return;
            }
            foregroundWindowFileName = getProcessName(foregroundWindowPid);
        }
    }

    TerminalChangerType getParentProcessType()
    {
        DWORD currentPid = GetCurrentProcessId();
        DWORD parentPid = getParentProcessId(currentPid);
        wxString parentName = getProcessName(parentPid);
        wxString commanderExe;
        if (wxGetEnv("COMMANDER_EXE", &commanderExe) && wxFileName(commanderExe).GetFullName().IsSameAs(parentName))
            return TerminalChangerType::TotalCommander;
        else if (parentName.IsSameAs("bash.exe"))
            return TerminalChangerType::Bash;
        else if (parentName.IsSameAs("cmd.exe"))
            return TerminalChangerType::Cmd;
        else if (parentName.IsSameAs("explorer.exe"))
            return TerminalChangerType::Explorer;
        else if (parentName.IsSameAs("Far.exe"))
            return TerminalChangerType::Far;
        else if (parentName.IsSameAs("powershell.exe"))
            return TerminalChangerType::Powershell;
        else
            return TerminalChangerType::None;
    }

    bool checkForegroundWindow()
    {
        if (foregroundWindowHandle != NULL)
        {
            DWORD pid;
            GetWindowThreadProcessId(foregroundWindowHandle, &pid);
            if (pid != 0)
            {
                wxString fileName = getProcessName(pid);
                if (pid == foregroundWindowPid && fileName == foregroundWindowFileName)
                {
                    return true;
                }
                else
                    return false;
            }
            else
            {
                return false;
            }
        }
        else
            return false;
    }

    bool checkParentProcess()
    {
        wxString processName = getProcessName(parentPid);
        if (processName == parentProcessName)
            return true;
        else
            return false;
    }

    void forceForegroundWindow(HWND hwnd) {
        /* this trick doesn't work for cmd
        DWORD windowThreadProcessId = GetWindowThreadProcessId(GetForegroundWindow(),LPDWORD(0));
        DWORD currentThreadId = GetCurrentThreadId();
        DWORD CONST_SW_SHOW = 5;
        AttachThreadInput(windowThreadProcessId, currentThreadId, true);
        BringWindowToTop(hwnd);
        ShowWindow(hwnd, CONST_SW_SHOW);
        AttachThreadInput(windowThreadProcessId,currentThreadId, false);
        */
        if (GetForegroundWindow() != foregroundWindowHandle)
        {
            SendMessageA(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            SendMessageA(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
        }
    }

    void focusForegroundWindow()
    {
        if (checkForegroundWindow())
            forceForegroundWindow(foregroundWindowHandle);
    }

    ~WinApiController()
    {
        CloseHandle(foregroundWindowHandle);
    }
};

#endif // WINAPI_CONTROLLER_H_INCLUDED
