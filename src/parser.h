#ifndef KAVEH_PARSER_H
#define KAVEH_PARSER_H

typedef enum 
{
  A_EOF = 0,
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

struct ASTnode *buildASTNode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *buildASTLeaf(int op, int intvalue);
struct ASTnode *buildASTUnary(int op, struct ASTnode *left, int intvalue);

struct ASTnode *parseExpressions(int precedence);

int interpretAST(struct ASTnode *n);
void statements(void);

#endif
