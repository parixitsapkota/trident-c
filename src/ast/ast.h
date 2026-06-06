#ifndef TRIDENT_AST_H
#define TRIDENT_AST_H

#include <stddef.h>

#include "../token/token.h"

typedef struct AstNode AstNode;

typedef struct {
  AstNode **nodes;
  size_t count;
  size_t capacity;
} AstCompound;

typedef struct {
  char *value;
  TokenKind kind;
} AstAtom;

typedef struct {
  char *name;
  AstCompound *args;
} AstFuncCall;

typedef struct {
  AstNode *node;
  TokenKind op;
} AstUnary;

typedef struct {
  AstNode *left;
  TokenKind op;
  AstNode *right;
} AstBinary;

typedef struct {
  bool pointer;
  char *name;
  AstCompound *args;
  char *return_type;
  AstCompound *body;
} AstFuncDecl;

typedef struct {
  bool constant;
  char *name;
  AstNode *expr;
} AstVarDecl;

typedef struct {
  bool constant;
  bool define;
  char *name;
  AstCompound *body;
} AstStion;

typedef struct {
  AstNode *condition;
  AstCompound *body;
} AstWhile;

typedef struct AstIfStmt {
  AstNode *condition;
  AstCompound *body;
  AstNode *next;
} AstIfStmt;

typedef enum {
  AST_ATOM,
  AST_FUNCTION_CALL,
  AST_UNARY,
  AST_BINARY,
  AST_EXPRESSION,
  AST_COMPOUND,
  AST_FUNCTION_DECL,
  AST_VAR_DECL,
  AST_STRUCT,
  AST_UNION,
  AST_LOOP,
  AST_WHILE,
  AST_IF_STMT,
  AST_ELSE_IF_STMT,
  AST_ELSE_STMT,
  AST_RETURN,
  AST_BREAK,
  AST_CONTINUE,
} AstKind;

struct AstNode {
  AstKind kind;
  void *node;
};

AstCompound *init_ast_compound();
void push_to_ast_compound(AstCompound *self, AstNode *node);
AstAtom *ast_atom(const char *value, TokenKind kind);
AstFuncCall *ast_function_call(const char *name, AstCompound *args);
AstUnary *ast_unary(AstNode *node, TokenKind op);
AstBinary *ast_Binary(AstNode *left, TokenKind op, AstNode *right);
AstFuncDecl *ast_func_decl(bool pointer, const char *name, AstCompound *args,
                           const char *return_type, AstCompound *body);
AstVarDecl *ast_var_decl(bool constant, const char *name, AstNode *expr);
AstStion *ast_stion(bool constant, bool define, const char *name,
                    AstCompound *body);
AstWhile *ast_while(AstNode *expr, AstCompound *body);
AstIfStmt *ast_if_else_stmt(AstNode *condition, AstCompound *body,
                            AstNode *next);
AstNode *ast_node(AstKind kind, void *node);

#endif
