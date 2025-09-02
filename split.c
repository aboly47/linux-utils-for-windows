#include <stdio.h>
#include <stdlib.h>

#define LINE_LEN 1024

int main(int argc, char *argv[]) {
    int lines_per_file = 1000;

    if(argc < 2) { fprintf(stderr,"Usage: %s FILE [LINES_PER_FILE]\n",argv[0]); return 1; }
    if(argc >= 3) lines_per_file = atoi(argv[2]);

    FILE *f = fopen(argv[1], "r");
    if(!f) { perror(argv[1]); return 1; }

    char buffer[LINE_LEN];
    int file_index = 0, line_count = 0;
    FILE *out = NULL;
    char outname[64];

    while(fgets(buffer, sizeof(buffer), f)) {
        if(line_count % lines_per_file == 0) {
            if(out) fclose(out);
            sprintf(outname, "%s.%02d", argv[1], file_index++);
            out = fopen(outname, "w");
            if(!out) { perror(outname); return 1; }
        }
        fputs(buffer, out);
        line_count++;
    }
    if(out) fclose(out);
    fclose(f);
    return 0;
}
