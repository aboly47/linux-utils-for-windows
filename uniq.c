#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 2){ fprintf(stderr,"Usage: %s FILE\n",argv[0]); return 1; }

    FILE *f = fopen(argv[1],"r");
    if(!f){ perror(argv[1]); return 1; }

    char line[1024], prev[1024] = "";
    while(fgets(line,sizeof(line),f)) {
        if(strcmp(line, prev)!=0) { printf("%s",line); strcpy(prev,line); }
    }
    fclose(f);
    return 0;
}
