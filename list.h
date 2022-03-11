/*RADU Sabina - 321CB*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN_TOP 10

typedef struct Cell {
    void *info;
    struct Cell *next;
} TCell, *TList;

TList createList(void *data) ;

void checkIfTooLong(TList *l, void (*freeInfo) (void *)) ;

void printList(TList l, FILE *out, void (*printEl)(void *, FILE *)) ;

int addToList(TList *l, void *data, int (*compar)(const void *, const void*)) ;

void addToPosList(TList *l, void *data, int pos) ;

void freeCells (TList l) ;

void deleteList(TList l, void (*freeInfo) (void *)) ;