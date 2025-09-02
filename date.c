#include <stdio.h>
#include <time.h>
#include <string.h>

// Simple date utility for Windows (compilable with TCC)
int main(int argc, char *argv[]) {
    time_t now;
    struct tm *t;
    char buffer[128];

    time(&now);
    t = localtime(&now);

    if (argc == 1) {
        // Default format (like Linux date output)
        strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", t);
        printf("%s\n", buffer);
    } else if (argc == 2 && argv[1][0] == '+') {
        // Custom format: date +FORMAT
        // Example: date +%Y-%m-%d
        if (strftime(buffer, sizeof(buffer), argv[1] + 1, t) == 0) {
            fprintf(stderr, "Format too long or invalid\n");
            return 1;
        }
        printf("%s\n", buffer);
    } else {
        fprintf(stderr, "Usage: %s [+FORMAT]\n", argv[0]);
        return 1;
    }

    return 0;
}
