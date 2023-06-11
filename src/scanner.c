#include "scanner.h"

static int charPositionInString(char *str, int ch)
{
  char *position;
  position = strchr(str, ch);

  if(position)
  {
    return position - str;
  }
  else
  {
    return EXIT_ERROR;
  }
}

static int nextChar()
{
  int ch;

  if (seenChar)
  {		// Use the character put
    ch = seenChar;		// back if there is one
    seenChar = 0;
    return ch;
  }

  ch = fgetc(inputFile);
  if ('\n' == ch)
  {
    line++;
  }
  return ch;
}

static void putBackSeenChar(int ch)
{
  seenChar = ch;
}

static int skipWhiteSpaces()
{
  int c;

  c = nextChar();
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = nextChar();
  }
  return (c);
}

// Scan and return an integer literal
// value from the input file. Store
// the value as a string in Text.
static int scanint(int c)
{
  int k, val = 0;

  // Convert each character into an int value
  while ((k = charPositionInString("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = nextChar();
  }

  // We hit a non-integer character, put it back.
  putBackSeenChar(c);
  return val;
}

// Scan and return the next token found in the input.
// Return 1 if token valid, 0 if no tokens left.
int scan(Token *t)
{
  int ch;

  ch = skipWhiteSpaces();

  // Determine the token based on
  // the input character
  switch (ch)
  {
  case EOF:
    return (0);
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_STAR;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  default:
    // If it's a digit, scan the
    // literal integer value in
    if (isdigit(ch)) {
      t->intvalue = scanint(ch);
      t->token = T_INTLIT;
      break;
    }

    printf("Unrecognised character %c on line %d\n", ch, line);
    exit(1);
  }

  // We found a token
  return (1);
}
