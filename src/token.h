#ifndef KAVEH_TOKEN_H
#define KAVEH_TOKEN_H

#define EXIT_SUCESS 0
#define EXIT_ERROR -1

typedef enum
{
  T_PLUS,
  T_MINUS,
  T_STAR,
  T_SLASH,
  T_INTLIT
} TokenTypes;

typedef struct
{
  TokenTypes token;
  int intvalue;
} Token;

#endif
