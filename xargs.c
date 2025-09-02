#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 2){ fprintf(stderr,"Usage: %s COMMAND\n",argv[0]); return 1; }

    char line[1024];
    while(fgets(line,sizeof(line),stdin)) {
        line[strcspn(line,"\n")] = 0;
        char cmd[2048];
        snprintf(cmd,sizeof(cmd),"%s %s", argv[1], line);
        system(cmd);
    }

    return 0;
}
