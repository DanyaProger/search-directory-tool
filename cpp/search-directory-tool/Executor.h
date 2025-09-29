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
            return;
        }
        if (sd_args.is_flag(L"parent"))
        {
            parent_info_message();
            return;
        }
        if (sd_args.is_flag(L"path"))
        {
            return;
        }
        if (sd_args.is_flag(L"remove-path"))
        {
            return;
        }

        if (sd_args.args_size() > 1)
        {
            return;
        }

        bool is_alias = sd_args.is_option(L"alias");
        wstring alias = is_alias ? sd_args.get_option(L"alias") : L"";
        bool is_token = sd_args.args_size();
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

    void parent_info_message()
    {
        DWORD pid = GetCurrentProcessId();
        DWORD ppid = get_parent_process_id(pid);
        wstring filename = get_process_name(ppid);
        wstring message = wstring(L"pid=") + to_wstring(pid) + wstring(L" filename=") + filename;
        MessageBoxW(NULL, message.c_str(), L"Parent process info", 0);
    }
};

#endif // EXECUTOR_H_INCLUDED
