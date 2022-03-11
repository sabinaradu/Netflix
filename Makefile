CC=gcc
CFLAGS=-Wall -g -std=c99
FILES = tema2.c list.c movie.c queue.c stack.c
BIN = tema2

build: $(FILES)
	$(CC) $(FILES) -o $(BIN) $(CFLAGS)

run: build
	./$(BIN)

clean:
	rm -f $(BIN)
