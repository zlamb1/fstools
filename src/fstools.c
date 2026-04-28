#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getopt.h"
#include "types.h"

typedef struct {
	const char* name;
	void (*fn)(int argc, char* argv[]);
} command;

command commands[] = {
	{.name = "cat"}, {.name = "cp"}, {.name = "ls"},	{.name = "mkdir"},
	{.name = "mv"},	 {.name = "rm"}, {.name = "rmdir"}, {.name = "touch"},
};

void error(int argc, char* argv[], const char* fmt, ...) {
	const char* name = argc ? argv[0] : "fstools";
	va_list args;

	fprintf(stderr, "%s: \033[1;31merror: \033[0m", name);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	exit(1);
}

int main(int argc, char* argv[]) {
	int flag;

	while ((flag = getopt(argc, argv, "")) > -1) {
	}

	if (optind == argc) {
		fprintf(stderr, "Usage: %s [COMMAND] [ARGS]...\n\n", argv[0]);
		fprintf(stderr, "COMMANDS:\n");
		for (usize i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
			command command = commands[i];
			fprintf(stderr, "%s\n", command.name);
		}
		exit(1);
	} else {
		const char* name = argv[optind];
		for (usize i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
			command command = commands[i];
			if (!strcmp(name, command.name)) {
				if (command.fn == null) {
					error(argc, argv, "unimplemented");
				}
				command.fn(argc, argv);
				goto done;
			}
		}
		error(argc, argv, "unknown command '%s'", name);
		exit(1);
	}

done:
	return (0);
}