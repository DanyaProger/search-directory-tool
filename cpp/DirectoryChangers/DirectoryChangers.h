#ifndef DIRECTORYCHANGERS_H_INCLUDED
#define DIRECTORYCHANGERS_H_INCLUDED

#include <windows.h>
#include <string>
#include <filesystem>

using namespace std;

class DirectoryChanger
{
protected:
    virtual void change_directory(wstring path){}
};

class TerminalDirectoryChanger : public DirectoryChanger
{
private:
    int delay;
public:
    TerminalDirectoryChanger(int delay)
    {
        this->delay = delay;
    }

    int get_delay()
    {
        return this->delay;
    }

    virtual wstring path_to_cd_command(wstring path){};

protected:
    void change_directory(wstring path) override {

    }
};

class CmdDirectoryChanger : public TerminalDirectoryChanger
{
public:
    CmdDirectoryChanger() : TerminalDirectoryChanger(0)
    {}

    wstring path_to_cd_command(wstring path) override
    {
        if (towlower(filesystem::current_path().wstring()[0]) == towlower(path[0]))
        {
            return L"cd " + path;
        }
        else
        {
            return L"cd /D " + path;
        }
    }
};

#endif // DIRECTORYCHANGER_H_INCLUDED
