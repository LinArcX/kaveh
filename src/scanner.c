#include "scanner.h"
#include "kutil.h"

Token g_token;

int   line = 1;
int	  lastChar = 0;
FILE  *p_sourceFile;

static int
nextChar(void)
{
  int ch;

  if (lastChar)
  {
    ch = lastChar;	// Use the character put back if there is one
    lastChar = 0;
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

static int
skipWhiteSpaces(void)
{
  int ch = nextChar();
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch)
  {
    ch = nextChar();
  }
  return (ch);
}

int
scan(Token * token)
{
  memset(token, 0, sizeof(Token));

  if(NULL != token)
  {
    int ch = skipWhiteSpaces();

    if(EOF == ch)
    {
      token->type = TOKEN_EOF;
      return 0;
    }
    if('+' == ch)
    {
      token->type = TOKEN_PLUS;
      if(!kmemcpy(token->literal.oprator, "+"))
      {
        fprintf(stderr, "[%s, %s, %s, %d]\n", errorType(ERROR_KAVEH), __FILE__, __func__, __LINE__);
        return 0;
      }
    }
    else if('-' == ch)
    {
      token->type = TOKEN_MINUS;
      if(!kmemcpy(token->literal.oprator, "-"))
      {
        fprintf(stderr, "[%s, %s, %s, %d]\n", errorType(ERROR_KAVEH), __FILE__, __func__, __LINE__);
        return 0;
      }
    }
    else if('*' == ch)
    {
      token->type = TOKEN_STAR;
      if(!kmemcpy(token->literal.oprator, "*"))
      {
        fprintf(stderr, "[%s, %s, %s, %d]\n", errorType(ERROR_KAVEH), __FILE__, __func__, __LINE__);
        return 0;
      } 
    }
    else if('/' == ch)
    {
      token->type = TOKEN_SLASH;
      if(!kmemcpy(token->literal.oprator, "/"))
      {
        fprintf(stderr, "[%s, %s, %s, %d]\n", errorType(ERROR_KAVEH), __FILE__, __func__, __LINE__);
        return 0;
      }
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
        fprintf(stderr, "[%s, %s, %s, %d] Unrecognised character %c on line %d\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__, ch, line);
      }
    }
    return 1;
  }
  else
  {
    fprintf(stderr, "[%s, %s, %s, %d] token is NULL!\n", errorType(ERROR_SCANNER), __FILE__, __func__, __LINE__);
    return 0;
  }
}
