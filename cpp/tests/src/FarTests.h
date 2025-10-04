#ifndef FARTESTS_H_INCLUDED
#define FARTESTS_H_INCLUDED

#include "AbstractChangerTests.h"
#include "InputSimulator.h"
#include "DirectoryChangers.h"

class FarTests : public AbstractChangerTests
{
private:
    FarDirectoryChanger changer;
protected:
    string get_test_class_name() override
    {
        return "FarTests";
    }

    wstring get_terminal_exe() override
    {
        return L"c:\\Program Files\\Far Manager\\Far.exe";
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

#endif // FARTESTS_H_INCLUDED
