#ifndef CMDLINE_H

typedef int fd;

typedef struct b_cmdline_opts {
	fd *files;
	int file_count;
	int usage;
	int help;
	int verbosity;
} cmdline_opts;

cmdline_opts             get_cmdline_opts(int argc, char *const *av);

static const int         verbosity_level_count = 4;
static const char *const verbosity_levels[4] = {
    "silent",
    "normal",
    "warn",
    "info",
};

#endif /* ifndef CMDLINE_H */
