#ifndef POWERSHELLTESTS_H_INCLUDED
#define POWERSHELLTESTS_H_INCLUDED

#include "AbstractChangerTests.h"
#include "InputSimulator.h"
#include "DirectoryChangers.h"

class PowerShellTests : public AbstractChangerTests
{
private:
    PowerShellDirectoryChanger changer;
protected:
    string get_test_class_name() override
    {
        return "PowerShellTests";
    }

    wstring get_terminal_exe() override
    {
        return L"c:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe";
    }

    TerminalDirectoryChanger* get_terminal_changer() override
    {
        return &changer;
    }

    int get_init_sleep() override
    {
        return 2000;
    }

    void send_command(wstring command) override
    {
        text_entry(command);
        key_press(VK_RETURN);
    }

    void send_exit() override
    {
        text_entry(L"exit");
        key_press(VK_RETURN);
    }
};

#endif // POWERSHELLTESTS_H_INCLUDED
