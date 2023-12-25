#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "scanner.h"

// Build and return a generic AST node
struct ASTnode* 
mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) 
{
  struct ASTnode *n;

  // Malloc a new ASTnode
  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (n == NULL) 
  {
    fprintf(stderr, "Unable to malloc in mkastnode()\n");
    exit(1);
  }
  // Copy in the field values and return it
  n->op = op;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}

// Make an AST leaf node
struct ASTnode* 
mkastleaf(int op, int intvalue) 
{
  return (mkastnode(op, NULL, NULL, intvalue));
}

// Make a unary AST node: only one child
struct ASTnode*
mkastunary(int op, struct ASTnode *left, int intvalue) 
{
  return (mkastnode(op, left, NULL, intvalue));
}


// List of AST operators
static char *ASTop[] = { "+", "-", "*", "/" };

// Given an AST, interpret the
// operators in it and return
// a final value.
int
interpretAST(struct ASTnode *n) 
{
  int leftval, rightval;

  // Get the left and right sub-tree values
  if (n->left)
    leftval = interpretAST(n->left);
  if (n->right)
    rightval = interpretAST(n->right);

  // Debug: Print what we are about to do
  if (n->op == A_INTLIT)
    printf("int %d\n", n->intvalue);
  else
    printf("%d %s %d\n", leftval, ASTop[n->op], rightval);

  switch (n->op) {
    case A_ADD:
      return (leftval + rightval);
    case A_SUBTRACT:
      return (leftval - rightval);
    case A_MULTIPLY:
      return (leftval * rightval);
    case A_DIVIDE:
      return (leftval / rightval);
    case A_INTLIT:
      return (n->intvalue);
    default:
      fprintf(stderr, "Unknown AST operator %d\n", n->op);
      exit(1);
  }
}

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode*
primary(Token* token) 
{
  struct ASTnode *n;

  // For an INTLIT token, make a leaf AST node for it
  // and scan in the next token. Otherwise, a syntax error
  // for any other token type.
  switch (token->type) {
    case TOKEN_INTEGER:
      n = mkastleaf(A_INTLIT, token->literal.integer);
      scan(token);
      return (n);
    default:
      fprintf(stderr, "syntax error on line %d\n", line);
      exit(1);
  }
}


// Convert a token into an AST operation.
int 
arithop(int tok) 
{
  switch (tok) {
    case TOKEN_PLUS:
      return (A_ADD);
    case TOKEN_MINUS:
      return (A_SUBTRACT);
    case TOKEN_STAR:
      return (A_MULTIPLY);
    case TOKEN_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithop() on line %d\n", line);
      exit(EXIT_FAILURE);
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *
binexpr(Token* token) 
{
  struct ASTnode *n, *left, *right;
  int nodetype;

  // Get the integer literal on the left.
  // Fetch the next token at the same time.
  left = primary(token);

  // If no tokens left, return just the left node
  if (token->type == TOKEN_EOF)
    return (left);

  // Convert the token into a node type
  nodetype = arithop(token->type);

  // Get the next token in
  scan(token);

  // Recursively get the right-hand tree
  right = binexpr(token);

  // Now build a tree with both sub-trees
  n = mkastnode(nodetype, left, right, 0);
  return (n);
}
