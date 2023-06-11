#ifndef KAVEH_SCANNER_H
#define KAVEH_SCANNER_H

#include "token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern int     line;
extern int	seenChar;
extern FILE	*inputFile;

int scan(Token *token);

#endif
