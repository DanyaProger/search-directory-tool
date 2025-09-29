#ifndef DIRECTORYCHANGERS_H_INCLUDED
#define DIRECTORYCHANGERS_H_INCLUDED

#include <string>

using namespace std;

class DirectoryChanger
{
public:
    virtual void change_directory(wstring path);
};

class TerminalDirectoryChanger : public DirectoryChanger
{
private:
    wstring exe_path;
    int delay;
public:
    TerminalDirectoryChanger(int delay);
    TerminalDirectoryChanger(wstring exe_path, int delay);

    int get_delay();

    virtual wstring path_to_cd_command(wstring path);

    void change_directory(wstring path);
};

class CmdDirectoryChanger : public TerminalDirectoryChanger
{
public:
    CmdDirectoryChanger();
    CmdDirectoryChanger(wstring exe_path);

    wstring path_to_cd_command(wstring path) override;
};

class PowerShellDirectoryChanger : public TerminalDirectoryChanger
{
public:
    PowerShellDirectoryChanger();
    PowerShellDirectoryChanger(wstring exe_path);

    wstring path_to_cd_command(wstring path) override;
};

class BashDirectoryChanger : public TerminalDirectoryChanger
{
public:
    BashDirectoryChanger();
    BashDirectoryChanger(wstring exe_path);

    wstring path_to_cd_command(wstring path) override;
};

class TotalCommanderDirectoryChanger : public TerminalDirectoryChanger
{
public:
    TotalCommanderDirectoryChanger();

    wstring path_to_cd_command(wstring path) override;

    void change_directory(wstring path) override;
};

#endif // DIRECTORYCHANGER_H_INCLUDED
