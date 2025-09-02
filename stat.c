#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/stat.h>
#include <time.h>

// Convert FILETIME to readable string
void filetime_to_str(FILETIME ft, char *buf, size_t bufsize) {
    SYSTEMTIME stUTC, stLocal;
    FileTimeToSystemTime(&ft, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    snprintf(buf, bufsize, "%04d-%02d-%02d %02d:%02d:%02d",
             stLocal.wYear, stLocal.wMonth, stLocal.wDay,
             stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
}

void print_stat(const char *filename) {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (!GetFileAttributesEx(filename, GetFileExInfoStandard, &fad)) {
        fprintf(stderr, "stat: cannot stat '%s'\n", filename);
        return;
    }

    LARGE_INTEGER size;
    size.HighPart = fad.nFileSizeHigh;
    size.LowPart  = fad.nFileSizeLow;

    char ctime[64], atime[64], mtime[64];
    filetime_to_str(fad.ftCreationTime, ctime, sizeof(ctime));
    filetime_to_str(fad.ftLastAccessTime, atime, sizeof(atime));
    filetime_to_str(fad.ftLastWriteTime, mtime, sizeof(mtime));

    printf("  File: %s\n", filename);
    printf("  Size: %lld bytes\n", (long long)size.QuadPart);
    printf("Access: %s\n", atime);
    printf("Modify: %s\n", mtime);
    printf("Change: %s\n", ctime);
    printf("Attributes:");
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) printf(" directory");
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_READONLY)  printf(" readonly");
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)    printf(" hidden");
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)    printf(" system");
    if (fad.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)   printf(" archive");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FILE...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        print_stat(argv[i]);
        if (i < argc - 1) printf("\n");
    }
    return 0;
}
