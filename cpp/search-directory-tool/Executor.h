#ifndef EXECUTOR_H_INCLUDED
#define EXECUTOR_H_INCLUDED

#include <iostream>
#include <filesystem>
#include <windows.h>

#include "argsparser.h"
#include "RecordsDispatcher.h"
#include "processes_helper.h"
#include "TerminalDispatcher.h"

extern wstring exe_path;

class Executor
{
public:
    void run(SdArgs sd_args) {
        const int MAX_BUFFER = 500;
        wchar_t buffer[MAX_BUFFER];
        GetModuleFileNameW(NULL, buffer, MAX_BUFFER);
        exe_path = wstring(buffer);

        if (sd_args.is_flag(L"help"))
        {
            help_message();
            return;
        }
        if (sd_args.is_flag(L"parent"))
        {
            parent_info_message();
            return;
        }
        if (sd_args.is_flag(L"path"))
        {
            add_sd_directory_to_path();
            return;
        }
        if (sd_args.is_flag(L"remove-path"))
        {
            remove_sd_directory_from_path();
            return;
        }

        if (sd_args.args_size() > 1)
        {
            return;
        }

        bool is_alias = sd_args.is_option(L"alias");
        wstring alias = is_alias ? sd_args.get_option(L"alias") : L"";
        bool is_token = sd_args.args_size() == 1;
        wstring token = is_token ? sd_args.arg(0) : L"";

        run(is_alias, alias, is_token, token);
    }

    void run(bool is_alias, wstring alias, bool is_token, wstring token)
    {
        RecordsDispatcher records(filesystem::path(exe_path).parent_path()/L"dirs.txt");
        records.load_dirs();

        if (!is_token)
        {
            token = filesystem::current_path().wstring();
        }

        wstring fullpath = records.get_most_suitable_path(token);
        if (fullpath == L"" && filesystem::path(token).is_absolute())
            fullpath = token;
        if (fullpath != L"")
        {
            if (!is_alias)
            {
                records.update_record_with_path_and_alias(fullpath);
            }
            else
            {
                records.update_record_with_path_and_alias(fullpath, alias);
            }
        }

        records.save_dirs();

        if (fullpath != L"")
        {
            TerminalDispatcher().change_directory(fullpath);
        }
    }

    void help_message()
    {
        wstring help;
        help += L"usage: sd [] [<full-path or alias>] [--alias <alias>] [--alias <alias> <full-path>]\r\n";
        help += L"          [--help] [--parent] [--path] [--remove-path]\r\n";
        help += L"\r\n";
        help += L"Main sd usecases:\r\n";
        help += L"    sd --alias <alias>        create alias for current directory\r\n";
        help += L"    sd <alias>                change current directory to directory with alias <alias>\r\n";
        help += L"    sd <full-path>            change current directory to <full-path> directory\r\n";
        help += L"\r\n";
        help += L"Options:\r\n";
        help += L"    --alias <alias>           define alias for current directory or if passed <full-path> for special directory\r\n";
        help += L"    --help                    show help message\r\n";
        help += L"    --parent                  show message with parent process information\r\n";
        help += L"    --path                    add directory with sd.exe to Path environment variable\r\n";
        help += L"    --remove-path             remove directory with sd.exe from Path environment variable\r\n";

        MessageBoxW(NULL, help.c_str(), L"sd help", 0);
    }

    void parent_info_message()
    {
        DWORD pid = GetCurrentProcessId();
        DWORD ppid = get_parent_process_id(pid);
        wstring filename = get_process_name(ppid);
        wstring message = wstring(L"pid=") + to_wstring(pid) + wstring(L" filename=") + filename;
        MessageBoxW(NULL, message.c_str(), L"Parent process info", 0);
    }

    wstring get_path_variable_in_registry(DWORD& path_type)
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

    void set_path_variable_in_registry(wstring value, DWORD path_type)
    {
        int buffer_size = WideCharToMultiByte(CP_ACP, 0, value.c_str(), value.size(), NULL, 0 , NULL, NULL);
        BYTE* buffer = new BYTE[buffer_size + 2];
        WideCharToMultiByte(CP_ACP, 0, value.c_str(), value.size(), (char*)buffer, buffer_size, NULL, NULL);

        HKEY hKey;
        RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_ALL_ACCESS, &hKey);

        RegSetValueExA(hKey, "Path", NULL, path_type, buffer, buffer_size);

        RegCloseKey(hKey);

        delete[] buffer;
    }

    void add_sd_directory_to_path()
    {
        wstring sd_dir = filesystem::path(exe_path).parent_path().wstring();

        DWORD path_type;
        wstring path = get_path_variable_in_registry(path_type);

        int path_size = path.size();
        while (path_size > 1 && path[path_size - 1] == L'\0')
            path_size--;

        vector<wstring> dirs;
        int pos = 0, new_pos;
        while ((new_pos = path.find(L";", pos)) != wstring::npos)
        {
            dirs.push_back(path.substr(pos, new_pos - pos));
            pos = new_pos + 1;
        }
        if (pos < path_size)
            dirs.push_back(path.substr(pos));

        bool sd_dir_in_path = false;
        for (int i = 0; i < dirs.size(); i++)
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
            set_path_variable_in_registry(new_path, path_type);

            DWORD_PTR nResult;
            SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_BLOCK, 1500, &nResult);
        }
    }

    void remove_sd_directory_from_path()
    {
        wstring sd_dir = filesystem::path(exe_path).parent_path().wstring();

        DWORD path_type;
        wstring path = get_path_variable_in_registry(path_type);
        int path_size = path.size();
        while (path_size > 1 && path[path_size - 1] == L'\0')
            path_size--;

        vector<wstring> dirs;
        int pos = 0, new_pos;
        while ((new_pos = path.find(L";", pos)) != wstring::npos)
        {
            dirs.push_back(path.substr(pos, new_pos - pos));
            pos = new_pos + 1;
        }
        if (pos < path_size)
            dirs.push_back(path.substr(pos));

        int sd_dir_index_in_path = -1;
        for (int i = 0; i < dirs.size(); i++)
        {
            if (filesystem::exists(dirs[i]) && filesystem::exists(sd_dir) && filesystem::equivalent(filesystem::path(dirs[i]), filesystem::path(sd_dir)))
            {
                sd_dir_index_in_path = i;
                break;
            }
        }
        if (sd_dir_index_in_path != -1)
        {
            wstring new_path;
            for (int i = 0; i < dirs.size(); i++)
                if (i != sd_dir_index_in_path)
                    new_path += dirs[i] + L';';
            new_path += path.substr(path_size);

            set_path_variable_in_registry(new_path, path_type);

            DWORD_PTR nResult;
            SendMessageTimeoutA(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_BLOCK, 1500, &nResult);
        }
    }
};

#endif // EXECUTOR_H_INCLUDED
