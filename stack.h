/*RADU Sabina - 321CB*/

#include <stdio.h>

typedef struct Cell *TList;

typedef struct Stack {
    void *top;
    TList list;
} TStack;

TStack *createStack(void *data);

int emptyStack(TStack *s);

void *top(TStack *s);

void addToStack(TStack *s, void *data);

void printStack(TStack *s, FILE *o, void (*printEl)(void *, FILE *));

void *removeFromStack(TStack *s);

void deleteStack(TStack *s, void (*freeInfo) (void *));