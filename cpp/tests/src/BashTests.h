#ifndef BASHTESTS_H_INCLUDED
#define BASHTESTS_H_INCLUDED

#include "AbstractChangerTests.h"
#include "InputSimulator.h"
#include "DirectoryChangers.h"

class BashTests : public AbstractChangerTests
{
private:
    BashDirectoryChanger changer;
protected:
    string get_test_class_name() override
    {
        return "BashTests";
    }

    wstring get_terminal_exe() override
    {
        return L"c:\\Program Files\\Git\\git-bash.exe";
    }

    TerminalDirectoryChanger* get_terminal_changer() override
    {
        return &changer;
    }

    int get_init_sleep() override
    {
        return 5000;
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

#endif // BASHTESTS_H_INCLUDED
