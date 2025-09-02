#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000
#define LINE_LEN 1024

int cmp(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main(int argc, char *argv[]) {
    if(argc < 2){ fprintf(stderr,"Usage: %s FILE\n",argv[0]); return 1; }

    FILE *f = fopen(argv[1],"r");
    if(!f){ perror(argv[1]); return 1; }

    char *lines[MAX_LINES];
    int count=0;
    char buffer[LINE_LEN];
    while(fgets(buffer,sizeof(buffer),f) && count<MAX_LINES) {
        lines[count++] = strdup(buffer);
    }
    fclose(f);

    qsort(lines,count,sizeof(char*),cmp);
    for(int i=0;i<count;i++){ printf("%s",lines[i]); free(lines[i]); }

    return 0;
}
