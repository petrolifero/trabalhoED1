#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include "lista/lista.h"

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

Grafo* initGrafo (unsigned int numeroVertices)
{
	Grafo* tmp;
	int i;
	srand(time(NULL));
	tmp=(Grafo*)calloc(1, sizeof(Grafo));
	if(tmp==NULL)
	{
			errno=ENOMEM;
			return NULL;
	}
	tmp->numeroVertices=numeroVertices;
	tmp->numeroArestas=0;
	tmp->vertices=listaInit(liberaVertice);
	for(i=0; i<numeroVertices; i++)
	{
			Vertice *add, *temporario;
			add=(Vertice*) calloc(1, sizeof(Vertice));
			if(add==NULL)
			{
					listaLibera(tmp->vertices);
					free(tmp);
					errno=ENOMEM;
					return NULL;
			}
			add->dado.nome=i;
			add->dado.id=(rand()%1000)/1000;
			add->vizinhos=listaInit();
			temporario=cons((void*)add,tmp->vertices);
			if(temporario==NULL)
			{
				listaLibera(add);
				listaLibera(tmp->vertices);
				free(tmp);
				errno=ENOMEM;
				return NULL;
			}
			tmp->vertices=temporario;
	}
	return tmp;
}

Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal)
{
		Vertice *tmp;
		grafo->numeroArestas++;
		for(tmp=grafo->vertices; tmp; tmp=tmp->
}

Grafo* addVertice (Grafo* grafo)
{
    unsigned int controlaFor;
    unsigned int** novaMatrizAdjacencia;
    if (grafo==NULL)
        return NULL;
    novaMatrizAdjacencia=(unsigned int**)calloc(grafo->numeroVertices+1, sizeof(unsigned int*));
    if(novaMatrizAdjacencia==NULL)
    {
        errno=ENOMEM;
        return grafo;
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices+1; controlaFor++)
    {
        novaMatrizAdjacencia[controlaFor]=(unsigned int*)calloc(grafo->numeroVertices+1, sizeof(unsigned int));
        if (novaMatrizAdjacencia[controlaFor]==NULL)
        {
            unsigned int i;
            for (i=0; i<controlaFor; i++)
            {
                free(novaMatrizAdjacencia[i]);
            }
            free(novaMatrizAdjacencia);
            errno=ENOMEM;
            return grafo;
        }
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices; controlaFor++)
    {
        unsigned int i;
        for(i=0; i<grafo->numeroVertices; i++)
        {
            novaMatrizAdjacencia[controlaFor][i]=grafo->matrizAdjacencia[controlaFor][i];
        }
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices ; controlaFor++)
    {
        free(grafo->matrizAdjacencia[controlaFor]);
    }
    free(grafo->matrizAdjacencia);
    grafo->numeroVertices++;
    grafo->matrizAdjacencia=novaMatrizAdjacencia;
    return grafo;
}

void liberaGrafo(Grafo* g)
{
	if (g)
	{
		unsigned int controlaFor;
		for(controlaFor=0; controlaFor<g->numeroVertices; controlaFor++)
		{
			free(g->matrizAdjacencia[controlaFor]);
		}
		free(g->matrizAdjacencia);
		free(g);
	}
}

void imprimeGrafo (Grafo* g)
{
	if (g!=NULL)
	{
		unsigned int controlaFor;
		for(controlaFor=0; controlaFor<g->numeroVertices; controlaFor++)
		{
			unsigned int indiceVizinhos;
			printf("%d: ", controlaFor);
			for(indiceVizinhos=0; indiceVizinhos<g->numeroVertices; indiceVizinhos++)
			{
				if(g->matrizAdjacencia[controlaFor][indiceVizinhos])
				{
					printf("%d ", indiceVizinhos);
				}
			}
			putchar('\n');
		}
	}
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
	visitados[vertice->informacoes.nome]=true;
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

//pegaVertice finish
Vertice* pegaVertice(Grafo* grafo, int nome)
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
}
