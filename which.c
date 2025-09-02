#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int file_exists(const char *path) {
    DWORD attrib = GetFileAttributesA(path);
    return (attrib != INVALID_FILE_ATTRIBUTES &&
           !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program>\n", argv[0]);
        return 1;
    }

    char *program = argv[1];
    char *path_env = getenv("PATH");
    if (!path_env) {
        fprintf(stderr, "PATH not set.\n");
        return 1;
    }

    char *path_copy = strdup(path_env);
    if (!path_copy) {
        perror("strdup");
        return 1;
    }

    char *token = strtok(path_copy, ";");
    char fullpath[MAX_PATH];
    const char *exts[] = {".exe", ".bat", ".cmd", ".com", ""};  // Windows executable extensions

    while (token) {
        for (int i = 0; exts[i][0]; i++) {
            snprintf(fullpath, sizeof(fullpath), "%s\\%s%s", token, program, exts[i]);
            if (file_exists(fullpath)) {
                printf("%s\n", fullpath);
                free(path_copy);
                return 0;
            }
        }
        token = strtok(NULL, ";");
    }

    fprintf(stderr, "%s not found in PATH\n", program);
    free(path_copy);
    return 1;
}
