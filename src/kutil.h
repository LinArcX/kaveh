#ifndef KAVEH_UTIL_H
#define KAVEH_UTIL_H

enum K_ERROR {
  ERROR_PARSER,
  ERROR_SCANNER,
  ERROR_KAVEH,
  WARNING
};

int kmemcpy(void *dest, const void *src);
char* errorType(int error_type);

#endif
