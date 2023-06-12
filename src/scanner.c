#include <errno.h>

#include "scanner.h"
#include "logger.h"

int   line = 1;
int	  lastChar = '\n';
FILE  *p_sourceFile;

char* stringOfTokenType(int type)
{
  switch(type)
  {
    case TOKEN_INTEGER:
      return "INTEGER";
      break;
    case TOKEN_PLUS:
      return "+";
      break;
    case TOKEN_MINUS:
      return "-";
      break;
    case TOKEN_STAR:
      return "*";
      break;
    case TOKEN_SLASH:
      return "/";
      break;
    default:
      return "NIL";
      break;
  }
}

int nextChar()
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

static int charPositionInString(char *str, int ch)
{
  char* position = strchr(str, ch);
  if(position)
  {
    return position - str;
  }
  else
  {
    return EXIT_NEGATIVE;
  }
}

static int scanInteger(int ch)
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

int skipWhiteSpaces()
{
  int ch = nextChar();
  while (' ' == ch || '\t' == ch || '\n' == ch || '\r' == ch || '\f' == ch)
  {
    ch = nextChar();
  }
  return (ch);
}

int tokenize(Token* token)
{
  int ch = skipWhiteSpaces();

  switch (ch)
  {
  case EOF:
    return EXIT_NEGATIVE;
  case '+':
    token->type = TOKEN_PLUS;
    strcpy(token->literal.oprator, "+");
    break;
  case '-':
    token->type = TOKEN_MINUS;
    strcpy(token->literal.oprator, "-");
    break;
  case '*':
    token->type = TOKEN_STAR;
    strcpy(token->literal.oprator, "*");
    break;
  case '/':
    token->type = TOKEN_SLASH;
    strcpy(token->literal.oprator, "/");
    break;
  default:
    if (isdigit(ch))
    {
      token->type = TOKEN_INTEGER;
      token->literal.integer = scanInteger(ch);
      break;
    }

    printf("Unrecognised character %c on line %d\n", ch, line);
    exit(EXIT_NEGATIVE);
  }

  return EXIT_POSITIVE;
}

void scan(char* sourceFile)
{
  p_sourceFile = fopen(sourceFile, "r");
  if (NULL == p_sourceFile)
  {
    fprintf(stderr, "Unable to open %s: %s\n", sourceFile, strerror(errno));
    exit(EXIT_NEGATIVE);
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
