#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    if(argc < 2){ fprintf(stderr,"Usage: %s COMMAND\n",argv[0]); return 1; }

    while(1){
        system("cls");
        system(argv[1]);
        Sleep(2000);
    }
    return 0;
}
