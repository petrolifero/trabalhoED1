#ifndef __grafo_h__
#define __grafo_h__

#include <lista/lista.h>
#include <stdbool.h>

typedef struct grafo Grafo;

Grafo* initGrafo (unsigned int numeroVertices);
void liberaVertice (void* v);
Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal);
Grafo* addVertice (Grafo* grafo);
Grafo* removeAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal);
Grafo* removeVertice (Grafo* grafo, unsigned int vertice);
void liberaGrafo (Grafo* grafo);
void imprimeGrafo(Grafo* grafo);
bool* buscaEmProfundidade (Grafo* g, void (*funcao)(void*));
bool estaConexo (Grafo* grafo);
Lista* djikstra (Grafo* grafo, int nomeOrigem, int nomeDestino);
bool existeCaminho(Grafo* grafo, int nomeOrigem, int nomeDestino);
int numeroVertices (Grafo* grafo);

#endif
