#ifndef WINAPI_CONTROLLER_H_INCLUDED
#define WINAPI_CONTROLLER_H_INCLUDED

#include <wx/string.h>
#include <wx/stdpaths.h>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#include "types.h"
#include "RecordsDispatcher.h"
#include "InputSimulator.h"

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
        wxString parentName = getProcessName(parentPid).Lower();
        wxString commanderExe;
        if (wxGetEnv("COMMANDER_EXE", &commanderExe) && wxFileName(commanderExe).GetFullName().Lower().IsSameAs(parentName))
            return TerminalChangerType::TotalCommander;
        else if (parentName.IsSameAs("bash.exe"))
            return TerminalChangerType::Bash;
        else if (parentName.IsSameAs("cmd.exe"))
            return TerminalChangerType::Cmd;
        else if (parentName.IsSameAs("explorer.exe"))
            return TerminalChangerType::Explorer;
        else if (parentName.IsSameAs("far.exe"))
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

        /*
        this trick always minimize target window
        if (GetForegroundWindow() != foregroundWindowHandle)
        {
            SendMessageA(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            SendMessageA(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
        }*/

        SetForegroundWindowEx(hwnd);
    }

    void focusForegroundWindow()
    {
        if (checkForegroundWindow())
            forceForegroundWindow(foregroundWindowHandle);
    }

    wstring getPathVariableInRegistry(DWORD& path_type)
    {
        HKEY hKey;
        RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_ALL_ACCESS, &hKey);
        BYTE* buffer;
        DWORD bufferSize = 0;
        buffer = new BYTE[bufferSize];

        LSTATUS status = RegQueryValueExA(hKey, "Path", NULL, &path_type, buffer, &bufferSize);
        if (status == ERROR_SUCCESS)
        {

        }
        else if (status != ERROR_MORE_DATA)
        {
            RegCloseKey(hKey);
            exit(0);
        }
        else
        {
            delete[] buffer;
            buffer = new BYTE[bufferSize];
            RegQueryValueExA(hKey, "Path", NULL, &path_type, buffer, &bufferSize);
        }
        RegCloseKey(hKey);

        int str_size = MultiByteToWideChar(CP_ACP, 0, (char*)buffer, bufferSize, NULL, 0);
        wchar_t* str = new wchar_t[str_size];
        MultiByteToWideChar(CP_ACP, 0, (char*)buffer, bufferSize, str, str_size);

        wstring path(str, str_size);
        delete[] buffer;
        delete[] str;
        return path;
    }

    void setPathVariableInRegistry(wstring value, DWORD path_type)
    {
        int buffer_size = WideCharToMultiByte(CP_ACP, 0, value.c_str(), value.size(), NULL, 0 , NULL, NULL);
        BYTE* buffer = new BYTE[buffer_size + 2];
        WideCharToMultiByte(CP_ACP, 0, value.c_str(), value.size(), (char*)buffer, buffer_size, NULL, NULL);

        HKEY hKey;
        RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_ALL_ACCESS, &hKey);

        RegSetValueExA(hKey, "Path", 0, path_type, buffer, buffer_size);

        RegCloseKey(hKey);

        delete[] buffer;
    }

    void addSdDirectoryToPath()
    {
        wstring sd_dir = filesystem::path(wxStandardPaths::Get().GetExecutablePath().ToStdWstring()).parent_path().wstring();

        DWORD path_type;
        wstring path = getPathVariableInRegistry(path_type);

        size_t path_size = path.size();
        while (path_size > 1 && path[path_size - 1] == L'\0')
            path_size--;

        vector<wstring> dirs;
        size_t pos = 0, new_pos;
        while ((new_pos = path.find(L";", pos)) != wstring::npos)
        {
            dirs.push_back(path.substr(pos, new_pos - pos));
            pos = new_pos + 1;
        }
        if (pos < path_size)
            dirs.push_back(path.substr(pos));

        bool sd_dir_in_path = false;
        for (size_t i = 0; i < dirs.size(); i++)
        {
            if (filesystem::exists(dirs[i]) && filesystem::exists(sd_dir) && filesystem::equivalent(filesystem::path(dirs[i]), filesystem::path(sd_dir)))
            {
                sd_dir_in_path = true;
                break;
            }
        }

        if (!sd_dir_in_path)
        {
            wstring new_path = path.substr(0, path_size);
            if (new_path[new_path.size() - 1] != L';')
            {
                new_path.push_back(L';');
            }
            new_path = new_path + sd_dir + L';';
            new_path += path.substr(path_size);
            setPathVariableInRegistry(new_path, path_type);

            DWORD_PTR nResult;
            SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_BLOCK, 1500, &nResult);
        }
    }

    void removeSdDirectoryFromPath()
    {
        wstring sd_dir = filesystem::path(wxStandardPaths::Get().GetExecutablePath().ToStdWstring()).parent_path().wstring();

        DWORD path_type;
        wstring path = getPathVariableInRegistry(path_type);
        size_t path_size = path.size();
        while (path_size > 1 && path[path_size - 1] == L'\0')
            path_size--;

        vector<wstring> dirs;
        size_t pos = 0, new_pos;
        while ((new_pos = path.find(L";", pos)) != wstring::npos)
        {
            dirs.push_back(path.substr(pos, new_pos - pos));
            pos = new_pos + 1;
        }
        if (pos < path_size)
            dirs.push_back(path.substr(pos));

        size_t sd_dir_index_in_path;
        bool sd_dir_in_path = false;
        for (size_t i = 0; i < dirs.size(); i++)
        {
            if (filesystem::exists(dirs[i]) && filesystem::exists(sd_dir) && filesystem::equivalent(filesystem::path(dirs[i]), filesystem::path(sd_dir)))
            {
                sd_dir_index_in_path = i;
                sd_dir_in_path = true;
                break;
            }
        }
        if (sd_dir_in_path)
        {
            wstring new_path;
            for (size_t i = 0; i < dirs.size(); i++)
                if (i != sd_dir_index_in_path)
                    new_path += dirs[i] + L';';
            new_path += path.substr(path_size);

            setPathVariableInRegistry(new_path, path_type);

            DWORD_PTR nResult;
            SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_BLOCK, 1500, &nResult);
        }
    }

    ~WinApiController()
    {
        CloseHandle(foregroundWindowHandle);
    }

    HWND AttemptSetForeground(HWND aTargetWindow, HWND aForeWindow)
    {
        SetForegroundWindow(aTargetWindow);
        Sleep(10);
        HWND new_fore_window = GetForegroundWindow();
        if (new_fore_window == aTargetWindow)
            return aTargetWindow;
        if (new_fore_window != aForeWindow && aTargetWindow == GetWindow(new_fore_window, GW_OWNER))
            return new_fore_window;
        return NULL;
    }

    HWND SetForegroundWindowEx(HWND aTargetWindow, bool aBackgroundActivation = false)
    {
        // copy from AutoHotKey
        DWORD g_MainThreadID = GetCurrentThreadId();
        if (!aTargetWindow)
            return NULL;

        DWORD target_thread = GetWindowThreadProcessId(aTargetWindow, NULL);

        HWND orig_foreground_wnd = GetForegroundWindow();

        if (IsIconic(aTargetWindow) && !aBackgroundActivation)
            ShowWindow(aTargetWindow, SW_RESTORE);

        if (aTargetWindow == orig_foreground_wnd)
            return aTargetWindow;

        HWND new_foreground_wnd;

        if (true)
    #define IF_ATTEMPT_SET_FORE if ((new_foreground_wnd = AttemptSetForeground(aTargetWindow, orig_foreground_wnd)))
            IF_ATTEMPT_SET_FORE
                return new_foreground_wnd;

        bool is_attached_my_to_fore = false, is_attached_fore_to_target = false;
        DWORD fore_thread = 0;
        if (orig_foreground_wnd)
        {
            fore_thread = GetWindowThreadProcessId(orig_foreground_wnd, NULL);
            if (fore_thread && g_MainThreadID != fore_thread)
                is_attached_my_to_fore = AttachThreadInput(g_MainThreadID, fore_thread, TRUE) != 0;
            if (fore_thread && target_thread && fore_thread != target_thread)
                is_attached_fore_to_target = AttachThreadInput(fore_thread, target_thread, TRUE) != 0;
        }

        bool sTriedKeyUp = false;

        for (int i = 0; i < 5; ++i)
        {
            if (!sTriedKeyUp) // At least one attempt failed this time, and Alt-up hasn't been tried since the process started.
            {
                sTriedKeyUp = true;
                key_up(VK_MENU);
            }
            IF_ATTEMPT_SET_FORE
                break;
        }

        if (!new_foreground_wnd)
        {
            key_down(VK_MENU);
            key_up(VK_MENU);
            key_down(VK_MENU);
            key_up(VK_MENU);

            new_foreground_wnd = AttemptSetForeground(aTargetWindow, orig_foreground_wnd);
        }
        if (orig_foreground_wnd)
        {
            if (is_attached_my_to_fore)
                AttachThreadInput(g_MainThreadID, fore_thread, FALSE);
            if (is_attached_fore_to_target)
                AttachThreadInput(fore_thread, target_thread, FALSE);
        }

        if (new_foreground_wnd && !aBackgroundActivation)
        {
            BringWindowToTop(aTargetWindow);
        }
        return new_foreground_wnd;
    }

    void fillDirsTxt()
    {
        wxString sdDir = wxStandardPaths::Get().GetExecutablePath().BeforeLast('\\');
        wxString dirsPath = sdDir;
        dirsPath.Append("\\dirs.txt");
        RecordsDispatcher dirs(dirsPath.ToStdWstring());
        dirs.load_dirs();

        dirs.update_record_with_path_and_alias(sdDir.ToStdWstring(), L"sd");

        wxString userProfile;
        if (wxGetEnv("USERPROFILE", &userProfile))
        {
            dirs.update_record_with_path_and_alias(userProfile.ToStdWstring(), L"home");
            wxString downloads = userProfile + "\\Downloads";
            dirs.update_record_with_path_and_alias(downloads.ToStdWstring(), L"loads");
            wxString documents = userProfile + "\\Documents";
            dirs.update_record_with_path_and_alias(documents.ToStdWstring(), L"doc");
            wxString music = userProfile + "\\Music";
            dirs.update_record_with_path_and_alias(music.ToStdWstring(), L"music");
            wxString pictures = userProfile + "\\Pictures";
            dirs.update_record_with_path_and_alias(pictures.ToStdWstring(), L"pic");
            wxString videos = userProfile + "\\Videos";
            dirs.update_record_with_path_and_alias(videos.ToStdWstring(), L"videos");
        }

        dirs.update_record_with_path_and_alias(L"C:\\", L"c");
        dirs.update_record_with_path_and_alias(L"D:\\", L"d");
        dirs.update_record_with_path_and_alias(L"E:\\", L"e");
        dirs.update_record_with_path_and_alias(L"F:\\", L"f");

        wxString windows;
        if (wxGetEnv("WINDIR", &windows))
        {
            dirs.update_record_with_path_and_alias(windows.ToStdWstring(), L"win");
        }
        wxString programFiles;
        if (wxGetEnv("PROGRAMFILES", &programFiles))
        {
            dirs.update_record_with_path_and_alias(programFiles.ToStdWstring(), L"pf");
        }
        wxString programFiles86;
        if (wxGetEnv("PROGRAMFILES(x86)", &programFiles86))
        {
            dirs.update_record_with_path_and_alias(programFiles86.ToStdWstring(), L"pf86");
        }

        dirs.save_dirs();
    }
};

#endif // WINAPI_CONTROLLER_H_INCLUDED
