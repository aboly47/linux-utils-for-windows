#include <windows.h>
#include <stdio.h>

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

// Forward declarations to avoid missing headers
WINBASEAPI HANDLE WINAPI CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
WINBASEAPI BOOL WINAPI Process32First(HANDLE hSnapshot, PROCESSENTRY32 *lppe);
WINBASEAPI BOOL WINAPI Process32Next(HANDLE hSnapshot, PROCESSENTRY32 *lppe);

int main() {
    while(1) {
        system("cls");

        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hSnap == INVALID_HANDLE_VALUE) {
            perror("CreateToolhelp32Snapshot");
            return 1;
        }

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);

        if(Process32First(hSnap, &pe)) {
            do {
                printf("%5lu %s\n", pe.th32ProcessID, pe.szExeFile);
            } while(Process32Next(hSnap, &pe));
        }

        CloseHandle(hSnap);
        Sleep(2000);
    }
    return 0;
}
