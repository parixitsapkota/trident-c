#include "ast.h"

#define alloc_ast_comp 10

AstCompound *init_ast_compound() {
  AstCompound *node = s_malloc(sizeof(AstCompound));
  if (node) {
    *node = (AstCompound){NULL, 0, alloc_ast_comp};
  }
  return node;
}

void push_to_ast_compound(AstCompound *self, AstNode *node) {
  if (!self->nodes) {
    self->capacity = alloc_ast_comp;
    self->nodes = s_malloc(sizeof(AstNode *) * self->capacity);
  } else if (self->capacity <= self->count) {
    self->capacity += alloc_ast_comp;
    self->nodes = s_realloc(self->nodes, sizeof(AstNode *) * self->capacity);
  }
  self->nodes[self->count] = node;
  ++self->count;
}

AstAtom *ast_atom(const char *value, TokenKind kind) {
  AstAtom *node = s_malloc(sizeof(AstAtom));
  *node = (AstAtom){(char *)value, kind};
  return node;
}

AstFuncCall *ast_function_call(const char *name, AstCompound *args) {
  AstFuncCall *node = s_malloc(sizeof(AstFuncCall));
  *node = (AstFuncCall){(char *)name, args};
  return node;
}

AstUnary *ast_unary(AstNode *node, TokenKind op) {
  AstUnary *node_ = s_malloc(sizeof(AstUnary));
  *node_ = (AstUnary){node, op};
  return node_;
}

AstBinary *ast_Binary(AstNode *left, TokenKind op, AstNode *right) {
  AstBinary *node = s_malloc(sizeof(AstBinary));
  *node = (AstBinary){left, op, right};
  return node;
}

AstFuncDecl *ast_func_decl(bool pointer, const char *name, AstCompound *args,
                           const char *return_type, AstCompound *body) {
  AstFuncDecl *node = s_malloc(sizeof(AstFuncDecl));
  *node = (AstFuncDecl){pointer, (char *)name, args, (char *)return_type, body};
  return node;
}

AstVarDecl *ast_var_decl(bool constant, const char *name, AstNode *expr) {
  AstVarDecl *node = s_malloc(sizeof(AstVarDecl));
  *node = (AstVarDecl){constant, (char *)name, expr};
  return node;
}

AstStion *ast_stion(bool constant, bool define, const char *name,
                    AstCompound *body) {
  AstStion *node = s_malloc(sizeof(AstStion));
  *node = (AstStion){constant, define, (char *)name, body};
  return node;
}

AstWhile *ast_while(AstNode *expr, AstCompound *body) {
  AstWhile *node = s_malloc(sizeof(AstWhile));
  *node = (AstWhile){expr, body};
  return node;
}

AstIfStmt *ast_if_else_stmt(AstNode *condition, AstCompound *body,
                            AstNode *next) {
  AstIfStmt *node = s_malloc(sizeof(AstIfStmt));
  *node = (AstIfStmt){condition, body, next};
  return node;
}

AstNode *ast_node(AstKind kind, void *node) {
  AstNode *node_ = s_malloc(sizeof(AstNode));
  *node_ = (AstNode){kind, node};
  return node_;
}
