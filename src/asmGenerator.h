#ifndef KAVEH_ASM_GENERATOR_H
#define KAVEH_ASM_GENERATOR_H

void cgpreamble();
void cgpostamble();

int cgload(int value);
void cgprintint(int r);

int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);

void freeall_registers(void);
static int alloc_register(void);
static void free_register(int reg);

#endif
