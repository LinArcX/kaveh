#include <stdlib.h>
#include <errno.h>

#include "scanner.h"
#include "parser.h"
#include "kutil.h"

int
main(int argc, char *argv[])
{
  if (2 != argc)
  {
    die2s("Usage: %s <sourceFile>\n", argv[0]);
  }

  p_sourceFile = fopen(argv[1], "r");
  if (NULL == p_sourceFile)
  {
    die3s("Unable to open %s: %s\n", argv[1], strerror(errno));
  }

  scan(&token);
  struct ASTnode *node;
  node = binexpr(&token);		// Parse the expression in the file
  printf("%d\n", interpretAST(node));	// Calculate the final result
  
  return EXIT_SUCCESS;
}
