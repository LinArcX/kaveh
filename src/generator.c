#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "kutil.h"
#include "parser.h"
#include "asmGenerator.h"

int 
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
    return (cgAdd(leftreg,rightreg));
  }
  else if(A_SUBTRACT == n->op)
  {
    return (cgSub(leftreg,rightreg));
  }
  else if(A_MULTIPLY == n->op)
  {
    return (cgMul(leftreg,rightreg));
  }
  else if(A_DIVIDE == n->op)
  {
    return (cgDiv(leftreg,rightreg));
  }
  else if(A_INTLIT == n->op)
  {
    return (cgLoad(n->intvalue));
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s(), %d] Unknown AST operator %d\n", errorType(ERROR_GENERATOR), __FILE__, __func__, __LINE__, n->op);
    exit(1);
  }
}

void 
genpreamble()
{
  cgPreamble(); 
}

void
genpostamble()
{
  cgPostamble(); 
}

void 
genfreeregs()        
{
  freeAllRegisters(); 
}

void 
genprintint(int reg) 
{ 
  cgPrintInt(reg); 
}

void
generateCode(struct ASTnode *n) 
{
  int reg;
  cgPreamble();

  reg = generateAST(n);
  cgPrintInt(reg);

  cgPostamble();
}
