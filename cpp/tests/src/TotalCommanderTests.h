#ifndef TOTALCOMMANDERTESTS_H_INCLUDED
#define TOTALCOMMANDERTESTS_H_INCLUDED

class TotalCommanderTests : public AbstractChangerTests
{
private:
    TotalCommanderDirectoryChanger changer;
protected:
    string get_test_class_name() override
    {
        return "TotalCommanderTests";
    }

    wstring get_terminal_exe() override
    {
        return L"D:\\Soft\\totalcmd\\TOTALCMD64.EXE";
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
        key_press(VK_RIGHT);
        text_entry(command);
        key_press(VK_RETURN);
    }

    void send_exit() override
    {
        key_press(VK_RIGHT);
        text_entry(L"cm_Exit");
        key_press(VK_RETURN);
    }
};

#endif // TOTALCOMMANDERTESTS_H_INCLUDED
