#ifndef EXPLORER_TESTS_H_INCLUDED
#define EXPLORER_TESTS_H_INCLUDED

#include "AbstractChangerTests.h"
#include "InputSimulator.h"
#include "DirectoryChangers.h"

class ExplorerTests : public AbstractChangerTests
{
private:
    ExplorerDirectoryChanger changer;
    boolean first_command = true;
protected:
    string get_test_class_name() override
    {
        return "ExplorerTests";
    }

    wstring get_terminal_exe() override
    {
        return L"c:\\Windows\\explorer.exe";
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
        if (first_command)
        {
            key_down(VK_CONTROL);
            key_down('L');
            key_up(VK_CONTROL);
            key_up('L');
        } else
        {
            key_down(VK_CONTROL);
            key_down('A');
            key_up(VK_CONTROL);
            key_up('A');
        }
        text_entry(command);
        key_press(VK_RETURN);
    }

    void send_exit() override
    {
        key_down(VK_MENU);
        key_down(VK_F4);
        key_up(VK_MENU);
        key_up(VK_F4);
    }
};

#endif // EXPLORER_H_INCLUDED
