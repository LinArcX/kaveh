#include "scanner.h"

static int
usage(const char *program)
{
  if(NULL != program)
  {
    fprintf(stderr, "Usage: %s <sourceFile>\n", program);
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int
main(int argc, char *argv[])
{
  if (2 != argc)
  {
    return usage(argv[0]);
  }
  return scan(argv[1]);
}
