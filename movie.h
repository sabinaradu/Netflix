/*RADU Sabina - 321CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "queue.h"
#include "stack.h"

#define NAME_LEN 32

typedef struct movie{
    char *nume;
    double rating;
    int sezoane;
    int time_left;
    TQueue *sez;
} TMovie;

int compareMovie (const void * a, const void * b) ;

TMovie *createMovie(char *nume, double rating, int sez, 
        TQueue *q, int time) ;

int watchMovie(TMovie *m, int len) ;

TMovie *findMovie(TList l, char *name);\

TMovie *findMovieQueue(TQueue *q, char *name);

TMovie *findMovieStack(TStack *s, char *name);

TMovie *findRemoveStack(TStack *s, char *name);

TMovie *findRemoveMovie(TList *l, char *name);

TMovie *findRemoveQueue(TQueue *q, char *name);

void printMovie(void *el, FILE *out) ;

void freeMovie(void *a) ;


