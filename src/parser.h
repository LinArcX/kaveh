#ifndef KAVEH_PARSER_H
#define KAVEH_PARSER_H

#include "scanner.h"

typedef enum 
{
  A_ADD,
  A_SUBTRACT,
  A_MULTIPLY,
  A_DIVIDE,
  A_INTLIT
} AstNodeTypes;

struct ASTnode 
{
  int op;				
  struct ASTnode *left;	
  struct ASTnode *right;
  int intvalue;			
};

struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(Token* token);
int interpretAST(struct ASTnode *n);

#endif
