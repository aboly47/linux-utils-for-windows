#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s FILE\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(!f) {
        perror(argv[1]);
        return 1;
    }

    int c, lines=0, words=0, bytes=0, in_word=0;
    while((c = fgetc(f)) != EOF) {
        bytes++;
        if(c=='\n') lines++;
        if(isspace(c)) in_word=0;
        else if(!in_word) { in_word=1; words++; }
    }

    fclose(f);
    printf("%d %d %d %s\n", lines, words, bytes, argv[1]);
    return 0;
}
