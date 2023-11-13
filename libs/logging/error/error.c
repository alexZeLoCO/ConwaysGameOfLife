#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error(char *message, int out_code)
{
	fprintf(stderr, message);
	exit(out_code);
	return;
}
