#include "kutil.h"
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
    return SUCCESS;
  }
  return DEST_SMALLER_THAN_SRC;
}
