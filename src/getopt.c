#include "getopt.h"
#include <stdio.h>
#include "types.h"

char* optarg;
int optind = 1, opterr = 1, optopt;

usize optflag, optpos;

int getopt(int argc, char* argv[], const char* optstring) {
	optarg = null;

	while (optind < argc) {
		char* arg = argv[optind];
		int flag;
		char ch;

		bool found = false;
		int needs_arg = 0;

		if (!optflag) {
			if (arg[0] == '-') {
				if (arg[1] == '-' && arg[2] == '\0') {
					optind++;
					break;
				}
				if (arg[1] != '\0') {
					// Shift the positional arguments.
					char** p = &argv[optind - 1];
					for (usize i = 0; i < optpos; i++) {
						char* tmp = p[1];
						p[1] = p[0];
						p[0] = tmp;
						p--;
					}
					// Start to consume flags.
					optflag++;
				}
			}
			if (!optflag) {
				optind++;
				optpos++;
				continue;
			}
		}

		flag = arg[optflag++];
		if (flag == '\0') {
			optind++;
			optflag = 0;
			continue;
		}

		for (usize i = 0; (ch = optstring[i]) != '\0'; i++) {
			if (ch == flag) {
				found = true;
				if (optstring[i + 1] == ':') {
					if (optstring[i + 2] != ':') {
						needs_arg = 1;
					} else {
						needs_arg = 2;
					}
				}
				break;
			}
		}

		if (!found) {
			optopt = flag;
			flag = '?';
			if (opterr) {
				fprintf(stderr, "%s: error: invalid option '%c'\n", argv[0],
						optopt);
			}
		}

		if (needs_arg != 0) {
			if (arg[optflag] != '\0') {
				optarg = arg + optflag;
			} else if (needs_arg == 1 && optind + 1 < argc) {
				optarg = argv[++optind];
			} else if (needs_arg == 1) {
				optopt = flag;
				flag = '?';
				if (opterr) {
					fprintf(stderr,
							"%s: error: option requires an argument '%c'\n",
							argv[0], optopt);
				}
			}
			optind++;
			optflag = 0;
		}

		return flag;
	}
	return -1;
}

void getopt_reset(void) {
	optind = 1;
	optflag = optpos = 0;
}