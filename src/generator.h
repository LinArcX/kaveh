#ifndef KAVEH_GENERATOR_H
#define KAVEH_GENERATOR_H

#include "parser.h"

void generateCode(struct ASTnode *n);
int generateAST(struct ASTnode *n);

void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);

#endif

