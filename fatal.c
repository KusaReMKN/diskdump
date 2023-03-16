#
/*
 * FATAL.C -- Re-implementation of err(3).
 */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fatal.h"

extern char	**__argv;

void
fatal(int status, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfatal(status, fmt, ap);
	va_end(ap);
}

void
vfatal(int status, const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", __argv[0]);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
	}
	fprintf(stderr, "%s\n", strerror(errno));
	exit(status);
}

void
fatalx(int status, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfatalx(status, fmt, ap);
	va_end(ap);
}

void
vfatalx(int status, const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", __argv[0]);
	if (fmt != NULL)
		vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(status);
}
