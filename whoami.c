#include <stdio.h>
#include <windows.h>

int main() {
    char username[256];
    DWORD size = sizeof(username);
    if(GetUserNameA(username, &size))
        printf("%s\n", username);
    return 0;
}
