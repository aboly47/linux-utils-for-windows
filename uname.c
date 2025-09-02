#include <stdio.h>
#include <windows.h>

int main() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    printf("Architecture: ");
    switch(si.wProcessorArchitecture){
        case 9: printf("x64"); break;
        case 0: printf("x86"); break;
        case 5: printf("ARM"); break;
        default: printf("Unknown"); break;
    }
    printf("\n");

    char computerName[256];
    DWORD size = sizeof(computerName);
    if(GetComputerNameA(computerName, &size))
        printf("Hostname: %s\n", computerName);

    return 0;
}
