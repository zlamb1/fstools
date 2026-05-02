#include <assert.h>
#include <limits.h>
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

static const char* base_name = "fstools";
static const char* sub_name = NULL;

command commands[] = {
	{.name = "cat"}, {.name = "cp"},	{.name = "fsck"},
	{.name = "ls"},	 {.name = "mkdir"}, {.name = "mv"},
	{.name = "rm"},	 {.name = "rmdir"}, {.name = "touch"},
};

void error(const char* fmt, ...) {
	va_list args;
	fprintf(stderr, "%s: \033[1;31merror: ", base_name);
	if (sub_name != NULL) {
		fprintf(stderr, "\033[0;1m%s: ", sub_name);
	}
	fprintf(stderr, "\033[0m");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
	exit(1);
}

int main(int argc, char* argv[]) {
	int flag;
	char* command_name;

	if (argc)
		base_name = argv[0];

	opterrcb = error;
	opterr = 0;

	while ((flag = getopt(argc, argv, "")) > -1) {
	}

	if (optind == argc) {
		fprintf(stderr, "Usage: %s [COMMAND] [ARGS]...\n\n", base_name);
		fprintf(stderr, "COMMANDS:\n");
		for (usize i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
			command command = commands[i];
			fprintf(stderr, "%s\n", command.name);
		}
		exit(1);
	}

	command_name = argv[optind];

	{
		// Remove the subcommand from args + reset getopt.
		int i = optind + 1;
		char** pos = &argv[i];

		while (i++ < argc) {
			pos[-1] = pos[0];
			pos++;
		}

		argv[0] = command_name;
		argv[--argc] = NULL;

		getopt_reset();
	}

	for (usize i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
		command command = commands[i];
		if (!strcmp(command_name, command.name)) {
			if (command.fn == null) {
				error("unimplemented");
			}
			sub_name = command_name;
			command.fn(argc, argv);
			goto done;
		}
	}

	error("unknown command '%s'", command_name);

done:
	return (0);
}