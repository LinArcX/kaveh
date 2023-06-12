#ifndef KAVEH_SCANNER_H
#define KAVEH_SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int  line;
extern int	lastChar;
extern FILE	*p_sourceFile;

typedef enum
{
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_INTEGER
} TokenTypes;

typedef struct
{
  char oprator[2];
  int integer;
} TokenLiteral;

typedef struct
{
  TokenTypes type;
  TokenLiteral literal;
} Token;

void scan(char* sourceFile);

#endif
