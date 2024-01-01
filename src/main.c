#include <errno.h>

#include "scanner.h"
#include "parser.h"
#include "generator.h"

FILE	*p_outFile;

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
    p_outFile = fopen("out.s", "w");
    if (NULL == p_outFile)
    {
      fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
      return -1;
    }
    genpreamble();                
    statements();
    genpostamble();               
    fclose(p_outFile);              
    return 0;

    //struct ASTnode *node = {0};
    //node = parseExpressions(0);		
    //if(NULL != node)
    //{
    //  printf("%d\n", interpretAST(node));
    //  generateCode(node);
    //  fclose(p_outFile);
    //  return 0;
    //}
  }
  return -1;
}
