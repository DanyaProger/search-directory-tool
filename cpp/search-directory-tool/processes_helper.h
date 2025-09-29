#ifndef PROCESSES_HELPER_H_INCLUDED
#define PROCESSES_HELPER_H_INCLUDED

#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <filesystem>
#include <psapi.h>

DWORD get_parent_process_id(DWORD pid)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0;

    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hSnapshot == INVALID_HANDLE_VALUE ) return -1;

    ZeroMemory( &pe32, sizeof( pe32 ) );
    pe32.dwSize = sizeof( pe32 );
    if( !Process32First( hSnapshot, &pe32 ) ) return -2;

    do{
        if( pe32.th32ProcessID == pid ){
            ppid = pe32.th32ParentProcessID;
            break;
        }
    }while( Process32Next( hSnapshot, &pe32 ) );
    if( hSnapshot != INVALID_HANDLE_VALUE ) CloseHandle( hSnapshot );

    return ppid;
}

wstring get_process_name(DWORD pid)
{
    HANDLE Handle = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        pid /* This is the PID, you can find one from windows task manager */
    );
    if (Handle)
    {
        wchar_t Buffer[500];
        if (GetModuleFileNameExW(Handle, 0, Buffer, 500))
        {
            wstring path(Buffer);
            return filesystem::path(path).filename().wstring();
        }
        else
        {

        }
        CloseHandle(Handle);
    }
    MessageBoxW(NULL, L"Can't get process name by pid", NULL, 0);
    return L"";
}

#endif // PROCESSES_HELPER_H_INCLUDED
