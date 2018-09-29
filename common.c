/*
 * Supporting functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "include/common.h"

void user_error(const char *e, ...)
{
	va_list(args);
	va_start(args, e);
	vprintf(e, args);
	va_end(args);
	printf("\n");
	exit(EXIT_FAILURE);
}

void system_error(const char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void * xmalloc(size_t num_bytes)
{
	void *ptr = malloc(num_bytes);
	if(!ptr)
		system_error("xmalloc error");
	return(ptr);
}

void * xrealloc(void *ptr, size_t num_bytes)
{
	ptr = realloc(ptr, num_bytes);
	if(!ptr)
		system_error("xrealloc error");
	return(ptr);
}
