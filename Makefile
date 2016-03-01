CFLAGS="-Ofast -Wall -Werror -Wextra -std=c11 -fomit-frame-pointer -march=native"

build: support grafo.o
	gcc grafo.o util/Lista.o -o grafo $(CFLAGS)

support:
	make  -C util/
