#ifndef COMMON_H
#define COMMON_H


extern void user_error(const char *, ...);
extern void system_error(const char *);

extern void * xmalloc(size_t num_bytes);
extern void * xrealloc(void *ptr, size_t num_bytes);


#endif
