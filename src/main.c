#include "kutil.h"
#include "scanner.h"

static int
usage(char *program)
{
  if(NULL != program)
  {
    fprintf(stderr, "Usage: %s <sourceFile>\n", program);
  }
  return ERROR;
}

int
main(int argc, char *argv[])
{
  if (2 != argc)
  {
    return usage(argv[0]);
  }
  scan(argv[1]);
  return SUCCESS;
}
