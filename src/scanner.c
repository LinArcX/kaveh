#include <errno.h>
#include "scanner.h"
#include "kutil.h"

int   line = 1;
int	  lastChar = '\n';
FILE  *p_sourceFile;

char*
stringOfTokenType(int type)
{
  if(TOKEN_INTEGER == type)
  {
    return "INTEGER";
  }
  else if(TOKEN_PLUS == type)
  {
    return "+";
  }
  else if(TOKEN_MINUS == type)
  {
    return "-";
  }
  else if(TOKEN_STAR == type)
  {
    return "*";
  }
  else if(TOKEN_SLASH == type)
  {
    return "/";
  }
  else
  {
    return "NIL";
  }
}

int
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
charPositionInString(char *str, int ch)
{
  char* position = strchr(str, ch);
  if(position)
  {
    return position - str;
  }
  return -1;
}

static int
scanInteger(int ch)
{
  int k, val = 0;

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

int
skipWhiteSpaces()
{
  int ch = nextChar();
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
    int ch = skipWhiteSpaces();

    switch (ch)
    {
    case EOF:
      return 0;
    case '+':
      token->type = TOKEN_PLUS;
      kmemcpy(token->literal.oprator, "+");
      break;
    case '-':
      token->type = TOKEN_MINUS;
      kmemcpy(token->literal.oprator, "-");
      break;
    case '*':
      token->type = TOKEN_STAR;
      kmemcpy(token->literal.oprator, "*");
      break;
    case '/':
      token->type = TOKEN_SLASH;
      kmemcpy(token->literal.oprator, "/");
      break;
    default:
      if (isdigit(ch))
      {
        token->type = TOKEN_INTEGER;
        token->literal.integer = scanInteger(ch);
        break;
      }

      printf("Unrecognised character %c on line %d\n", ch, line);
      exit(1);
    }
    return 1;
  }
  return 0;
}

void
scan(char* sourceFile)
{
  p_sourceFile = fopen(sourceFile, "r");
  if (NULL == p_sourceFile)
  {
    fprintf(stderr, "Unable to open %s: %s\n", sourceFile, strerror(errno));
    exit(-1);
  }

  Token token;
  while (tokenize(&token))
  {
    switch(token.type)
    {
      case TOKEN_PLUS:
      case TOKEN_MINUS:
      case TOKEN_STAR:
      case TOKEN_SLASH:
        printf("Token %s, literal %s\n", stringOfTokenType(token.type), token.literal.oprator);
        break;
      case TOKEN_INTEGER:
        printf("Token %s, literal %d\n", stringOfTokenType(token.type), token.literal.integer);
        break;
    }
  }
}
