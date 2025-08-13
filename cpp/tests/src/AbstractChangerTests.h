#ifndef ABSTRACTCHANGERTESTS_H
#define ABSTRACTCHANGERTESTS_H

#include <fstream>
#include <string>
#include <windows.h>
#include <filesystem>
#include <iostream>

#include "InputSimulator.h"
#include "DirectoryChangers.h"

using namespace std;

class AbstractChangerTests
{
private:
    wstring start_str;
    PROCESS_INFORMATION processInfo;
protected:
    virtual wstring get_terminal_exe(){};
    virtual TerminalDirectoryChanger* get_terminal_changer(){};

    virtual int get_init_sleep(){};
    virtual void send_command(wstring command){};
    virtual void send_exit(){};

public:
    void before_all_tests()
    {
        STARTUPINFOW info={sizeof(info)};
        CreateProcessW(get_terminal_exe().c_str(), NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &info, &processInfo);

        Sleep(get_init_sleep());
    }

    void test_sd_home()
    {
        filesystem::remove(L"d:\\Soft\\sd\\pwd.bat");

        send_command(get_terminal_changer()->path_to_cd_command(L"c:\\Users\\danil\\source\\repos\\search-directory-tool"));
        Sleep(1000);

        send_command(L"sd home");

        Sleep(2000);

        send_command(L"sd-pwd.bat");

        Sleep(2000);

        wstring actual_dir;

        wifstream pwd(L"d:\\Soft\\sd\\pwd.txt");
        pwd >> actual_dir;
        pwd.close();

        if (actual_dir != L"c:\\Users\\danil")
        {
            wcout << "wrong actual string: " << actual_dir << "\n";
            return;
        }
        cout << "test passed\n";
    }

    void after_all_tests()
    {
        send_exit();

        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
};

#endif
