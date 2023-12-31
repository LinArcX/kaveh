#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "kutil.h"
#include "parser.h"
#include "asmGenerator.h"

static int 
generateAST(struct ASTnode *n) 
{
  int leftreg, rightreg;

  if (n->left)
  {
    leftreg = generateAST(n->left);
  }

  if (n->right)
  {
    rightreg = generateAST(n->right);
  }

  if(A_ADD == n->op)
  {
    return (cgadd(leftreg,rightreg));
  }
  else if(A_SUBTRACT == n->op)
  {
    return (cgsub(leftreg,rightreg));
  }
  else if(A_MULTIPLY == n->op)
  {
    return (cgmul(leftreg,rightreg));
  }
  else if(A_DIVIDE == n->op)
  {
    return (cgdiv(leftreg,rightreg));
  }
  else if(A_INTLIT == n->op)
  {
    return (cgload(n->intvalue));
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unknown AST operator %d\n", errorType(ERROR_GENERATOR), __FILE__, __func__, __LINE__, n->op);
    exit(1);
  }
}

void
generateCode(struct ASTnode *n) 
{
  int reg;
  cgpreamble();
  reg = generateAST(n);
  cgprintint(reg);
  cgpostamble();
}
