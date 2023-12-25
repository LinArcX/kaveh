#ifndef KAVEH_UTIL_H
#define KAVEH_UTIL_H

enum KERROR {
  KDEST_SMALLER_THAN_SRC = 10000
};

void kmemcpy(void *dest, const void *src);

int kerror(void);
void kerror2i(char* message, int arg1, int arg2);

void die(void);
void die1i(char*, int);
void die2i(char*, int, int);
void die1s(char*);
void die2s(char*, char*);
void die3s(char*, char*, char*);

#endif
