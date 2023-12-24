#include <errno.h>
#include <stdlib.h>

#include "scanner.h"
#include "kutil.h"

#define outTokenStringLenght 100

int   line = 1;
int	  lastChar = 0;
FILE  *p_sourceFile;

static int
tokenTypeString(int type, char * const tokenName)
{
  memset(tokenName, 0, outTokenStringLenght);

  if(TOKEN_INTEGER == type)
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "INTEGER"))
    {
      return die();
    }
  }
  else if(TOKEN_PLUS == type)
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "+"))
    {
      return die();
    }
  }
  else if(TOKEN_MINUS == type)
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "-"))
    {
      return die();
    }
  }
  else if(TOKEN_STAR == type)
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "*"))
    {
      return die();
    }
  }
  else if(TOKEN_SLASH == type)
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "/"))
    {
      return die();
    }
  }
  else
  {
    if(EXIT_SUCCESS != kmemcpy(tokenName, "NIL"))
    {
      return die();
    }
  }
  return EXIT_SUCCESS;
}

static int
nextChar()
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
skipWhiteSpaces()
{
  char ch = nextChar();
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch)
  {
    ch = nextChar();
  }
  return (ch);
}

int
tokenize(Token* token)
{
  memset(token, 0, sizeof(Token));

  if(NULL != token)
  {
    char ch = skipWhiteSpaces();

    if(EOF == ch)
    {
      return EXIT_FAILURE;
    }
    else if('+' == ch)
    {
      token->type = TOKEN_PLUS;
      if(EXIT_SUCCESS != kmemcpy(token->literal.oprator, "+"))
      {
        return die();
      }
      return EXIT_SUCCESS;
    }
    else if('-' == ch)
    {
      token->type = TOKEN_MINUS;
      if(EXIT_SUCCESS != kmemcpy(token->literal.oprator, "-"))
      {
        return die();
      }
      return EXIT_SUCCESS;
    }
    else if('*' == ch)
    {
      token->type = TOKEN_STAR;
      if(EXIT_SUCCESS != kmemcpy(token->literal.oprator, "*"))
      {
        return die();
      }
      return EXIT_SUCCESS;
    }
    else if('/' == ch)
    {
      token->type = TOKEN_SLASH;
      if(EXIT_SUCCESS != kmemcpy(token->literal.oprator, "/"))
      {
        return die();
      }
      return EXIT_SUCCESS;
    }
    else 
    {
      if (isdigit(ch))
      {
        token->type = TOKEN_INTEGER;
        token->literal.integer = scanInteger(ch);
        return EXIT_SUCCESS;
      }
    }
    fprintf(stderr, "[ERROR] Unrecognised character %c on line %d\n", ch, line);
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

int
scan(const char* sourceFile)
{
  p_sourceFile = fopen(sourceFile, "r");
  if (NULL == p_sourceFile)
  {
    fprintf(stderr, "Unable to open %s: %s\n", sourceFile, strerror(errno));
    exit(EXIT_FAILURE);
  }

  Token token;
  char outTokenString[outTokenStringLenght] = {'\0'};

  while (EXIT_SUCCESS == tokenize(&token))
  {
    if(EXIT_SUCCESS == tokenTypeString(token.type, outTokenString))
    {
      if(TOKEN_PLUS == token.type)
      {
        printf("Token %s, literal %s\n", outTokenString, token.literal.oprator);
      }
      else if(TOKEN_MINUS == token.type)
      {
        printf("Token %s, literal %s\n", outTokenString, token.literal.oprator);
      }
      else if(TOKEN_STAR == token.type)
      {
        printf("Token %s, literal %s\n", outTokenString, token.literal.oprator);
      }
      else if(TOKEN_SLASH == token.type)
      {
        printf("Token %s, literal %s\n", outTokenString, token.literal.oprator);
      }
      else if(TOKEN_INTEGER == token.type)
      {
        printf("Token %s, literal %d\n", outTokenString, token.literal.integer);
      }
    }
  }
  return EXIT_SUCCESS;
}
