#include <stdio.h>
#include <windows.h>

void du(const char *path) {
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(path, &fd);
    if(h == INVALID_HANDLE_VALUE) return;

    do {
        if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            LARGE_INTEGER size;
            size.LowPart = fd.nFileSizeLow;
            size.HighPart = fd.nFileSizeHigh;
            printf("%lld\t%s\n", size.QuadPart, fd.cFileName);
        }
    } while(FindNextFileA(h, &fd));
    FindClose(h);
}

int main(int argc, char *argv[]) {
    if(argc < 2) { fprintf(stderr, "Usage: %s PATH\n", argv[0]); return 1; }
    du(argv[1]);
    return 0;
}
