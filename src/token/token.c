#include "token.h"
#include "../utils/utils.h"
#include <stddef.h>
#include <stdio.h>

#define tokstr(x)                                                              \
  case x:                                                                      \
    return #x
char *token_kind_to_str(const TokenKind kind) {
  switch (kind) {
    tokstr(END_OF_TOKEN);
    tokstr(UNKNOWN);
    tokstr(INT);
    tokstr(FLOAT);
    tokstr(STRING);
    tokstr(PUB);
    tokstr(EXTERN);
    tokstr(CONST);
    tokstr(VOLATILE);
    tokstr(FUNC);
    tokstr(RET);
    tokstr(IF);
    tokstr(ELSE);
    tokstr(LOOP);
    tokstr(WHILE);
    tokstr(I8);
    tokstr(I16);
    tokstr(I32);
    tokstr(I64);
    tokstr(I128);
    tokstr(U8);
    tokstr(U16);
    tokstr(U32);
    tokstr(U64);
    tokstr(U128);
    tokstr(F16);
    tokstr(F32);
    tokstr(F64);
    tokstr(F128);
    tokstr(STRUCT);
    tokstr(UNION);
    tokstr(ENUM);
    tokstr(ERROR);
    tokstr(PTR);
    tokstr(DREF);
    tokstr(TYPEOF);
    tokstr(DEFINE);
    tokstr(IMPORT);
    tokstr(O_BRACE);
    tokstr(C_BRACE);
    tokstr(O_PREN);
    tokstr(C_PREN);
    tokstr(O_BRACKET);
    tokstr(C_BRACKET);
    tokstr(COMMA);
    tokstr(COLN);
    tokstr(SEMICOLN);
    tokstr(PLUS);
    tokstr(DASH);
    tokstr(STAR);
    tokstr(SLASH);
    tokstr(PERCENT);
    tokstr(ASSIGN);
    tokstr(PLUS_ASSIGN);
    tokstr(DASH_ASSIGN);
    tokstr(STAR_ASSIGN);
    tokstr(SLASH_ASSIGN);
    tokstr(PERCENT_ASSIGN);
    tokstr(INCREMENT);
    tokstr(DECREMENT);
    tokstr(NEGATE);
    tokstr(AND);
    tokstr(OR);
    tokstr(SHIFT_LEFT);
    tokstr(SHIFT_RIGHT);
    tokstr(EQUAL);
    tokstr(NOT_EQUAL);
    tokstr(LESSER);
    tokstr(GREATER);
    tokstr(LESSER_EQUAL);
    tokstr(GREATER_EQUAL);
  default:
    return "UNKNOWN_TOKEN";
  }
}

void add_token(TokenUnion *self, TokenKind kind, const char *value,
               const size_t line, const size_t col) {
  if (!self) {
    self = s_malloc(sizeof(Token) * 512);
    self->token_capacity = sizeof(Token) * 512;
  } else if (self->token_capacity <= self->token_count) {
    self = s_realloc(self, self->token_capacity + sizeof(Token) * 512);
    self->token_capacity += sizeof(Token) * 512;
  }
  self->tokens[self->token_count] = (Token){kind, (char *)value, line, col};
  ++self->token_count;
}

void print_tokens(const Token *tokens) {
  for (size_t i = 0; tokens[i].kind != END_OF_TOKEN; ++i) {
    char *kind = token_kind_to_str(tokens[i].kind);
    printf("%-15s : %lu:%lu\t%s\n", kind, tokens[i].line, tokens[i].col,
           tokens[i].value);
  }
}

char *lexer_error_kind_to_string(const LexerErrorKind kind) {
  switch (kind) {
  case END_OF_LEX_ERR:
    return NULL;
  case UNTERMINATED_STRING:
    return "Unterminated Sstring";
  case UNKNOWN_TOKEN:
    return "Unknown Token";
  case UNKNOWN_DIRECTIVE:
    return "Unknown Directive";
  default:
    return "Unknown Lexer Error Code!";
  }
}

void add_lexer_errors(TokenUnion *self, const LexerErrorKind code,
                      const size_t token) {
  if (!self) {
    self = s_malloc(sizeof(LexerError) * 5);
    self->error_capacity = sizeof(LexerError) * 5;
  } else if (self->error_capacity <= self->error_count) {
    self = s_realloc(self, self->error_capacity + sizeof(LexerError) * 5);
    self->error_capacity += sizeof(Token) * 5;
  }
  self->errors[self->error_count] = (LexerError){code, token};
  ++self->error_count;
}

void print_lexer_errors(const TokenUnion *self) {
  for (size_t i = 0; self->errors[i].kind != END_OF_LEX_ERR; ++i) {
    char *msg = lexer_error_kind_to_string(self->errors[i].kind);
    size_t line = self->tokens[self->errors[i].token].line;
    size_t col = self->tokens[self->errors[i].token].line;
    fprintf(stderr, "%s at %lu:%lu\n", msg, line, col);
  }
}
