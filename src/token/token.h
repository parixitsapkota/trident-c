#ifndef ANVIL_TOKEN_H
#define ANVIL_TOKEN_H

#include <stddef.h>

typedef enum {
  // Helper_Tokens
  END_OF_TOKEN,
  UNKNOWN,
  // Literals
  INT,
  FLOAT,
  STRING,
  // Qualifier
  PUB,
  EXTERN,
  CONST,
  VOLATILE,
  // Function
  FUNC,
  RET,
  // Conditional
  IF,
  ELSE,
  // Loop
  LOOP,
  WHILE,
  // Signed_Int
  I8,
  I16,
  I32,
  I64,
  I128,
  // Unsigned_Int
  U8,
  U16,
  U32,
  U64,
  U128,
  // Float
  F16,
  F32,
  F64,
  F128,
  // Struct And Union
  STRUCT,
  UNION,
  // Enumerator
  ENUM,
  ERROR,
  // Pointers
  PTR,
  DREF,
  // Directive
  TYPEOF,
  DEFINE,
  IMPORT,
  // Seperator
  O_BRACE,
  C_BRACE,
  O_PREN,
  C_PREN,
  O_BRACKET,
  C_BRACKET,
  COMMA,
  COLN,
  SEMICOLN,
  // Adative
  PLUS,
  DASH,
  STAR,
  SLASH,
  PERCENT,
  // Adative
  ASSIGN,
  PLUS_ASSIGN,
  DASH_ASSIGN,
  STAR_ASSIGN,
  SLASH_ASSIGN,
  PERCENT_ASSIGN,
  // Unary
  INCREMENT,
  DECREMENT,
  NEGATE,
  // Logical
  AND,
  OR,
  // Shift
  SHIFT_LEFT,
  SHIFT_RIGHT,
  // Compare
  EQUAL,
  NOT_EQUAL,
  LESSER,
  GREATER,
  LESSER_EQUAL,
  GREATER_EQUAL,
} TokenKind;
char *token_kind_to_str(TokenKind kind);

typedef struct {
  TokenKind kind;
  char *value;
  size_t line;
  size_t col;
} Token;
void print_tokens(const Token *tokens);

typedef enum {
  END_OF_LEX_ERR,
  UNTERMINATED_STRING,
  UNKNOWN_TOKEN,
  UNKNOWN_DIRECTIVE,
} LexerErrorKind;
char *lexer_error_kind_to_string(LexerErrorKind kind);

typedef struct {
  LexerErrorKind kind;
  size_t token;
} LexerError;

typedef struct {
  Token *tokens;
  LexerError *errors;
  size_t token_capacity;
  size_t token_count;
  size_t error_capacity;
  size_t error_count;
} TokenUnion;
void print_lexer_errors(const TokenUnion *self);
void add_token(TokenUnion *self, TokenKind kind, const char *value, size_t line,
               size_t col);
void add_lexer_errors(TokenUnion *self, LexerErrorKind error_code,
                      size_t token);

#endif // ANVIL_TOKEN_H
