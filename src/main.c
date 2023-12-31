#include <errno.h>
#include "scanner.h"
#include "parser.h"

int
main(int argc, char *argv[])
{
  if (2 != argc)
  {
    fprintf(stderr, "Usage: %s <sourceFile>\n", argv[0]);
    return -1;
  }

  p_sourceFile = fopen(argv[1], "r");
  if (NULL == p_sourceFile)
  {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    return -1;
  }

  if(scan(&g_token))
  {
    struct ASTnode *node = {0};
    node = parse(0);		
    if(NULL != node)
    {
      printf("%d\n", interpretAST(node));
      return 0;
    }
  }
  return -1;
}
