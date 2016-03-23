#ifndef __grafo_h__
#define __grafo_h__

#include <lista/lista.h>

typedef struct
{
	unsigned int nome;
	float id;
}Informacoes;

typedef struct
{
	Informacoes dado;
	Lista* vizinhos;
}Vertice;

typedef struct
{
	unsigned int indice;
	unsigned int custo;
}Vizinhos;

typedef struct
{
    unsigned int numeroVertices;
    unsigned int numeroArestas;
	Lista* vertices;
}Grafo;

typedef struct
{
	Vertices *pai;
	Vertices *filho;
}Parents;

typedef struct
{
	Vertices *heap;
	int custoHeap;
}MinHeap;

typedef struct{
	Verice *no;
	int custoDist;
}Distance;

#define Grafo_numVertices(G) (G->numeroVertices)

Grafo* initGrafo (unsigned int numeroVertices);
void liberaVertice (void* v);
Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal);
Grafo* addVertice (Grafo* grafo);
void liberaGrafo (Grafo* grafo);
void imprimeGrafo(Grafo* grafo);
bool* buscaEmProfundidade (Grafo* g, void (*funcao)(void*));
bool estaConexo (Grafo* grafo);
Lista* djikstra (Grafo* grafo, int nomeOrigem, int nomeDestino);
bool existeCaminho(Grafo* grafo, int nomeOrigem, int nomeDestino);
void imprime(void* vertice);
void imprimeGrafo (Grafo* g);
int pegaCusto (Grafo* grafo, unsigned int i, unsigned int j);
Grafo* removeAresta (Grafo* grafo, unsigned int i, unsigned int j);
Grafo* removeVertice(Grafo* g, unsigned int nome);

#endif
