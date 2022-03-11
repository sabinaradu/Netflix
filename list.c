/*RADU Sabina - 321CB*/

#include "list.h"


TList createList(void *data) {
    TList l = (TList)malloc(sizeof(TCell));
    
    if (!l) {
        fprintf(stderr, "Could not allocate list head.\n");
        return NULL;
    }


    l->info = data;
    l->next = NULL;

    return l;
}

void printList(TList l, FILE *out, void (*printEl)(void *, FILE *)) {
    fprintf(out, "[");
    TList p = l;

    while (p != NULL) {
        printEl(p->info, out);
        p = p->next;
        if (p)
            fprintf(out, ", ");
    }

    fprintf(out, "].\n");
}

int addToList(TList *l, void *data, int (*compar)(const void *, const void*)) {
    TList new_cell = (TList)malloc(sizeof(TCell));

    if (!new_cell) {
        fprintf(stderr, "Could not allocate list element.\n");
        return -1;
    }

    int pos = 0;

    new_cell->info = data;
    new_cell->next = NULL;

    TList p = *l, last = NULL;
    while( p != NULL ) {
        if (compar(new_cell, p) > 0) {
            if (p == *l) {
                new_cell->next = *l;
                *l = new_cell;
                return pos + 1;
            }
            last->next = new_cell;
            new_cell->next = p;
            return pos + 1;
        }
        last = p;
        p = p->next;
        pos += 1;
    }
    last->next = new_cell;
    return pos + 1;
}

void checkIfTooLong(TList *l, void (*freeInfo) (void *)) {
	TList p = *l, last = NULL;

	int count = 0;

	while (p != NULL) {
		count++;
		if (count > MAX_LEN_TOP) {
			TList n = p->next;
			freeInfo(p->info);
			free(p);
			p = last;
			p->next = n;
		}

		last = p;
		p = p->next;
	}
}

void addToPosList(TList *l, void *data, int pos) {
    TList new_cell = (TList)malloc(sizeof(TCell));

    if (!new_cell) {
        fprintf(stderr, "Could not allocate list element.\n");
        return;
    }

    int count = 1;

    new_cell->info = data;
    new_cell->next = NULL;

    TList p = *l, last = NULL;
    while( p != NULL ) {
        if (count == pos) {
            if (last == NULL) {
                new_cell->next = *l;
                *l = new_cell;
                return;
            }
            last->next = new_cell;
            new_cell->next = p;
            return;
        }

        last = p;
        p = p->next;
        count++;
    }

    last->next = new_cell;
}

void freeCells (TList l) {
	TList p = NULL;
    if (l->next == NULL) {
        free(l);
        return;
    }

    do {
        p = l->next;
        free(l);
        l = p;
    } while (p != NULL);
}

void deleteList(TList l, void (*freeInfo) (void *)) {
	if (!l) {
		return;
	}

    TList p = NULL;
    if (l->next == NULL) {
        freeInfo(l->info);
        free(l);
        return;
    }

    do {
        p = l;
        l = l->next;
        freeInfo(p->info);
        free(p);
    } while (l != NULL);
}
