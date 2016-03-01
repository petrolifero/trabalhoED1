CURRENT=`pwd`
CFLAGS=-Ofast -Wall -Werror -Wextra -std=c11 -fomit-frame-pointer -march=native -I$(CURRENT)


build: support grafo.o
	gcc main.c util/Lista.o grafo.o -o main $(CFLAGS)

support:
	CFLAGS="$(CFLAGS)" make  -C util/
	gcc grafo.c -c -o grafo.o $(CFLAGS)
