#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000
#define LINE_LEN 1024

int main(int argc, char *argv[]) {
    int n = 10;
    int file_arg = 1;

    if(argc >= 3 && argv[1][0]=='-' && argv[1][1]=='n') {
        n = atoi(argv[2]);
        file_arg = 3;
    }

    if(argc <= file_arg) {
        fprintf(stderr, "Usage: %s [-n NUM] FILE\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[file_arg], "r");
    if(!f) { perror(argv[file_arg]); return 1; }

    char *lines[MAX_LINES];
    int count = 0;

    char buffer[LINE_LEN];
    while(fgets(buffer, sizeof(buffer), f)) {
        if(count < MAX_LINES) {
            lines[count] = strdup(buffer);
            count++;
        }
    }
    fclose(f);

    int start = count > n ? count - n : 0;
    for(int i=start;i<count;i++) {
        fputs(lines[i], stdout);
        free(lines[i]);
    }

    return 0;
}
