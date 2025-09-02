#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *desc;
    const unsigned char *magic;
    size_t len;
    size_t offset;
} Magic;

Magic magics[] = {
    // --- Images ---
    {"JPEG image", (const unsigned char *)"\xFF\xD8\xFF", 3, 0},
    {"PNG image",  (const unsigned char *)"\x89PNG\r\n\x1A\n", 8, 0},
    {"GIF image",  (const unsigned char *)"GIF87a", 6, 0},
    {"GIF image",  (const unsigned char *)"GIF89a", 6, 0},
    {"BMP image",  (const unsigned char *)"BM", 2, 0},
    {"TIFF image (LE)", (const unsigned char *)"II*\0", 4, 0},
    {"TIFF image (BE)", (const unsigned char *)"MM\0*", 4, 0},
    {"ICO image",  (const unsigned char *)"\x00\x00\x01\x00", 4, 0},
    {"WebP image", (const unsigned char *)"RIFF", 4, 0},  // + "WEBP" at 8

    // --- Documents ---
    {"PDF document", (const unsigned char *)"%PDF-", 5, 0},
    {"PostScript document", (const unsigned char *)"%!", 2, 0},
    {"RTF document", (const unsigned char *)"{\\rtf", 5, 0},
    {"Microsoft OLE2 (DOC/XLS/PPT)", (const unsigned char *)"\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", 8, 0},
    {"Office OpenXML (DOCX/XLSX/PPTX)", (const unsigned char *)"PK\x03\x04", 4, 0},
    {"EPUB e-book", (const unsigned char *)"PK\x03\x04", 4, 0}, // + check mimetype file inside

    // --- Archives / Compression ---
    {"ZIP archive", (const unsigned char *)"PK\x03\x04", 4, 0},
    {"ZIP empty archive", (const unsigned char *)"PK\x05\x06", 4, 0},
    {"ZIP spanned archive", (const unsigned char *)"PK\x07\x08", 4, 0},
    {"RAR archive v1.5", (const unsigned char *)"Rar!\x1A\x07\x00", 7, 0},
    {"RAR archive v5", (const unsigned char *)"Rar!\x1A\x07\x01\x00", 8, 0},
    {"7z archive", (const unsigned char *)"7z\xBC\xAF\x27\x1C", 6, 0},
    {"GZIP compressed", (const unsigned char *)"\x1F\x8B", 2, 0},
    {"BZIP2 compressed", (const unsigned char *)"BZh", 3, 0},
    {"XZ compressed", (const unsigned char *)"\xFD""7zXZ", 6, 0},
    {"TAR archive (POSIX)", (const unsigned char *)"ustar", 5, 257},

    // --- Audio ---
    {"MP3 audio (ID3)", (const unsigned char *)"ID3", 3, 0},
    {"MP3 audio (frame)", (const unsigned char *)"\xFF\xFB", 2, 0},
    {"WAV audio", (const unsigned char *)"RIFF", 4, 0},  // + "WAVE" at 8
    {"FLAC audio", (const unsigned char *)"fLaC", 4, 0},
    {"OGG audio", (const unsigned char *)"OggS", 4, 0},
    {"MIDI audio", (const unsigned char *)"MThd", 4, 0},
    {"AIFF audio", (const unsigned char *)"FORM", 4, 0},  // + "AIFF" at 8

    // --- Video ---
    {"AVI video", (const unsigned char *)"RIFF", 4, 0},  // + "AVI " at 8
    {"MP4 video", (const unsigned char *)"ftypisom", 8, 4},
    {"MP4 video", (const unsigned char *)"ftypmp42", 8, 4},
    {"MOV video", (const unsigned char *)"ftypqt  ", 8, 4},
    {"MKV/WEBM video", (const unsigned char *)"\x1A\x45\xDF\xA3", 4, 0},
    {"FLV video", (const unsigned char *)"FLV", 3, 0},

    // --- Executables ---
    {"Windows EXE/DLL", (const unsigned char *)"MZ", 2, 0},
    {"ELF binary", (const unsigned char *)"\x7F""ELF", 4, 0},
    {"Mach-O binary (32-bit)", (const unsigned char *)"\xFE\xED\xFA\xCE", 4, 0},
    {"Mach-O binary (64-bit)", (const unsigned char *)"\xFE\xED\xFA\xCF", 4, 0},
    {"Mach-O FAT binary", (const unsigned char *)"\xCA\xFE\xBA\xBE", 4, 0},

    // --- Fonts ---
    {"TrueType font", (const unsigned char *)"\x00\x01\x00\x00", 4, 0},
    {"OpenType font", (const unsigned char *)"OTTO", 4, 0},
    {"WOFF font", (const unsigned char *)"wOFF", 4, 0},
    {"WOFF2 font", (const unsigned char *)"wOF2", 4, 0},

    {NULL, NULL, 0, 0}
};

const char *detect_file(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return "Cannot open file";

    unsigned char buf[512];
    size_t n = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    if (n == 0) return "Empty file";

    for (int i = 0; magics[i].desc; i++) {
        if (n >= magics[i].offset + magics[i].len &&
            memcmp(buf + magics[i].offset, magics[i].magic, magics[i].len) == 0) {
            return magics[i].desc;
        }
    }

    // fallback: text vs binary
    int text = 1;
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == 0) { text = 0; break; }
        if (buf[i] < 7 || buf[i] > 127) { text = 0; break; }
    }
    return text ? "ASCII text" : "Unknown binary";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("%s: %s\n", argv[i], detect_file(argv[i]));
    }

    return 0;
}
