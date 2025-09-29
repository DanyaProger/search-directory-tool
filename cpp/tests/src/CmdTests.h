#ifndef CMDTESTS_H_INCLUDED
#define CMDTESTS_H_INCLUDED

#include "AbstractChangerTests.h"
#include "InputSimulator.h"
#include "DirectoryChangers.h"

class CmdTests : public AbstractChangerTests
{
private:
    CmdDirectoryChanger changer;
protected:
    string get_test_class_name() override
    {
        return "CmdTests";
    }

    wstring get_terminal_exe() override
    {
        return L"C:\\Windows\\System32\\cmd.exe";
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

#endif // CMDTESTS_H_INCLUDED
