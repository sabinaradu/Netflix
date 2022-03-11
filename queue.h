/*RADU Sabina - 321CB*/

#include <stdio.h>

typedef struct Cell *TList;

typedef struct Queue {
    void *front, *rear;
    int size;
    TList list;
} TQueue;

TQueue *createQueue(void *data);

int queueEmpty(TQueue *q);

int addToQueue(TQueue *q, void *data);

void printQueue(TQueue *q, FILE *o, void (*printEl)(void *, FILE *));

void deleteQueue(TQueue *q, void (*freeInfo) (void *));

void freeQueueOfQueue(TQueue *q, void (*freeInfo) (void *));

void *removeFromQueue(TQueue *q);