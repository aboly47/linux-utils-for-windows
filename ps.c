#include <windows.h>
#include <stdio.h>

int main() {
    // These constants normally come from tlhelp32.h
    #define TH32CS_SNAPPROCESS 0x00000002

    typedef struct tagPROCESSENTRY32 {
        DWORD dwSize;
        DWORD cntUsage;
        DWORD th32ProcessID;
        ULONG_PTR th32DefaultHeapID;
        DWORD th32ModuleID;
        DWORD cntThreads;
        DWORD th32ParentProcessID;
        LONG pcPriClassBase;
        DWORD dwFlags;
        char szExeFile[260];
    } PROCESSENTRY32;

    // Function pointers to avoid linking issues
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hSnap == INVALID_HANDLE_VALUE) {
        perror("CreateToolhelp32Snapshot");
        return 1;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);

    // Manually get first process
    if(!Process32First(hSnap, &pe)) {
        CloseHandle(hSnap);
        return 1;
    }

    do {
        printf("%lu\t%s\n", pe.th32ProcessID, pe.szExeFile);
    } while(Process32Next(hSnap, &pe));

    CloseHandle(hSnap);
    return 0;
}
