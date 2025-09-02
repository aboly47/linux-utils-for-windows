#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc < 2){ fprintf(stderr,"Usage: %s FILE\n",argv[0]); return 1; }

    FILE *f = fopen(argv[1],"w");
    if(!f){ perror(argv[1]); return 1; }

    int c;
    while((c=getchar())!=EOF){
        putchar(c);
        fputc(c,f);
    }

    fclose(f);
    return 0;
}
