#include "kutil.h"

#include <stdio.h>
#include <string.h>

int
kmemcpy(void *dest, const void *src)
{
  size_t srcSize = sizeof(src);
  size_t destSize = sizeof(dest);

  if(destSize < srcSize)
  {
    fprintf(stderr, "[%s, %s, %s, %d] *dest > *src\n", errorType(ERROR_KAVEH), __FILE__, __func__, __LINE__);
    return 0;
  }
  else
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
    return 1;
  }
}

char*
errorType(int error_type)
{
  if(ERROR_SCANNER == error_type)
  {
    return (char *)"Scanner Error";
  }
  else if(ERROR_PARSER == error_type)
  {
    return (char *)"Parser Error";
  }
  else if(ERROR_KAVEH == error_type)
  {
    return (char *)"Kaveh Error";
  }
  else
  {
    return (char *)"Uknown Error";
  }
}
