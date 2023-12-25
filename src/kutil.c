#include "kutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
kmemcpy(void *dest, const void *src)
{
  size_t srcSize = sizeof(src);
  size_t destSize = sizeof(dest);

  if(destSize < srcSize)
  {
    die();
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
  }
}

int
kerror(void)
{
  fprintf(stderr, "[ERROR] file: %s, line: %d", __FILE__, __LINE__);
  return EXIT_FAILURE;
}

void
kerror2i(char* message, int arg1, int arg2)
{
  fprintf(stderr, message, arg1, arg2);
}

void
die(void)
{
  fprintf(stderr, "[ERROR] file: %s, line: %d", __FILE__, __LINE__);
  exit(EXIT_FAILURE);
}

void
die1i(char* message, int arg)
{
  fprintf(stderr, message, arg);
  exit(EXIT_FAILURE);
}

void
die2i(char* message, int arg1, int arg2)
{
  fprintf(stderr, message, arg1, arg2);
  exit(EXIT_FAILURE);
}

void
die1s(char* message)
{
  fprintf(stderr, message, NULL);
  exit(EXIT_FAILURE);
}

void
die2s(char* message, char* arg1)
{
  fprintf(stderr, message, arg1);
  exit(EXIT_FAILURE);
}

void
die3s(char* message, char* arg1, char* arg2)
{
  fprintf(stderr, message, arg1, arg2);
  exit(EXIT_FAILURE);
}
