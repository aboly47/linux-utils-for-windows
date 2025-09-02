#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4) {
        fprintf(stderr,"Usage: %s s/old/new/ FILE\n", argv[0]);
        return 1;
    }

    char *file = argv[3];
    char *pattern = argv[1];
    if(pattern[0]!='s' || pattern[1]!='/') { 
        fprintf(stderr,"Only simple s/old/new/ supported\n"); 
        return 1; 
    }

    char *p1 = strchr(pattern+2,'/');
    if(!p1) { fprintf(stderr,"Invalid pattern\n"); return 1; }
    *p1=0;
    char *old = pattern+2;
    char *new = p1+1;

    FILE *f = fopen(file,"r");
    if(!f){ perror(file); return 1; }

    char line[1024];
    while(fgets(line,sizeof(line),f)) {
        char *pos = line;
        while((pos=strstr(pos,old))) {
            printf("%.*s%s", (int)(pos-line), line, new);
            pos += strlen(old);
            memmove(line, pos, strlen(pos)+1);
            pos = line;
        }
        printf("%s", line);
    }
    fclose(f);
    return 0;
}
