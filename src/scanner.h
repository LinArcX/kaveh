#ifndef KAVEH_SCANNER_H
#define KAVEH_SCANNER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN     512             // Length of symbols in input

extern int  line;
extern int	lastChar;
extern FILE	*p_sourceFile;
extern char Text[TEXTLEN + 1];         // Last identifier scanned

typedef enum
{
  TOKEN_EOF = 0,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_SEMICOLON,
  TOKEN_PRINT,
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
