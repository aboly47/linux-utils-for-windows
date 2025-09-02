#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void remove_dir(const char *path) {
    WIN32_FIND_DATAA fd;
    char search_path[512];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);

    HANDLE h = FindFirstFileA(search_path, &fd);
    if(h == INVALID_HANDLE_VALUE) return;

    do {
        if(strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..")) {
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s\\%s", path, fd.cFileName);

            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                remove_dir(full_path);
            } else {
                DeleteFileA(full_path);
            }
        }
    } while(FindNextFileA(h, &fd));
    FindClose(h);
    RemoveDirectoryA(path);
}

int main(int argc, char *argv[]) {
    if(argc < 2) { fprintf(stderr,"Usage: %s FILE...\n",argv[0]); return 1; }

    for(int i=1;i<argc;i++) {
        DWORD attr = GetFileAttributesA(argv[i]);
        if(attr == INVALID_FILE_ATTRIBUTES) {
            perror(argv[i]);
            continue;
        }
        if(attr & FILE_ATTRIBUTE_DIRECTORY) remove_dir(argv[i]);
        else DeleteFileA(argv[i]);
    }
    return 0;
}
