#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 4) {
        fprintf(stderr,"Usage: %s -f FIELD FILE\n", argv[0]);
        return 1;
    }

    int field = atoi(argv[2]);
    FILE *f = fopen(argv[3],"r");
    if(!f){ perror(argv[3]); return 1; }

    char line[1024];
    while(fgets(line,sizeof(line),f)) {
        char *token;
        int count=1;
        token = strtok(line,"\t\n");
        while(token) {
            if(count==field) { printf("%s\n",token); break; }
            token = strtok(NULL,"\t\n");
            count++;
        }
    }

    fclose(f);
    return 0;
}
