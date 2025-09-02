SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=.exe)
CC = tcc
CFLAGS =
LDFLAGS_whoami = -ladvapi32

all: $(TARGETS)

# Special rule for whoami.exe
whoami.exe: whoami.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_whoami)

# General rule for all other .c files
%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all