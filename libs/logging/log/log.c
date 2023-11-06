#include <stdio.h>
#include <stdlib.h>

#include "log.h"

int logging = 0;

void set_logging_on (int is_logging_on)
{
	logging = is_logging_on;
	return;
}

int is_logging_on ()
{
	return logging;
}

void info (const char* message, ...)
{
	if (is_logging_on()) printf(message);
	return;
}

