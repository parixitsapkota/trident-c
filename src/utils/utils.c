#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *s_malloc(const size_t size) {
  void *ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "Memory allocation failed for size %zu\n", size);
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void *s_realloc(const void *ptr, const size_t new_size) {
  void *new_ptr = realloc((void *)ptr, new_size);
  if (!new_ptr) {
    fprintf(stderr, "Memory reallocation failed for size %zu\n", new_size);
    exit(EXIT_FAILURE);
  }
  return new_ptr;
}

char *s_substr(const char *str, const size_t start, const size_t length) {
  char *substr = s_malloc(length + 1);
  strncpy(substr, str + start, length);
  substr[length] = '\0';
  return substr;
}

char *s_read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Failed to open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = s_malloc(file_size + 1);

  fread(content, 1, file_size, file);
  content[file_size] = '\0';

  fclose(file);
  return content;
}