#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <lista/lista.h>
#include <grafo/grafo.h>

typedef struct
{
	unsigned int nome;
	float id;
}Informacoes;

typedef struct
{
	int indice;
	int custo;
}Vizinhos;

typedef struct
{
	Informacoes dado;
	Lista* vizinhos;
}Vertice;

typedef struct grafo
{
    unsigned int numeroVertices;
    unsigned int numeroArestas;
	Lista* vertices;
}Grafo;


void liberaVertice (void* v)
{
	Vertice *vertice=(Vertice*)v;
	if (v==NULL) return;
	Lista_destruir(vertice->vizinhos);
	free(vertice);
}

//pegaVertice finish
static Vertice* pegaVertice(Grafo* grafo, int nome)
{
	Lista_iterar(grafo->vertices, first, next, cur){
		int nomeAtual=((Vertice*) Lista_obterValor(cur))->dado.nome;
		if(nomeAtual==nome)
		{
			return (Vertice*) Lista_obterValor(cur);
		}
	}
	return NULL;
}

//addVertice finish
Grafo* addVertice (Grafo* grafo)
{
	Vertice *tmp=(Vertice*)calloc(1, sizeof(Vertice));
	if(tmp==NULL)
	{
		errno=ENOMEM;
		return NULL;
	}
	tmp->vizinhos=Lista_cria(free);
	tmp->dado.nome=grafo->numeroVertices;
	tmp->dado.id=(rand()%1000)/1000;
	Lista_unshift(grafo->vertices, (void *) tmp);
	grafo->numeroVertices++;
	return grafo;
}

//initGrafo finish
Grafo* initGrafo (unsigned int numeroVertices)
{
	Grafo* tmp;
	unsigned int i;
	tmp=(Grafo*)calloc(1, sizeof(Grafo));
	tmp->vertices = Lista_cria(liberaVertice);
	for(i=0; i<numeroVertices; i++)
	{
		tmp=addVertice(tmp);
	}
	return tmp;
}

//addAresta finish
Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal)
{
	unsigned int contador=0;
	
	Lista_iterar(grafo->vertices, first, next, cur){
		if(contador == 2) break;
		Vertice *tmp=(Vertice*) Lista_obterValor(cur);
		int *i=(int*)calloc(1,sizeof(int));
		if(tmp->dado.nome == verticeInicial)
		{
			*i=verticeFinal;
		}
		else if(tmp->dado.nome == verticeFinal)
		{
			*i=verticeInicial;
		}	
		Lista_unshift(tmp->vizinhos, (void *) i);
		contador++;
	}

	return grafo;
}

//liberaGrafo finish
void liberaGrafo(Grafo* g)
{
	Lista_iterar(g->vertices, first, next, cur){
		if(cur) liberaVertice(cur);
	}

	Lista_destruir(g->vertices);
	free(g);
}

//imprime finish
static void imprime(void* vertice)
{
	Vertice* tmp=(Vertice*)vertice;
	printf("%d\n", tmp->dado.nome);
}

//buscaEmProfundidadeAux finish
static void buscaEmProfundidadeAux (Grafo* grafo, bool* visitados, Vertice* vertice, void (*funcao) (void*))
{
	visitados[vertice->dado.nome]=true;
	if(funcao!=NULL)
	{
		funcao(vertice);
	}
	Lista_iterar(vertice->vizinhos, first, next, cur){
		int *temporario=(int*) Lista_obterValor(cur);
		if(!visitados[*temporario])
		{
			buscaEmProfundidadeAux(grafo,visitados,pegaVertice(grafo, *temporario), funcao);
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
	buscaEmProfundidadeAux(g,visitados, (Vertice*)Lista_obterValor(g->vertices->first),funcao);
	return visitados;
}

//imprimeGrafo finish
void imprimeGrafo (Grafo* g)
{
	buscaEmProfundidade(g,imprime);
}

//estaConexo finish
bool estaConexo (Grafo* grafo)
{
	unsigned int i;
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


Lista* dijsktra (Grafo* grafo, int nomeOrigem, int nomeDestino)
{
		
	return NULL;
}

//existeCaminho finish
bool existeCaminho(Grafo* grafo, int nomeOrigem, int nomeDestino)
{
	Lista* tmp = dijsktra(grafo,nomeOrigem,nomeDestino);
	if(Lista_vazia(tmp))
	{
		Lista_destruir(tmp);
		return false;
	}
	Lista_destruir(tmp);
	return true;
}

int numeroVertices(Grafo* grafo)
{
		return grafo->numeroVertices;
}
