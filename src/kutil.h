#ifndef KAVEH_UTIL_H
#define KAVEH_UTIL_H

#include <stdio.h>

enum K_ERROR {
  ERROR_PARSER,
  ERROR_SCANNER,
  ERROR_GENERATOR,
  ERROR_KAVEH,
  WARNING
};

extern FILE	*p_outFile;

int kmemcpy(void *dest, const void *src);
char* errorType(int error_type);

#endif
