#ifndef KAVEH_UTIL_H
#define KAVEH_UTIL_H

enum KERROR {
  KDEST_SMALLER_THAN_SRC = 10000
};

int kmemcpy(void *dest, const void *src);
int die(void);

#endif
