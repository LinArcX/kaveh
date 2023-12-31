#ifndef KAVEH_PARSER_H
#define KAVEH_PARSER_H

typedef enum 
{
  A_EOF = -1,
  A_ADD = 0,
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

struct ASTnode *buildASTNode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *buildASTLeaf(int op, int intvalue);
struct ASTnode *buildASTUnary(int op, struct ASTnode *left, int intvalue);

struct ASTnode *parse(void);

int interpretAST(struct ASTnode *n);

#endif
