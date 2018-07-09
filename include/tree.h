#ifndef TREE_H
#define TREE_H

#define ANSI_COLOR_BRIGHT_RED   "\x1b[91;1m"
#define ANSI_COLOR_BRIGHT_GREEN "\x1b[92;1m"
#define ANSI_COLOR_BRIGHT_BLUE  "\x1b[94;1m"
#define ANSI_COLOR_WHITE_FILE   "\x1b[0m"
#define ANSI_COLOR_RESET        "\x1b[0m"

typedef enum {false, true} bool;

extern void read_input(int, char *[]);
extern void read_and_serve_stream(const char *, int);

extern void sort_alphabeticly(int, char *[], const char *, int);
extern int greater_stirng(const char *, const char *);

extern void print_list(int, char *[], const char *, int);

extern void print_amount();
extern char *current_directory();
extern int existing_directory(const char *);
extern int is_executable(const char *);

#endif

