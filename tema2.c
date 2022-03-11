/*RADU Sabina - 321CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"

TMovie *readMovie() {
	int total = 0;
	char *token = strtok(NULL, " ");
    char *nume = token;

	token = strtok(NULL, " ");
	double rating = atof(token);

	token = strtok(NULL, " ");
	int sez = atoi(token);

	TQueue *sezoane = NULL;
	for(int i = 0; i < sez; i++) {
		token = strtok(NULL, " ");
		int ep = atoi(token);
                
		token = strtok(NULL, " ");
		int *el = (int *)malloc(sizeof(int));
		if (!el)
			return NULL;
		*el = atoi(token);
		total += *el;

		TQueue *q = createQueue(el);
		if (!q) {
			free(el);
			return NULL;
		}

		for(int j = 1; j < ep; j++) {
			token = strtok(NULL, " ");
			el = (int *)malloc (sizeof(int));

			if (!el) {
				deleteQueue(q, free);
				return NULL;
			}
			*el = atoi(token);
			total += *el;

			addToQueue(q, el);
		}

		if (sezoane)
		addToQueue(sezoane, q);
		else {
			sezoane = createQueue(q);
			if (!sezoane) {
				deleteQueue(q, free);
				return NULL;
			}    
		}
	}

	TMovie *m = createMovie(nume, rating, sez, sezoane, total);
	if (!m)
		freeQueueOfQueue(sezoane, free);
	return m;
}

TMovie *findAndRemove(TList *a, TList *b, TList *c, TList *d, char *name) {
	TMovie *m = NULL;
	m = findRemoveMovie(a, name);
	if (m)
		return m;
	m = findRemoveMovie(b, name);
	if (m)
		return m;
	m = findRemoveMovie(c, name);
	if (m)
		return m;
	m = findRemoveMovie(d, name);
	if (m)
		return m;
	return NULL;
}

TMovie *find(TList a, TList b, TList c, TList d, char *name) {
	TMovie *m = NULL;
	m = findMovie(a, name);
	if (m)
		return m;
	m = findMovie(b, name);
	if (m)
		return m;
	m = findMovie(c, name);
	if (m)
		return m;
	m = findMovie(d, name);
	if (m)
		return m;
	return NULL;
}

int main(int argc, char **argv) {
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    TStack *history = NULL;
    TStack *watch = NULL;
    TQueue *later = NULL;
    TList trend = NULL;
    TList doc = NULL;
    TList tut = NULL;
    TList top10 = NULL;

    char *token, line[1000];

    while(fgets(line, 1000, input) != NULL) {
        line[strlen(line)-1] = 0;
        token = strtok(line, " ");

        if(token == NULL) 
            break;
        else if(!strcmp(token, "add")) {
            token = strtok(NULL, " ");
            int id = atoi(token);
            
            TMovie *m = readMovie();
            if (!m)
            	goto exit;

            int pos = 0;

            switch(id) {
                case 1:
                    if (!trend)
                        trend = createList(m);
                    else
                        pos = addToList(&trend, m, compareMovie);
                    
                    if (!trend)
                        return 0;
                    break;
                case 2:
                    if (!doc)
                        doc = createList(m);
                    else
                        pos = addToList(&doc, m, compareMovie);
                    
                    if (!doc)
                       return 0;
                    break;
                case 3:
                    if (!tut)
                        tut = createList(m);
                    else
                        pos = addToList(&tut, m, compareMovie);
                    
                    if (!tut)
                        return 0;
                    break;

                default:
                   fprintf(stderr, "Weird cateogry ID.\n");
                   return 0;
            }

            if (pos == 0)
                pos += 1;

            fprintf(output, 
                    "Serialul %s a fost adaugat la pozitia %d.\n", m->nume, pos);

        }
        else if(!strcmp(token, "add_sez")) {
            token = strtok(NULL, " ");
            TMovie *m = find(trend, doc, tut, top10, token);
            if (!m)
            	m = findMovieQueue(later, token);

            if (!m)
            	m = findMovieStack(watch, token);

            if (!m) {
            	fprintf(stderr, "No show found with that name.\n");
                continue;
            }

            fprintf(output, "Serialul %s are un sezon nou.\n", token);

            int total = 0;

            token = strtok(NULL, " ");
            int ep = atoi(token);

            token = strtok(NULL, " ");
            int *el = (int *)malloc(sizeof(int));
            if (!el)
                goto exit;

            *el = atoi(token);
            total += *el;
            TQueue *q = createQueue(el);
            if (!q) {
                free(el);
                goto exit;
            }

            for(int i = 1; i < ep; i++) {
                    token = strtok(NULL, " ");
                    el = (int *)malloc (sizeof(int));

                    if (!el) {
                        deleteQueue(q, free);
                        goto exit;
                    }

					*el = atoi(token);
					total += *el;

                    addToQueue(q, el); 
            }

            m->sezoane += 1;
            m->time_left += total;

            addToQueue(m->sez, q);
        }
        else if(!strcmp(token, "add_top")) {
        	token = strtok(NULL, " ");
        	int pos = atoi(token);

        	TMovie *m = readMovie();
        	if (!m)
        		goto exit;

        	if (!top10)
        		top10 = createList(m);
        	else
        		addToPosList(&top10, m, pos);

        	checkIfTooLong(&top10, freeMovie);

            fprintf(output, "Categoria top10: ");
            printList(top10, output, printMovie);
        }
        else if(!strcmp(token, "later")) {
        	token = strtok(NULL, " ");
            TMovie *m = findAndRemove(&trend, &doc, &tut, &top10, token);
            if (!m) {
                fprintf(stderr, "No show found with that name.\n");
                continue;
            }

            int pos = 0;

            if (!later)
            	later = createQueue(m);
            else
            	pos = addToQueue(later, m);

            if (pos == 0)
            	pos += 1;

            fprintf(output, "Serialul %s se afla in "
            	"coada de asteptare pe pozitia %d.\n", token, pos);
        }
        else if(!strcmp(token, "watch")) {
            token = strtok(NULL, " ");

            TMovie *m = NULL;
            if (watch)
            	m = findRemoveStack(watch, token);

            if (m && !strcmp(m->nume, token)) {
            	token = strtok(NULL, " ");
            	int len = atoi(token);

            	if (watchMovie(m, len)) {
            		fprintf(output, "Serialul %s "
            			"a fost vizionat integral.\n", m->nume);
            		if (!history)
            			history = createStack(m);
            		else
            			addToStack(history, m);
            	}
            	else
            		addToStack(watch, m);

            	continue;
            }

            m = findAndRemove(&trend, &doc, &tut, &top10, token);
            if(!m)
            	m = findRemoveQueue(later, token);
            if(!m) {
                fprintf(stderr, "No show found with that name.\n");
                continue;
            }

            token = strtok(NULL, " ");
            int len = atoi(token);

            if (watchMovie(m, len)) {
            	fprintf(output, "Serialul %s "
            		"a fost vizionat integral.\n", m->nume);
            	if (!history)
            		history = createStack(m);
            	else
            		addToStack(history, m);
            } else {
            	if (!watch)
            		watch = createStack(m);
            	else
            		addToStack(watch, m);
            }

        }
        else if(!strcmp(token, "show")) {
            token = strtok(NULL, " ");

            if (!strcmp(token, "top10")) {
                fprintf(output, "Categoria %s: ", token);
                printList(top10, output, printMovie);
            }
            else if (!strcmp(token, "later")) {
            	fprintf(output, "Categoria %s: ", token);
            	printQueue(later, output, printMovie);
            }
            else if (!strcmp(token, "watching")) {
            	fprintf(output, "Categoria %s: ", token);
            	printStack(watch, output, printMovie);
            }
            else if (!strcmp(token, "history")) {
            	fprintf(output, "Categoria %s: ", token);
            	printStack(history, output, printMovie);
            }
            else {

                int categ = atoi(token);
                fprintf(output, "Categoria %d: ", categ);

                switch(categ) {
                    case 1:
                        printList(trend, output, printMovie);
                        break;
                    case 2:
                        printList(doc, output, printMovie);
                        break;
                    case 3:
                        printList(tut, output, printMovie);
                        break;
                    default:
                        fprintf(stderr, "Unexpected number in show area.\n");
                        return 0;
                }
            }
        }
    }

exit:
	if (history)
		deleteStack(history, freeMovie);
	if (watch)
		deleteStack(watch, freeMovie);
	if (later)
		deleteQueue(later, freeMovie);
    if (trend)
        deleteList(trend, freeMovie);
    if (doc)
        deleteList(doc, freeMovie);
    if (tut)
        deleteList(tut, freeMovie);
    if (top10)
        deleteList(top10, freeMovie);
    
    fclose(input);
    fclose(output);
    return 0;
}
