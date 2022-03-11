/*RADU Sabina - 321CB*/

#include "queue.h"
#include "list.h"

TQueue *createQueue(void *data) {
    TQueue *q = (TQueue *)malloc(sizeof(TQueue));

    if (!q) {
        fprintf(stderr, "Trouble allocating Q.\n");
        return NULL;
    }

    TList l = createList(data);
    if (!l) {
        free(q);
        return NULL;
    }

    q->list = l;
    q->front = q->rear = l;
    q->size = 1;

    return q;
}

int queueEmpty(TQueue *q) {
	return q->front == q->rear && q->front == NULL;
}



int addToQueue(TQueue *q, void *data) {
    if (!q) {
        fprintf(stderr, "Please don't send NULL queues.\n");
        return -1;
    }

    TList l = createList(data);
    if (!l) return -1;

    if (queueEmpty(q)) {
    	q->list = l;
    	q->front = q->rear = l;
    	q->size = 1;
    	return 1;
    }

    ((TList)q->rear)->next = l;
    q->rear = l;
    q->size += 1;

    return q->size;
}

void *peek(TQueue *q) {
	if (!q) {
        fprintf(stderr, "Please don't send NULL queues.\n");
        return NULL;
    }

	return ((TList)q->front)->info;
}

void *removeFromQueue(TQueue *q) {
	if (!q) {
        fprintf(stderr, "Please don't send NULL queues.\n");
        return NULL;
    }

    if (queueEmpty(q)) {
    	return NULL;
    }

    void *data = ((TList)q->front)->info;
    q->front = q->list->next;
    if( q->front == ((TList)q->rear)->next)
    	q->rear = q->front;
    free(q->list);
    q->list = (TList)q->front;
    q->size -= 1;

    return data;
}

void printQueue(TQueue *q, FILE *o, void (*printEl)(void *, FILE *)) {
	if (!q){
		fprintf(o, "[].\n");
		return;
	}
	printList(q->list, o, printEl);
}

void freeQueueOfQueue(TQueue *q, void (*freeInfo) (void *)) {
    TList p = q->front;
    
    while (p != NULL) {
        q->front = ((TList)q->front)->next;

        deleteQueue(p->info, freeInfo);
        free(p);

        p = q->front;
    }

    free(q);
}

void deleteQueue(TQueue *q, void (*freeInfo) (void *)) {
    if (!q)
        return;
    
    deleteList(q->list, freeInfo);
    free(q);
}

