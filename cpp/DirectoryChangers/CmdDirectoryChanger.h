#ifndef CMDDIRECTORYCHANGER_H_INCLUDED
#define CMDDIRECTORYCHANGER_H_INCLUDED

#include <string>
#include <filesystem>

using namespace std;

class CmdDirectoryChanger : public TerminalDirectoryChanger
{
public:
    CmdDirectoryChanger() : TerminalDirectoryChanger(0)
    {}

    wstring path_to_cd_command(wstring path)
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

#endif // CMDDIRECTORYCHANGER_H_INCLUDED
