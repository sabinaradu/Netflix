/*RADU Sabina - 321CB*/

#include "stack.h"
#include "list.h"

TStack *createStack(void *data) {
	TStack *s = (TStack *)malloc(sizeof(TStack));

    if (!s) {
        fprintf(stderr, "Trouble allocating stack.\n");
        return NULL;
    }

    TList l = createList(data);
    if (!l) {
        free(s);
        return NULL;
    }

    s->list = l;
    s->top = l;

    return s;
}

int emptyStack(TStack *s) {
	return s->top == NULL;
}

void *top(TStack *s) {
	if (!s) {
        fprintf(stderr, "Please don't send NULL stacks.\n");
        return NULL;
    }

    if (emptyStack(s))
    	return NULL;
    else
		return ((TList)s->top)->info;
}

void addToStack(TStack *s, void *data) {
	if (!s) {
        fprintf(stderr, "Please don't send NULL stacks.\n");
        return;
    }

    TList l = createList(data);
    if (!l) return;

    l->next = (TList)s->top;
    s->top = l;
    s->list = l;
}

void printStack(TStack *s, FILE *o, void (*printEl)(void *, FILE *)) {
	if (!s) {
		fprintf(o, "[].\n");
		return;
	}

	printList(s->list, o, printEl);
}

void *removeFromStack(TStack *s) {
	if (!s) {
        fprintf(stderr, "Please don't send NULL stacks.\n");
        return NULL;
    }

    if (emptyStack(s))
    	return NULL;

    void *data = top(s);

    s->top = s->list->next;
    free(s->list);
    s->list = s->top;

    return data;
}

void deleteStack(TStack *s, void (*freeInfo) (void *)) {
    if (!s)
        return;
    
    deleteList(s->list, freeInfo);
    free(s);
}