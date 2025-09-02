#include <stdio.h>
#include <windows.h>

int main() {
    DWORD ms = GetTickCount();
    DWORD seconds = ms / 1000;
    DWORD mins = seconds / 60;
    DWORD hours = mins / 60;
    DWORD days = hours / 24;

    printf("Uptime: %lu days, %lu:%02lu:%02lu\n", days, hours%24, mins%60, seconds%60);
    return 0;
}
