#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

noreturn void panic(const char *s) {
	fprintf(stderr, "%s\n", s);
	exit(1);
}
