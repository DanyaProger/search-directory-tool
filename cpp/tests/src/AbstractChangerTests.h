#ifndef ABSTRACTCHANGERTESTS_H
#define ABSTRACTCHANGERTESTS_H

#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <locale>
#include <codecvt>

#include "InputSimulator.h"
#include "DirectoryChangers.h"
#include "RecordsDispatcher.h"

using namespace std;

class AbstractChangerTests
{
private:
    wstring start_str;
    PROCESS_INFORMATION processInfo;
    bool current_test_passed;
    string method_name;
    wstring project_dir = filesystem::absolute(filesystem::path(L"..\\..")).wstring();
    wstring sd_dir = filesystem::absolute(filesystem::path(L"..\\bin\\Release")).wstring();
    wstring old_path, new_path;

    void reset_check(string method_name)
    {
        current_test_passed = true;
        this->method_name = method_name;
    }

    void result_test()
    {
        string place = get_test_class_name() + ":" + method_name;
        if (current_test_passed)
        {
            wcout << "test passed: " << wstring(place.begin(), place.end()) << "\n";
        } else
        {
            wcout << "test failed: " << wstring(place.begin(), place.end()) << "\n";
        }
    }

    void check_pwd(wstring expected_dir, int counter)
    {
        wstring actual_dir;

        wifstream pwd(filesystem::path(sd_dir + L"\\pwd.txt"));
        pwd.imbue(std::locale(pwd.getloc(), new std::codecvt_utf8<wchar_t>));
        getline(pwd, actual_dir);
        pwd.close();

        transform(actual_dir.begin(), actual_dir.end(), actual_dir.begin(), ::towlower);
        transform(expected_dir.begin(), expected_dir.end(), expected_dir.begin(), ::towlower);

        if (actual_dir != expected_dir)
        {
            string place = get_test_place(counter);
            wcout << "    " << wstring(place.begin(), place.end()) << " " << "mismatch: actual dir: \"" << actual_dir << "\" expected_dir: \"" << expected_dir << "\"\n";
            current_test_passed = false;
        }
    }

    string get_test_place(int counter) {
        return get_test_class_name() + ":" + method_name + ":" + to_string(counter);
    }

    wstring get_path_variable_in_registry(DWORD& path_type)
    {
        HKEY hKey;
        RegOpenKeyExW(HKEY_CURRENT_USER, L"Environment", 0, KEY_ALL_ACCESS, &hKey);
        BYTE* buffer;
        DWORD bufferSize = 1000;
        buffer = new BYTE[bufferSize];

        LSTATUS status = RegQueryValueExA(hKey, "Path", NULL, &path_type, buffer, &bufferSize);
        if (status == ERROR_SUCCESS)
        {

        }
        else if (status != ERROR_MORE_DATA)
        {
            RegCloseKey(hKey);
            wcout << L"error during reading path from registry\r\n";
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

        /*PROCESS_INFORMATION setx_exe_info;
        STARTUPINFOW info={sizeof(info)};
        wstring setx_exe(L"c:\\Windows\\System32\\setx.exe");
        wstring args = setx_exe + L" Path \"" + value + L"\"";
        CreateProcessW(L"c:\\Windows\\System32\\setx.exe", const_cast<wchar_t*>(args.c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &info, &setx_exe_info);
        WaitForSingleObject(setx_exe_info.hProcess, INFINITE);
        CloseHandle(setx_exe_info.hProcess);
        CloseHandle(setx_exe_info.hThread);*/
    }

protected:
    virtual wstring get_terminal_exe(){};
    virtual TerminalDirectoryChanger* get_terminal_changer(){};

    virtual int get_init_sleep(){};
    virtual void send_command(wstring command){};
    virtual void send_exit(){};

    virtual string get_test_class_name() {
        return "AbstractChangerTests";
    }

public:
    void before_all_tests()
    {
        /*old_path = wstring(_wgetenv(L"PATH"));
        new_path = sd_dir + L";" + old_path;
        _wputenv((L"PATH=" + new_path).c_str());*/

        /*DWORD path_type;
        wstring path;
        if (filesystem::exists(filesystem::path(path_txt)))
        {
            wifstream txt(filesystem::path(path_txt.c_str()));
            txt.imbue(std::locale(txt.getloc(), new std::codecvt_utf8<wchar_t>));
            getline(txt, path);
            txt.close();
            filesystem::remove(filesystem::path(path_txt));

            get_path_variable_in_registry(path_type);
            set_path_variable_in_registry(path, path_type);
        }
        path = get_path_variable_in_registry(path_type);

        wstring new_path = sd_dir + L";" + path;

        set_path_variable_in_registry(new_path, path_type);

        wofstream txt(filesystem::path(path_txt.c_str()));
        txt.imbue(std::locale(txt.getloc(), new std::codecvt_utf8<wchar_t>));
        txt << path;
        txt.close();

        wcout << get_path_variable_in_registry(path_type) << "\r\n";*/

        if (filesystem::exists(sd_dir + L"\\dirs.txt") && !filesystem::exists(sd_dir + L"\\dirs1.txt"))
        {
            filesystem::rename(sd_dir + L"\\dirs.txt", sd_dir + L"\\dirs1.txt");
            filesystem::remove(sd_dir + L"\\dirs.txt");
        }

        RecordsDispatcher records(sd_dir + L"\\dirs.txt");
        records.load_dirs();
        records.update_record_with_path_and_alias(wstring(_wgetenv(L"USERPROFILE")), L"home");
        records.save_dirs();

        wstring sd_pwd_content[6] = {
            L"@echo off",
            L"FOR /F \"tokens=* USEBACKQ\" %%F IN (`chcp`) DO (SET var=%%F)",
            L"FOR %%A IN (%var%) DO SET last=%%A",
            L"chcp 65001>NUL 2>&1",
            L"echo %cd%> " + sd_dir + L"\\pwd.txt",
            L"chcp %last%>NUL 2>&1"
        };
        wofstream sd_pwd(filesystem::path(sd_dir + L"\\sd-pwd.bat"));
        sd_pwd.imbue(std::locale(sd_pwd.getloc(), new std::codecvt_utf8<wchar_t>));
        for (int i = 0; i < 6; i++)
        {
            sd_pwd << sd_pwd_content[i] << "\r\n";
        }
        sd_pwd.close();

        STARTUPINFOW info={sizeof(info)};
        CreateProcessW(get_terminal_exe().c_str(), NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &info, &processInfo);

        Sleep(get_init_sleep());
    }

    void test_sd_home()
    {
        reset_check("test_sd_home");

        filesystem::remove(sd_dir + L"\\pwd.txt");

        wstring start_dir = project_dir;

        send_command(get_terminal_changer()->path_to_cd_command(start_dir));
        Sleep(1000);

        send_command(L"sd-pwd.bat");
        Sleep(1000);

        check_pwd(start_dir, 1);

        send_command(L"sd home");
        Sleep(1000);

        send_command(L"sd-pwd.bat");
        Sleep(1000);

        wstring expected_dir(_wgetenv(L"USERPROFILE"));

        check_pwd(expected_dir, 2);

        result_test();
    }

    void test_several_aliases()
    {
        reset_check("test_several_aliases");

        filesystem::remove(sd_dir + L"\\pwd.txt");

        wstring start_dir1 = (filesystem::path(project_dir)/L"tmp").wstring();
        wstring start_dir2 = (filesystem::path(project_dir)/L"tmp"/L"dir1").wstring();

        filesystem::create_directories(filesystem::path(start_dir2));

        send_command(get_terminal_changer()->path_to_cd_command(start_dir1));
        Sleep(1000);

        send_command(L"sd --alias tmp");
        Sleep(1000);

        send_command(get_terminal_changer()->path_to_cd_command(start_dir2));
        Sleep(1000);

        send_command(L"sd --alias dir1");
        Sleep(1000);

        send_command(L"sd tmp");
        Sleep(1000);

        send_command(L"sd-pwd.bat");
        Sleep(1000);

        check_pwd(start_dir1, 1);

        send_command(L"sd dir1");
        Sleep(1000);

        send_command(L"sd-pwd.bat");
        Sleep(1000);

        check_pwd(start_dir2, 2);

        RecordsDispatcher records(sd_dir + L"\\dirs.txt");
        records.load_dirs();
        records.remove_record_with_alias(L"tmp");
        records.remove_record_with_alias(L"dir1");
        records.save_dirs();

        result_test();
    }

    void test_replace_alias()
    {
        reset_check("test_replace_alias");

        filesystem::remove(sd_dir + L"\\pwd.txt");

        wstring start_dir1 = project_dir;
        wstring start_dir2 = project_dir + L"\\tmp";

        filesystem::create_directories(filesystem::path(start_dir2));

        send_command(get_terminal_changer()->path_to_cd_command(start_dir1));
        Sleep(1000);

        send_command(L"sd --alias tmp");
        Sleep(1000);

        send_command(get_terminal_changer()->path_to_cd_command(start_dir2));
        Sleep(1000);

        send_command(L"sd --alias tmp");
        Sleep(1000);

        send_command(get_terminal_changer()->path_to_cd_command(start_dir1));
        Sleep(1000);

        send_command(L"sd tmp");
        Sleep(1000);

        send_command(L"sd-pwd.bat");
        Sleep(1000);

        check_pwd(start_dir2, 1);

        RecordsDispatcher records(sd_dir + L"\\dirs.txt");
        records.load_dirs();
        records.remove_record_with_alias(L"tmp");
        records.save_dirs();

        result_test();
    }

    void test_create_current_directory_alias()
    {
        reset_check("test_create_current_directory_alias");

        wstring tmp_dir = project_dir + L"\\tmp";
        wstring dir_with_spaces = project_dir + L"\\tmp\\space 1 2 3 space";
        wstring dir_with_unicode = project_dir + L"\\tmp\\搜尋目錄";

        wstring dirs[4] = {L"c:\\Program Files", tmp_dir, dir_with_spaces, dir_with_unicode};

        for (int i = 0; i < 4; i++)
        {
            filesystem::remove(sd_dir + L"\\pwd.txt");

            filesystem::create_directories(dirs[i]);

            send_command(get_terminal_changer()->path_to_cd_command(dirs[i]));
            Sleep(1000);

            send_command(L"sd --alias dir");
            Sleep(1000);

            send_command(L"sd home");
            Sleep(1000);

            send_command(L"sd dir");
            Sleep(1000);

            send_command(L"sd-pwd.bat");
            Sleep(1000);

            check_pwd(dirs[i], i);

            RecordsDispatcher records(sd_dir + L"\\dirs.txt");
            records.load_dirs();
            records.remove_record_with_alias(L"dir");
            records.save_dirs();
        }

        result_test();
    }

    void test_change_directory_between_drives()
    {
        reset_check("test_change_directory_with_alias");

        wstring c_dirs[2] = {L"c:\\", L"c:\\Program Files"};
        wstring d_dir = L"d:\\";
        const int DIRS_SIZE = 3;
        wstring dirs[DIRS_SIZE] = {c_dirs[0], c_dirs[1], d_dir};
        wstring aliases[DIRS_SIZE] = {L"_c", L"_pf", L"_d"};

        RecordsDispatcher records(sd_dir + L"\\dirs.txt");
        records.load_dirs();
        for (int i = 0; i < DIRS_SIZE; i++)
        {
            records.update_record_with_path_and_alias(dirs[i], aliases[i]);
        }
        records.save_dirs();

        send_command(L"sd home");
        Sleep(1000);

        const int SEQUENCE_SIZE = 5;
        int dir_sequence[SEQUENCE_SIZE] = {2, 0, 2, 1, 2};

        for (int i = 0; i < SEQUENCE_SIZE; i++) {
            filesystem::remove(sd_dir + L"\\pwd.txt");

            send_command(L"sd " + aliases[dir_sequence[i]]);
            Sleep(1000);

            send_command(L"sd-pwd.bat");
            Sleep(1000);

            check_pwd(dirs[dir_sequence[i]], i + 1);
        }

        records.load_dirs();
        for (int i = 0; i < DIRS_SIZE; i++) {
            records.remove_record_with_alias(aliases[i]);
        }
        records.save_dirs();

        result_test();
    }

    void after_all_tests()
    {
        send_exit();

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        filesystem::remove_all(project_dir + L"\\tmp");

        if (filesystem::exists(sd_dir + L"\\dirs1.txt"))
        {
            if (filesystem::exists(sd_dir + L"\\dirs.txt"))
                filesystem::remove(sd_dir + L"\\dirs.txt");
            filesystem::rename(sd_dir + L"\\dirs1.txt", sd_dir + L"\\dirs.txt");
            filesystem::remove(sd_dir + L"\\dirs1.txt");
        }

        /*DWORD path_type;
        wstring path;

        if (filesystem::exists(path_txt))
        {
            wifstream txt(filesystem::path(path_txt.c_str()));
            txt.imbue(std::locale(txt.getloc(), new std::codecvt_utf8<wchar_t>));
            getline(txt, path);
            txt.close();
            filesystem::remove(filesystem::path(path_txt));

            get_path_variable_in_registry(path_type);
            set_path_variable_in_registry(path, path_type);
        }*/
    }
};

#endif
