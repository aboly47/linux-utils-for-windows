#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LEN MAX_PATH

int main(int argc, char *argv[]) {
    char full_path[MAX_PATH_LEN];
    DWORD path_len;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <relative-or-partial-path>\n", argv[0]);
        fprintf(stderr, "Example: %s .\\myfile.txt\n", argv[0]);
        return 1;
    }

    const char *input_path = argv[1];

    // Resolve to full path
    path_len = GetFullPathNameA(input_path, MAX_PATH_LEN, full_path, NULL);

    if (path_len == 0) {
        fprintf(stderr, "Error: Cannot resolve path '%s' (last error: %lu)\n", input_path, GetLastError());
        return 1;
    }

    if (path_len >= MAX_PATH_LEN) {
        fprintf(stderr, "Error: Resolved path is too long.\n");
        return 1;
    }

    printf("%s\n", full_path);
    return 0;
}