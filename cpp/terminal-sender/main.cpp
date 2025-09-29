#include <string>
#include <windows.h>
#include <psapi.h>
#include <filesystem>

#include "InputSimulator.h"

using namespace std;

int wmain(int argc, wchar_t** argv)
{
    if (argc == 4)
    {
        int sdProcessId = _wtoi(argv[1]);
        int delay = _wtoi(argv[2]);
        wstring command(argv[3]);

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

        Sleep(delay);

        text_entry(command);
        key_press(VK_RETURN);
    }

    return 0;
}
