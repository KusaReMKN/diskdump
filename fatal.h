#
/*
 * FATAL.H -- Re-implementation of err(3).
 */

#ifndef MKN_FATAL_H
#define MKN_FATAL_H	1

#include <stdarg.h>

void	fatal(int status, const char *fmt, ...);
void	vfatal(int status, const char *fmt, va_list ap);
void	fatalx(int status, const char *fmt, ...);
void	vfatalx(int status, const char *fmt, va_list ap);

#endif	/* !MKN_FATAL_H */
