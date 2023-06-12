#include "scanner.h"
#include "logger.h"

void usage(char *program)
{
  fprintf(stderr, "Usage: %s <sourceFile>\n", program);
  exit(EXIT_NEGATIVE);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    usage(argv[0]);
  }

  scan(argv[1]);
  return EXIT_ZERO;
}
