#include <errno.h>
#include <stdlib.h>

#include "scanner.h"
#include "kutil.h"

#define outTokenStringLenght 100
Token token;

int   line = 1;
int	  lastChar = 0;
FILE  *p_sourceFile;

static void
tokenTypeString(int type, char * const tokenName)
{
  memset(tokenName, 0, outTokenStringLenght);

  if(TOKEN_INTEGER == type)
  {
    kmemcpy(tokenName, "INTEGER");
  }
  else if(TOKEN_PLUS == type)
  {
    kmemcpy(tokenName, "+");
  }
  else if(TOKEN_MINUS == type)
  {
    kmemcpy(tokenName, "-");
  }
  else if(TOKEN_STAR == type)
  {
    kmemcpy(tokenName, "*");
  }
  else if(TOKEN_SLASH == type)
  {
    kmemcpy(tokenName, "/");
  }
  else
  {
    kmemcpy(tokenName, "NIL");
  }
}

static int
nextChar(void)
{
  int ch;

  if (lastChar)
  {
    ch = lastChar;	// Use the character put
    lastChar = 0;   // back if there is one
    return ch;
  }

  ch = fgetc(p_sourceFile);
  if ('\n' == ch)
  {
    line++;
  }
  return ch;
}

static int
charPositionInString(const char * str, int ch)
{
  const char * position = strchr(str, ch);
  if(position)
  {
    return position - str;
  }
  return -1;
}

static int
scanInteger(int ch)
{
  int k;
  int val = 0;

  // Convert each character into an int value
  while ((k = charPositionInString("0123456789", ch)) >= 0)
  {
    val = val * 10 + k;
    ch = nextChar();
  }

  // We hit a non-integer character, put it back.
  lastChar = ch;
  return val;
}

static char
skipWhiteSpaces(void)
{
  char ch = nextChar();
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch)
  {
    ch = nextChar();
  }
  return (ch);
}

void
scan(Token* token)
{
  memset(token, 0, sizeof(Token));

  if(NULL != token)
  {
    char ch = skipWhiteSpaces();

    if(EOF == ch)
    {
      return;
    }
    if('+' == ch)
    {
      token->type = TOKEN_PLUS;
      kmemcpy(token->literal.oprator, "+");
    }
    else if('-' == ch)
    {
      token->type = TOKEN_MINUS;
      kmemcpy(token->literal.oprator, "-");
    }
    else if('*' == ch)
    {
      token->type = TOKEN_STAR;
      kmemcpy(token->literal.oprator, "*");
    }
    else if('/' == ch)
    {
      token->type = TOKEN_SLASH;
      kmemcpy(token->literal.oprator, "/");
    }
    else 
    {
      if (isdigit(ch))
      {
        token->type = TOKEN_INTEGER;
        token->literal.integer = scanInteger(ch);
      }
      else
      {
        kerror2i("[ERROR] Unrecognised character %c on line %d\n", ch, line);
      }
    }
  }
  else
  {
    die1s("[ERROR] Token is NULL\n");
  }
}
