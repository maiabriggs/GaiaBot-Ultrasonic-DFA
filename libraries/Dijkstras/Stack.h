// Stack.h

#ifndef Stack_h
#define Stack_h

#include "Arduino.h"

#define STACK_CAPACITY 100

void stack_init();
void stack_push(int value);
int stack_top();
void stack_pop();
bool stack_empty();

#endif
