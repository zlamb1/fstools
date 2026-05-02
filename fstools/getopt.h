#ifndef FSTOOLS_GETOPT_H
#define FSTOOLS_GETOPT_H 1

extern char* optarg;
extern int optind, opterr, optopt;
extern void (*opterrcb)(const char* fmt, ...);

int getopt(int argc, char* argv[], const char* optstring);
void getopt_reset(void);

#endif