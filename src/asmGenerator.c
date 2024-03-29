#include <stdio.h>

#include "kutil.h"
#include "asmGenerator.h"

// List of available registers and their names
static int freereg[4];
static char *reglist[4]= { "%r8", "%r9", "%r10", "%r11" };

void 
cgPreamble()
{
  freeAllRegisters();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t.type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n",
  p_outFile);
}

void
cgPostamble()
{
  fputs(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n",
  p_outFile);
}

// Load an integer literal value into a register. Return the number of the register
int 
cgLoad(int value) 
{
  // Get a new register
  int r= allocateRegister();

  // Print out the code to initialise it
  fprintf(p_outFile, "\tmovq\t$%d, %s\n", value, reglist[r]);
  return(r);
}

// Call printint() with the given register
void 
cgPrintInt(int r) 
{
  fprintf(p_outFile, "\tmovq\t%s, %%rdi\n", reglist[r]);
  fprintf(p_outFile, "\tcall\tprintint\n");
  freeRegister(r);
}

int 
cgAdd(int r1, int r2) 
{
  fprintf(p_outFile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
  freeRegister(r1);
  return(r2);
}

int 
cgSub(int r1, int r2) 
{
  fprintf(p_outFile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
  freeRegister(r2);
  return(r1);
}

int 
cgMul(int r1, int r2) 
{
  fprintf(p_outFile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
  freeRegister(r1);
  return(r2);
}

// Divide the first register by the second and return the number of the register with the result
int 
cgDiv(int r1, int r2) 
{
  fprintf(p_outFile, "\tmovq\t%s,%%rax\n", reglist[r1]);
  fprintf(p_outFile, "\tcqo\n");
  fprintf(p_outFile, "\tidivq\t%s\n", reglist[r2]);
  fprintf(p_outFile, "\tmovq\t%%rax,%s\n", reglist[r1]);
  freeRegister(r2);
  return(r1);
}

// Set all registers as available
void
freeAllRegisters(void)
{
  freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// Allocate a free register. Return the number of the register. Die if no available registers.
static int
allocateRegister(void)
{
  for (int i=0; i<4; i++) 
  {
    if (freereg[i]) 
    {
      freereg[i]= 0;
      return(i);
    }
  }
  fprintf(stderr, "Out of registers!\n");
  return 0;
}

// Return a register to the list of available registers. Check to see if it's not already there.
static int
freeRegister(int reg)
{
  if (freereg[reg] != 0) 
  {
    fprintf(stderr, "Error trying to free register %d\n", reg);
    return 0;
  }
  freereg[reg]= 1;
  return 1;
}
