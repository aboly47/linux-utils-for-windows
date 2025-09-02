#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utime.h> //for utime (file timestamp update)
#include <io.h> //for access(), open(), close()
#include <fcntl.h>
#include <sys/stat.h>

#ifndef S_IRUSR
#define S_IRUSR _S_IREAD
#endif
#ifndef S_IWUSR
#define S_IWUSR S_IWRITE
#endif

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	const char *filename = argv[1];

	if (utime(filename, NULL) == 0) {
		return 0;
	}

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		fprintf(stderr, "touch: cannot create file '%s'\n", filename);
		return 1;
	}

	close(fd);
	utime(filename, NULL);
	return 0;
}