#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>

#include "log.h"

int logging = 0;

typedef struct DateAndTime
{
	int year;
	int month;
	int day;
	int hour;
	int minutes;
	int seconds;
	int msec;
} DateAndTime;

void set_logging_on(int is_logging_on)
{
	logging = is_logging_on;
	return;
}

int is_logging_on()
{
	return logging;
}

void info(const char* format, ...) {
    // Get the current time
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* timeinfo;
    timeinfo = localtime(&tv.tv_sec);

    // Format the timestamp including milliseconds
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S.", timeinfo);

    // Print milliseconds
    char milliseconds[7];
    snprintf(milliseconds, sizeof(milliseconds), "%03ld", tv.tv_usec / 1000);

    // Print the log message with timestamp
    printf("%s%s]: ", timestamp, milliseconds);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

