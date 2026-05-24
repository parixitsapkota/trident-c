#ifndef FORGE_UTILS_H
#define FORGE_UTILS_H

#include <stddef.h>

void *s_malloc(size_t size);
void *s_realloc(const void *ptr, size_t new_size);
char *s_substr(const char *str, size_t start, size_t length);
char *s_read_file(const char *filename);

#endif // FORGE_UTILS_H