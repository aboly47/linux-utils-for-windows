#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 3) { fprintf(stderr,"Usage: %s SET1 SET2\n",argv[0]); return 1; }

    char c;
    while((c=getchar())!=EOF) {
        char *pos = strchr(argv[1],c);
        if(pos) {
            int index = pos - argv[1];
            if(index < strlen(argv[2])) putchar(argv[2][index]);
        } else {
            putchar(c);
        }
    }
    return 0;
}
