#include <stdio.h>
#include <stdlib.h>

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

    char line[1024];
    int count = 0;
    while(fgets(line, sizeof(line), f) && count<n) {
        fputs(line, stdout);
        count++;
    }

    fclose(f);
    return 0;
}
