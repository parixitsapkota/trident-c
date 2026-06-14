#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../SHI/shi_file.h"
#include "lexer/lexer.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "USAGE : %s <filename>", argv[0]);
    exit(1);
  }

  char *buffer = shi_file_read(argv[1], NULL);

  Token *tokens = lexer(buffer);

  free(buffer);

  return 0;
}
