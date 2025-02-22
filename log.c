#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void 
debug(const char *fmt, ...)
{
#ifdef DEBUG
	va_list args;
	static char format[1024];

	(void) sprintf(format, "DEBUG: %s\n", fmt);

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
#endif /* DEBUG */
}

void 
warn(const char *fmt, ...)
{
	va_list args;
	static char format[1024];

	(void) sprintf(format, "WARN: %s\n", fmt);

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

void 
error(const char *fmt, ...)
{
	va_list args;
	static char format[1024];

	(void) sprintf(format, "ERROR: %s\n", fmt);

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

void 
fatal(const char *fmt, ...)
{
	va_list args;
	static char format[1024];

	(void) sprintf(format, "FATAL: %s\n", fmt);

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

	(void) exit(0);
}
