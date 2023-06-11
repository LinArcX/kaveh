#include "scanner.h"
#include <errno.h>

int     line = 1;
int	seenChar = '\n';
FILE	*inputFile;

static void usage(char *prog)
{
  fprintf(stderr, "Usage: %s inputFile\n", prog);
  exit(EXIT_ERROR);
}

char *tokens[] = {
  "+",
  "-",
  "*",
  "/",
  "intlit"
};

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile()
{
  Token token;

  while (scan(&token))
  {
    printf("Token %s", tokens[token.token]);
    if (token.token == T_INTLIT)
    {
      printf(", value %d", token.intvalue);
    }
    printf("\n");
  }
}

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    usage(argv[0]);
  }

  if ((inputFile = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(EXIT_ERROR);
  }

  scanfile();
  return EXIT_SUCCESS;
}
