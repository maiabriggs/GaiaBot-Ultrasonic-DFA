// Stack.cpp

#include "Arduino.h"
#include "Stack.h"

int stack[STACK_CAPACITY];
int stackTop = -1;

void stack_init() {
    stackTop = -1;
}

void stack_push(int value) {
    if (stackTop < STACK_CAPACITY - 1) {
        stack[++stackTop] = value;
    }
}

int stack_top() {
    if (stackTop >= 0) {
        return stack[stackTop];
    }
    return -1;
}

void stack_pop() {
    if (stackTop >= 0) {
        --stackTop;
    }
}

bool stack_empty() {
    return stackTop == -1;
}
