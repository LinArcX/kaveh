#include <stdlib.h>

#include "scanner.h"
#include "parser.h"
#include "kutil.h"

static const char * ASTOperators[] = { "+", "-", "*", "/" };

struct ASTnode* 
buildASTNode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) 
{
  struct ASTnode *n = {0};

  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (NULL == n) 
  {
    fprintf(stderr, "[%s, %s, %d] buildASTNode() --> Unable to malloc ASTNode!\n", errorType(ERROR_PARSER), __FILE__, __LINE__);
    return NULL;
  }

  n->op = op;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}

struct ASTnode* 
buildASTLeaf(int op, int intvalue) 
{
  return (buildASTNode(op, NULL, NULL, intvalue));
}

struct ASTnode*
buildASTUnary(int op, struct ASTnode *left, int intvalue) 
{
  return (buildASTNode(op, left, NULL, intvalue));
}

// Parse a primary factor and return an AST node representing it.
static struct ASTnode*
primary(void) 
{
  // For an INTLIT token, make a leaf AST node for it and scan in the next token. Otherwise, a syntax error for any other token type.
  if(TOKEN_INTEGER == g_token.type)
  {
    struct ASTnode * n = buildASTLeaf(A_INTLIT, g_token.literal.integer);
    scan(&g_token);
    return n;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %d] primary() --> Syntax Error on line: %d\n", errorType(ERROR_PARSER), __FILE__, __LINE__, line);
  }
  return NULL;
}

int 
scannerTypeToParserType(int token) 
{
  if(TOKEN_PLUS == token)
  {
    return A_ADD;
  }
  else if(TOKEN_MINUS == token)
  {
    return A_SUBTRACT;
  }
  else if(TOKEN_STAR == token)
  {
    return A_MULTIPLY;
  }
  else if(TOKEN_SLASH == token)
  {
    return A_DIVIDE;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %d] scannerTypeToParserType() --> unknown token: %d on line %d\n", errorType(ERROR_PARSER), __FILE__, __LINE__, token, line);
    return -2;
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *
parse(void) 
{
  int parserNodeType;
  struct ASTnode *n = {0};
  struct ASTnode *left = {0};
  struct ASTnode *right = {0};

  // Get the integer literal on the left. Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  if (g_token.type == TOKEN_EOF)
  {
    return left;
  }

  parserNodeType = scannerTypeToParserType(g_token.type);
  if(parserNodeType >= -1)
  {
    scan(&g_token);
    right = parse();
    n = buildASTNode(parserNodeType, left, right, 0);
  }
  return n;
}

int
interpretAST(struct ASTnode *n) 
{
  if(NULL != n)
  {
    int leftval, rightval;
    if (n->left)
    {
      leftval = interpretAST(n->left);
    }
    if (n->right)
    {
      rightval = interpretAST(n->right);
    }

    if (n->op == A_INTLIT)
    {
      printf("int %d\n", n->intvalue);
    }
    else
    {
      printf("%d %s %d\n", leftval, ASTOperators[n->op], rightval);
    }

    if(A_ADD == n->op)
    {
      return (leftval + rightval);
    }
    else if (A_SUBTRACT == n->op)
    {
      return (leftval - rightval);
    }
    else if (A_MULTIPLY == n->op)
    {
      return (leftval * rightval);
    }
    else if (A_DIVIDE == n->op)
    {
      return (leftval / rightval);
    }
    else if(A_INTLIT == n->op)
    {
      return (n->intvalue);
    }
    else
    {
      fprintf(stderr, "[%s, %s, %d] interpretAST() --> Unknown AST Operator: %d!\n", errorType(ERROR_PARSER), __FILE__, __LINE__, n->op);
    }
  }
  return 0;
}
