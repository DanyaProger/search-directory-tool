#include <string>
#include <windows.h>
#include <psapi.h>
#include <filesystem>
#include <fstream>

#include "InputSimulator.h"

using namespace std;

class exception_with_message: public exception
{
private:
    string message;
public:
    exception_with_message(const string& message): message(message) {}

    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

int wmain(int argc, wchar_t** argv)
{
    if (argc < 4)
        throw exception_with_message("few arguments");

    int sdProcessId = _wtoi(argv[1]);

    HANDLE sdProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, sdProcessId);

    if (sdProcess != INVALID_HANDLE_VALUE)
    {
        wchar_t Buffer[500];
        if (GetModuleFileNameExW(sdProcess, 0, Buffer, 500))
        {
            wstring path(Buffer);
            wstring process_name = filesystem::path(path).filename().wstring();
            if (process_name == L"sd.exe")
            {
                WaitForSingleObject(sdProcess, 100000);
            }
        }
        CloseHandle(sdProcess);
    }

    for (int i = 2; i < argc; i = i + 2)
    {
        if (i == argc - 1)
        {
            throw exception_with_message("no pair for last argument");
        }
        wstring arg(argv[i]);
        if (arg == L"-kd")
        {
            key_down(_wtoi(argv[i + 1]));
        } else if (arg == L"-ku")
        {
            key_up(_wtoi(argv[i + 1]));
        } else if (arg == L"-t")
        {
            text_entry(wstring(argv[i + 1]));
        } else if (arg == L"-d")
        {
            Sleep(_wtoi(argv[i + 1]));
        } else
        {
            throw exception_with_message("unknown argument key");
        }
    }

    return 0;
}
