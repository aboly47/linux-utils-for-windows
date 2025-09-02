# Force make to use cmd.exe instead of bash because fuck me.
SHELL = cmd.exe

# Compiler and flags
CC = tcc
CFLAGS =
OUTDIR = lufw

# Find all .c files
SRCS := $(wildcard *.c)
TARGETS := $(SRCS:.c=.exe)
TARGETS := $(addprefix $(OUTDIR)/, $(TARGETS))

# Default goal
all: $(OUTDIR) $(TARGETS)

# Create output directory if it doesn't exist
$(OUTDIR):
	if not exist "$(OUTDIR)" mkdir "$(OUTDIR)"

# Default rule for compiling .c files
$(OUTDIR)/%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

$(OUTDIR)/whoami.exe: whoami.c
	$(CC) $(CFLAGS) $< -ladvapi32 -o $@

.PHONY: all clean

clean:
	del /Q $(OUTDIR)\*.exe
	rmdir $(OUTDIR)