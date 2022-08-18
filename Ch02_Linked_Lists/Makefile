#
# Makefile
# rzavalet, 2022-06-18 20:02
#

CC = gcc
CFLAGS = -ggdb -O0 
ASAN_FLAGS = -fsanitize=address -fsanitize=leak 
LIBS =
BIN = ./bin

all:
	@echo "Makefile needs your attention"

utils.o : utils.c
	$(CC) -c -o $(BIN)/$@ $^ $(CFLAGS) $(ASAN_FLAGS) $(LIBS)

% : %.c
	mkdir -p bin
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(ASAN_FLAGS) $(LIBS)

vis: res/graph.dot
	dot -Tpng < res/graph.dot > res/graph.png
	xdg-open res/graph.png

.PHONY = clean

clean:
	rm $(BIN)/*

# vim:ft=make
#
