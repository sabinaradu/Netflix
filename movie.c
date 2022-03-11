/*RADU Sabina - 321CB*/

#include "movie.h"


int compareMovie (const void * a, const void * b) {
    TList f = (TList)a;
    TList g = (TList)b;

    TMovie *m1 = (TMovie *)f->info;
    TMovie *m2 = (TMovie *)g->info;

    double diff = m1->rating - m2->rating;
    if (diff == 0)
        return strcmp(m2->nume, m1->nume);
    return diff > 0 ? 1 : -1;
}

TMovie *createMovie(char *nume, double rating, int sez, 
        TQueue *q, int time) {
    TMovie *m = (TMovie *)malloc(sizeof(TMovie));

    if (!m) {
        fprintf(stderr, "Could not allocate movie.\n");
        return NULL;
    }
    
    m->nume = (char *)malloc(NAME_LEN+1);
    if (!m->nume) {
        fprintf(stderr, "Could not allocate name.\n");
        free(m);
        return NULL;
    }

    memset(m->nume, 0, NAME_LEN+1);
    strncpy(m->nume, nume, NAME_LEN);
    m->rating = rating;
    m->sezoane = sez;
    m->sez = q;
    m->time_left = time;
    return m;
}

TMovie *findMovie(TList l, char *name) {
    TList p = l;

    while(p != NULL) {
        if (!strcmp(((TMovie *)p->info)->nume, name))
            return (TMovie *)p->info;
        p = p->next;
    }

    return NULL;
}

TMovie *findMovieQueue(TQueue *q, char *name) {
	TMovie *ret = NULL;
	TMovie *m = removeFromQueue(q);
	if (!m)
		return NULL;
	if (!strcmp(m->nume, name))
		ret = m;

	TQueue *nq = createQueue(m);
	if(!nq) {
		fprintf(stderr, "Queue for removal could not be allocated\n");
		return NULL;
	}
	while (!queueEmpty(q) ) {
		m = removeFromQueue(q);
		if (!ret && !strcmp(m->nume, name))
			ret = m;
		addToQueue(nq, m);
	}

	while(!queueEmpty(nq)) {
		m = removeFromQueue(nq);
		addToQueue(q, m);
	}

	free(nq);

	return ret;
}


TMovie *findMovieStack(TStack *s, char *name) {
	TMovie *ret = NULL;
	TMovie *m = removeFromStack(s);
	if (!m)
		return NULL;
	if (!strcmp(m->nume, name))
		ret = m;

	TStack *ns = createStack(m);
	if(!ns) {
		fprintf(stderr, "Stack for removal could not be allocated\n");
		return NULL;
	}
	while (!emptyStack(s) ) {
		m = removeFromStack(s);
		if (!ret && !strcmp(m->nume, name))
			ret = m;
		addToStack(ns, m);
	}

	while(!emptyStack(ns)) {
		m = removeFromStack(ns);
		addToStack(s, m);
	}

	free(ns);

	return ret;
}

TMovie *findRemoveStack(TStack *s, char *name) {
	TMovie *ret = NULL;
	TMovie *m = removeFromStack(s);
	if (!m)
		return NULL;
	if (!strcmp(m->nume, name))
		return m;

	TStack *ns = createStack(m);
	if(!ns) {
		fprintf(stderr, "Queue for removal could not be allocated\n");
		return NULL;
	}
	while (!emptyStack(s) ) {
		m = removeFromStack(s);
		if (!strcmp(m->nume, name))
			ret = m;
		else
			addToStack(ns, m);
	}

	while(!emptyStack(ns)) {
		m = removeFromStack(ns);
		addToStack(s, m);
	}

	free(ns);

	return ret;
}


TMovie *findRemoveQueue(TQueue *q, char *name) {
	TMovie *ret = NULL;
	TMovie *m = removeFromQueue(q);
	if (!m)
		return NULL;
	if (!strcmp(m->nume, name))
		return m;

	TQueue *nq = createQueue(m);
	if(!nq) {
		fprintf(stderr, "Queue for removal could not be allocated\n");
		return NULL;
	}
	while (!queueEmpty(q) ) {
		m = removeFromQueue(q);
		if (!strcmp(m->nume, name))
			ret = m;
		else
			addToQueue(nq, m);
	}

	while(!queueEmpty(nq)) {
		m = removeFromQueue(nq);
		addToQueue(q, m);
	}

	free(nq);

	return ret;
}

TMovie *findRemoveMovie(TList *l, char *name) {
    TList p = *l, last = NULL;

    while(p != NULL) {
        if (!strcmp(((TMovie *)p->info)->nume, name)) {
        	if (last == NULL)
        		*l = p->next;
        	else {
        		last->next = p->next;
        	}
        	TMovie *m = p->info;
        	free(p);
            return m;
        }
        last = p;
        p = p->next;
    }

    return NULL;
}

int watchMovie(TMovie *m, int len) {
	m->time_left -= len;
	if (m->time_left <= 0) {
		m->time_left = 0;
		return 1;
	}
	return 0;
}

void printMovie(void *el, FILE *out) {
    TMovie *m = (TMovie *)el;
    if (!m)
        return;
    if (!m->nume)
        return;

    fprintf(out, "(%s, %.1lf)", m->nume, m->rating);
}

void freeMovie(void *a) {
	if(!a)
		return;

    TMovie *m = (TMovie *)a;
    free(m->nume);

    freeQueueOfQueue(m->sez, free);

    free(m);
}
