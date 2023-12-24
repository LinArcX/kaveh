#include "kutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
kmemcpy(void *dest, const void *src)
{
  size_t srcSize = sizeof(src);
  size_t destSize = sizeof(dest);

  if(destSize >= srcSize)
  {
    if (dest < src && dest + srcSize > src) 
    {
      memmove(dest, src, srcSize);
    }
    else if (src < dest && src + srcSize > dest) 
    {
      memmove(dest, src, srcSize);
    }
    else 
    {
      memcpy(dest, src, srcSize);
    }
    return EXIT_SUCCESS;
  }
  return KDEST_SMALLER_THAN_SRC;
}

int
die(void)
{
  fprintf(stderr, "[ERROR] file: %s, line: %d", __FILE__, __LINE__);
  return EXIT_FAILURE;
}
