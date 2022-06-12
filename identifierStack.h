// Project 3 - Static Semantics
// identifierStack.h
// Tan Nguyen
// ntnhmc@umsystem.edu
// Apr 18, 2022
//


#ifndef IDENTIFIERSTACK_H
#define IDENTIFIERSTACK_H

#include <stdbool.h>
#include "token.h"

#define MAX_STACK_SIZE 100

void push(token);
void stackInit();
bool verify(token);
void print_stack();

#endif
