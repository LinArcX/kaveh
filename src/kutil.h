#ifndef KAVEH_UTIL_H
#define KAVEH_UTIL_H

enum KERROR {
    SUCCESS = 0,
    ERROR = -1,
    DEST_SMALLER_THAN_SRC = 10000
};

int kmemcpy(void *dest, const void *src);

#endif
