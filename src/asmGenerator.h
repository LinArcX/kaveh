#ifndef KAVEH_ASM_GENERATOR_H
#define KAVEH_ASM_GENERATOR_H

#include <stdio.h>

void cgPreamble();
void cgPostamble();

int cgLoad(int value);
void cgPrintInt(int r);

int cgAdd(int r1, int r2);
int cgSub(int r1, int r2);
int cgMul(int r1, int r2);
int cgDiv(int r1, int r2);

void freeAllRegisters(void);
static int allocateRegister(void);
static int freeRegister(int reg);

#endif
