#include <stdio.h>

#include "cmdline.h"

int main([[maybe_unused]] int ac, [[maybe_unused]] char **av) {
	printf("Hello, World!\n");

	[[maybe_unused]]
	cmdline_opts opts = get_cmdline_opts(ac, av);

	return 0;
}
