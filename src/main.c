#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"
#include "utils/utils.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "USAGE : %s <filename>", argv[0]);
    exit(1);
  }

  char *buffer = s_read_file(argv[1]);

  printf("%s\n", buffer);

  lexer(buffer);

  free(buffer);

  return 0;
}
