#include "cmdline.h"

#include "utils.h"

#define nullptr NULL
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static int strcasecmp(const char *s1, const char *s2) {
	for (;; ++s1, ++s2) {
		int d = tolower(*s1) - tolower(*s2);
		if (d || !*s1) {
			return d;
		}
	}
}

static int get_verbosity(const char *level) {
	if (!level) return 2;
	for (int i = 0; i < verbosity_level_count; ++i) {
		if (!strcasecmp(level, verbosity_levels[i])) {
			printf("verbosity => %s\n", verbosity_levels[i]);
			return i;
		}
	}
	return -1;
}

void handle_long_arg(struct option longopts[], int optind, cmdline_opts *opts) {
	switch (optind) {
		case 0:  // help
			opts->help = 1;
			break;
		case 1:  // usage
			opts->usage = 1;
			break;
		case 2:  // verbose
			opts->verbosity = get_verbosity(optarg);
			break;
		case 3:  // silent
			opts->verbosity = 0;
			break;
		case 4:  // file
			int *tmp = realloc(opts->files,
					   sizeof(int) * ++opts->file_count);
			if (!tmp) panic("malloc failed");
			opts->files = tmp;
			opts->files[opts->file_count - 1]
			    = open(optarg, O_RDONLY);
			if (opts->files[opts->file_count - 1] == -1)
				panic("failed to open file");
			break;
		default: break;
	}
	printf("options %s", longopts[optind].name);
	if (optarg) printf(" with arg %s", optarg);
	printf("\n");
}

cmdline_opts get_cmdline_opts(int ac, char *const *av) {
	static cmdline_opts      rv = {.verbosity = 0};
	static const char *const optstring = "hf:v::s";
	static struct option     longopts[]
	    = {{"help", no_argument, &rv.help, 1},
	       {"usage", no_argument, &rv.usage, 1},
	       {"verbose", optional_argument, &rv.verbosity, 1},
	       {"silent", no_argument, &rv.verbosity, 0},
	       {"file", required_argument, &rv.verbosity, 0},
	       {nullptr, no_argument, nullptr, 0}};

	int option_index = 0;
	int c = 0;
	rv.files = realloc(nullptr, sizeof(int) * rv.file_count);
	while ((c = getopt_long(ac, av, optstring, longopts, &option_index))
	       != -1) {
		switch (c) {
			case 0:
				handle_long_arg(longopts, option_index, &rv);
				break;
			case 's': rv.verbosity = 0; break;
			case 'v':
				rv.verbosity = get_verbosity(optarg);
				printf("verbosity: %i\n", rv.verbosity);
				break;
			case 'f': rv.file_count++; break;
			case '?':
			default : break;
		}
	}

	if (optind < ac) {
		printf("non-option values passed to program: ");
		while (optind < ac) printf("%s ", av[optind++]);
		printf("\n");
	}
	return rv;
}
