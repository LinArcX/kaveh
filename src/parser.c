#include <stdlib.h>

#include "scanner.h"
#include "parser.h"
#include "kutil.h"
#include "generator.h"

static const char * ASTOperators[] = { "+", "-", "*", "/" };
//                                 EOF  +   -    *   /  INTLIT
static int g_operatorsPrecedence[] = {0, 10,  10,  20, 20, 0 };

struct ASTnode* 
buildASTNode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) 
{
  struct ASTnode *n = {0};

  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (NULL == n) 
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unable to malloc ASTNode!\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__);
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
  else if(TOKEN_INTEGER == token)
  {
    return A_INTLIT;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unknown token: %d on line %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, token, line);
    return -2;
  }
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
    fprintf(stderr, "[%s, %s, %s(), %d] Syntax Error on line: %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, line);
  }
  return NULL;
}

static int 
operatorPrecedence(int tokenType) 
{
  int prec = g_operatorsPrecedence[tokenType];
  if (prec == 0) 
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Syntax Error on line: %d, token: %d\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, line, tokenType);
  }
  return prec;
}

// Ensure that the current token is t, and fetch the next token. Otherwise throw an error 
void 
match(int t, char *what) 
{
  if (g_token.type == t)
  {
    scan(&g_token);
  }
  else
  {
    printf("%s expected on line %d\n", what, line);
    exit(1);
  }
}

void 
semi(void) 
{
  match(TOKEN_SEMICOLON, ";");
}

// Parse one or more statements
void 
statements(void) 
{
  struct ASTnode *tree;
  int reg;

  while (1) {
    // Match a 'print' as the first token
    match(TOKEN_PRINT, "print");

    // Parse the following expression and generate the assembly code
    tree = parseExpressions(0);
    reg = generateAST(tree);
    genprintint(reg);
    genfreeregs();

    // Match the following semicolon and stop if we are at EOF
    semi();
    if (TOKEN_EOF == g_token.type)
    {
      return;
    }
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *
parseExpressions(int precedence) 
{
  int tokenType;
  struct ASTnode *left = {0};
  struct ASTnode *right = {0};

  // Get the integer literal on the left. Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  tokenType = g_token.type;
  if (TOKEN_SEMICOLON == tokenType)
  {
    return left;
  }

  while(operatorPrecedence(tokenType) > precedence)
  {
    scan(&g_token);
    right = parseExpressions(g_operatorsPrecedence[tokenType]);
    left = buildASTNode(scannerTypeToParserType(tokenType), left, right, 0);
    tokenType = g_token.type;

    if (TOKEN_SEMICOLON == tokenType)
    {
      return left;
    }
  }
  return left;
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

    #ifdef PARSER_LOG
    if (n->op == A_INTLIT)
    {
      printf("int %d\n", n->intvalue);
    }
    else
    {
      printf("%d %s %d\n", leftval, ASTOperators[n->op], rightval);
    }
    #endif
    
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
      fprintf(stderr, "[%s, %s, %s(), %d] Unknown AST Operator: %d!\n", errorType(ERROR_PARSER), __FILE__, __func__, __LINE__, n->op);
    }
  }
  return 0;
}
