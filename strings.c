#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if(argc < 2) { fprintf(stderr,"Usage: %s FILE\n",argv[0]); return 1; }

    FILE *f = fopen(argv[1], "rb");
    if(!f) { perror(argv[1]); return 1; }

    int c, len=0;
    char buf[1024];

    while((c=fgetc(f))!=EOF) {
        if(isprint(c)) buf[len++] = c;
        else {
            if(len>=4) { buf[len]=0; printf("%s\n",buf); }
            len=0;
        }
    }

    if(len>=4) { buf[len]=0; printf("%s\n",buf); }

    fclose(f);
    return 0;
}
