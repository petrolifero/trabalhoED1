#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <lista/lista.h>

typedef struct
{
		int nome;
		float id;
}Informacoes;

typedef struct
{
		Informacoes dado;
		Lista* vizinhos;
}Vertice;

typedef struct
{
    unsigned int numeroVertices;
    unsigned int numeroArestas;
	Lista* vertices;
}Grafo;

//pegaVertice finish
static Vertice* pegaVertice(Grafo* grafo, int nome)
{
	Lista* vertices;
	for(vertices=grafo->vertices; !estaVazia(vertices); vertices=cdr(vertices))
	{
		int nomeAtual=((Vertice*)car(vertices))->dado.nome;
		if(nomeAtual==nome)
		{
			return (Vertice*)car(vertices);
		}
	}
	return NULL;
}

Grafo* initGrafo (unsigned int numeroVertices)
{
}

Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal)
{
	Lista* v;
	unsigned int contador=0;
	for(v=grafo->vertices; !estaVazia(v)&&contador!=2; v=cdr(v))
	{
		Vertice *tmp=(Vertice*) car(v);
		if(tmp->dado.nome == verticeInicial)
		{
			int *i=(int*)calloc(1,sizeof(int));
			Lista *tentativadeCons;
			*i=verticeFinal;
			
		}
	}
}


//addVertice finish
Grafo* addVertice (Grafo* grafo)
{
	Vertice *tmp=(Vertice*)calloc(1, sizeof(Vertice));
	Lista* tentativaDeCons;
	if(tmp==NULL)
	{
		errno=ENOMEM;
		return NULL;
	}
	tmp->vizinhos=listaInit(free);
	tmp->dado.nome=grafo->numeroVertices;
	tmp->dado.id=(rand()%1000)/1000;
	tentativaDeCons=cons((void*)tmp, grafo->vertices);
	if(tentativaDeCons==NULL)
	{
		listaLibera(vizinhos);
		free(tmp);
		errno=ENOMEM;
		return NULL;
	}
	grafo->numeroVertices++;
	grafo->vertices=tentativaDeCons;
	return grafo;
}

//liberaGrafo finish
void liberaGrafo(Grafo* g)
{
	listaLibera(g->vertices);
	free(g);
}

//imprime finish
static void imprime(void* vertice)
{
	Vertice* tmp=(Vertice*)vertice;
	printf("%d\n", tmp->dado.nome);
}

//imprimeGrafo finish
void imprimeGrafo (Grafo* g)
{
	buscaEmProfundidade(g,imprime);
}

//estaConexo finish
bool estaConexo (Grafo* grafo)
{
	int i;
	bool* visitados=buscaEmProfundidade(grafo,NULL);
	for(i=0; i<grafo->numeroVertices; i++)
	{
		if(!visitados[i])
		{
			return false;
		}
	}
	return true;
}


//buscaEmProfundidade finish
bool* buscaEmProfundidade (Grafo* g, void (*funcao)(void*))
{
	bool *visitados;
	visitados=(bool*)calloc(g->numeroVertices, sizeof(bool));
	if(visitados==NULL)
	{
		errno=ENOMEM;
		return NULL;
	}
	buscaEmProfundidadeAux(g,visitados, (Vertice*)car(g->vertices),funcao);
	return visitados;
}







//buscaEmProfundidadeAux finish
static void buscaEmProfundidadeAux (Grafo* grafo, bool* visitados, Vertice* vertice, void (*funcao) (void*))
{
	Lista *tmp;
	visitados[vertice->dado.nome]=true;
	if(funcao!=NULL)
	{
		funcao(vertice);
	}
	for(tmp=vertice->vizinhos; !estaVazia(tmp); tmp=cdr(tmp))
	{
		int *temporario=(int*)car(tmp);
		if(!visitados[*temporario])
		{
			buscaEmProfundidadeAux(grafo,visitados,pegaVertice(grafo, *temporario), funcao);
		}
	}
}





Lista* dijsktra (Grafo* grafo, int nomeOrigem, int nomeDestino)
{
	return NULL;
}
