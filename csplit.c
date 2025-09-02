#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 3) { 
        fprintf(stderr,"Usage: %s FILE PATTERN\n",argv[0]); 
        return 1; 
    }

    FILE *f = fopen(argv[1],"r");
    if(!f) { perror(argv[1]); return 1; }

    char line[1024];
    int file_index = 0;
    FILE *out = fopen("xx00","w");
    if(!out) { perror("xx00"); return 1; }

    while(fgets(line,sizeof(line),f)) {
        if(strstr(line, argv[2])) {
            fclose(out);
            char outname[16];
            snprintf(outname,sizeof(outname),"xx%02d",++file_index);
            out = fopen(outname,"w");
            if(!out) { perror(outname); return 1; }
        }
        fputs(line,out);
    }

    fclose(out);
    fclose(f);
    return 0;
}
