#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MONTH_COLS 20
#define GAP "  "  // gap between month blocks

static const char *MONTH_NAMES[12] = {
    "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};

static int is_leap(int y) {
    return (y%4==0 && y%100!=0) || (y%400==0);
}

static int month_len(int m, int y) {
    static const int ml[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int d = ml[m-1];
    if (m==2 && is_leap(y)) d = 29;
    return d;
}

// Sakamoto's algorithm: 0=Sunday, ... 6=Saturday
static int weekday(int y, int m, int d) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (m < 3) y -= 1;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

static void center_text(char *out, int width, const char *text) {
    int len = (int)strlen(text);
    if (len >= width) { strncpy(out, text, width); out[width] = '\0'; return; }
    int left = (width - len) / 2;
    int i = 0;
    for (; i < left; ++i) out[i] = ' ';
    memcpy(out + left, text, len);
    for (i = left + len; i < width; ++i) out[i] = ' ';
    out[width] = '\0';
}

static void month_header(char *out, int m, int y, int monday_first) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%s %d", MONTH_NAMES[m-1], y);
    center_text(out, MONTH_COLS, buf);
}

static void weekday_header(char *out, int monday_first) {
    const char *sun = "Su Mo Tu We Th Fr Sa";
    const char *mon = "Mo Tu We Th Fr Sa Su";
    snprintf(out, MONTH_COLS+1, "%s", monday_first ? mon : sun);
}

// Fill a 6xMONTH_COLS array of lines for the month (dates only)
static void build_month_block(int m, int y, int monday_first, char lines[6][MONTH_COLS+1]) {
    int first_w = weekday(y, m, 1); // 0=Sun
    int days = month_len(m, y);

    // compute starting column index (0..6) based on header order
    int start = monday_first ? (first_w == 0 ? 6 : first_w - 1) : first_w;

    // Clear lines
    for (int r=0; r<6; ++r) {
        for (int c=0; c<MONTH_COLS; ++c) lines[r][c] = ' ';
        lines[r][MONTH_COLS] = '\0';
    }

    // place day numbers in 2-wide fields separated by one space -> width 20 fits "XX " * 7 minus last space
    // layout columns at positions: 0,3,6,9,12,15,18 (2 digits starting at those)
    auto int colpos[7] = {0,3,6,9,12,15,18};
    int w = start, r = 0;
    for (int d=1; d<=days; ++d) {
        if (r >= 6) break;
        int col = colpos[w];
        if (d < 10) {
            lines[r][col] = ' ';
            lines[r][col+1] = '0' + d;
        } else {
            lines[r][col] = '0' + (d/10);
            lines[r][col+1] = '0' + (d%10);
        }
        // put space after each number (already spaces)
        w++;
        if (w == 7) { w = 0; r++; }
    }
}

// Print a single month (title + weekdays + up to 6 weeks)
static void print_single_month(int m, int y, int monday_first) {
    char title[MONTH_COLS+1], wdh[MONTH_COLS+1];
    char weeks[6][MONTH_COLS+1];

    month_header(title, m, y, monday_first);
    weekday_header(wdh, monday_first);
    build_month_block(m, y, monday_first, weeks);

    printf(" %s\n", title);
    printf(" %s\n", wdh);
    for (int r=0; r<6; ++r) {
        // trim trailing spaces for a slightly cleaner look
        int end = MONTH_COLS-1;
        while (end >= 0 && weeks[r][end] == ' ') end--;
        if (end < 0) { puts(""); continue; }
        weeks[r][end+1] = '\0';
        printf(" %s\n", weeks[r]);
    }
}

// Print 3 months in a row
static void print_three_months_row(int m1, int y1, int m2, int y2, int m3, int y3, int monday_first) {
    char title1[MONTH_COLS+1], title2[MONTH_COLS+1], title3[MONTH_COLS+1];
    char wdh1[MONTH_COLS+1], wdh2[MONTH_COLS+1], wdh3[MONTH_COLS+1];
    char wk1[6][MONTH_COLS+1], wk2[6][MONTH_COLS+1], wk3[6][MONTH_COLS+1];

    month_header(title1, m1, y1, monday_first);
    month_header(title2, m2, y2, monday_first);
    month_header(title3, m3, y3, monday_first);
    weekday_header(wdh1, monday_first);
    weekday_header(wdh2, monday_first);
    weekday_header(wdh3, monday_first);
    build_month_block(m1, y1, monday_first, wk1);
    build_month_block(m2, y2, monday_first, wk2);
    build_month_block(m3, y3, monday_first, wk3);

    printf(" %s" GAP "%s" GAP "%s\n", title1, title2, title3);
    printf(" %s" GAP "%s" GAP "%s\n", wdh1, wdh2, wdh3);
    for (int r=0; r<6; ++r) {
        // print each week's line; they already have fixed width
        printf(" %s" GAP "%s" GAP "%s\n", wk1[r], wk2[r], wk3[r]);
    }
}

// Print a whole year in a 3x4 grid
static void print_year(int y, int monday_first) {
    char header[64];
    snprintf(header, sizeof(header), "%d", y);
    char centered[MONTH_COLS*3 + 2*strlen(GAP) + 1];
    center_text(centered, MONTH_COLS*3 + 2*(int)strlen(GAP), header);
    printf(" %s\n\n", centered);

    for (int row = 0; row < 4; ++row) {
        int m1 = row*3 + 1, m2 = m1 + 1, m3 = m1 + 2;
        print_three_months_row(m1, y, m2, y, m3, y, monday_first);
        if (row != 3) puts("");
    }
}

static void adjust_month(int *m, int *y, int delta) {
    int mm = *m + delta;
    int yy = *y;
    while (mm < 1) { mm += 12; yy -= 1; }
    while (mm > 12) { mm -= 12; yy += 1; }
    *m = mm; *y = yy;
}

static void usage(const char *prog) {
    fprintf(stderr,
        "Usage:\n"
        "  %s [-m] [-3]\n"
        "  %s [-m] YEAR\n"
        "  %s [-m] [-3] MONTH YEAR\n"
        "Options:\n"
        "  -m   Monday-first week (default Sunday-first)\n"
        "  -3   Show prev/this/next months in one row (month view)\n",
        prog, prog, prog);
}

int main(int argc, char **argv) {
    int monday_first = 0;
    int three = 0;
    int pos = 1;

    // parse flags
    while (pos < argc && argv[pos][0] == '-') {
        if (strcmp(argv[pos], "-m") == 0) monday_first = 1;
        else if (strcmp(argv[pos], "-3") == 0) three = 1;
        else { usage(argv[0]); return 1; }
        pos++;
    }

    // get current date
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    int cur_y = lt->tm_year + 1900;
    int cur_m = lt->tm_mon + 1;

    if (argc - pos == 0) {
        // no args: current month (or -3 current-centered)
        if (three) {
            int pm=cur_m, py=cur_y, nm=cur_m, ny=cur_y;
            adjust_month(&pm, &py, -1);
            adjust_month(&nm, &ny, +1);
            print_three_months_row(pm, py, cur_m, cur_y, nm, ny, monday_first);
        } else {
            print_single_month(cur_m, cur_y, monday_first);
        }
        return 0;
    } else if (argc - pos == 1) {
        // YEAR
        int y = atoi(argv[pos]);
        if (y <= 0) { usage(argv[0]); return 1; }
        print_year(y, monday_first);
        return 0;
    } else if (argc - pos == 2) {
        // MONTH YEAR
        int m = atoi(argv[pos]);
        int y = atoi(argv[pos+1]);
        if (m < 1 || m > 12 || y <= 0) { usage(argv[0]); return 1; }
        if (three) {
            int pm=m, py=y, nm=m, ny=y;
            adjust_month(&pm, &py, -1);
            adjust_month(&nm, &ny, +1);
            print_three_months_row(pm, py, m, y, nm, ny, monday_first);
        } else {
            print_single_month(m, y, monday_first);
        }
        return 0;
    } else {
        usage(argv[0]);
        return 1;
    }
}
