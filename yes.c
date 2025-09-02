#include <stdio.h>

int main(int argc, char *argv[]) {
    char *s = argc > 1 ? argv[1] : "y";
    while(1) printf("%s\n", s);
    return 0;
}
