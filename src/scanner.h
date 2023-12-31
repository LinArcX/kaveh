#ifndef KAVEH_SCANNER_H
#define KAVEH_SCANNER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern int  line;
extern int	lastChar;
extern FILE	*p_sourceFile;

typedef enum
{
  TOKEN_EOF = -1,
  TOKEN_PLUS = 0,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_INTEGER,
} TokenTypes;

typedef struct
{
  char oprator[2]; // 2 because one for operator and another for \0
  int integer;
} TokenLiteral;

typedef struct
{
  TokenTypes type;
  TokenLiteral literal;
} Token;
extern Token g_token;

int scan(Token * token);

#endif
