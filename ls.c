#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    const char *path = argc > 1 ? argv[1] : ".";

    WIN32_FIND_DATAA fd;
    char search_path[512];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    HANDLE h = FindFirstFileA(search_path, &fd);
    if(h == INVALID_HANDLE_VALUE) {
        perror("FindFirstFileA");
        return 1;
    }

    do {
        if(strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..")) {
            printf("%s", fd.cFileName);
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) printf("/"); 
            printf("\n");
        }
    } while(FindNextFileA(h, &fd));

    FindClose(h);
    return 0;
}
