#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <lista/lista.h>
#include <grafo/grafo.h>

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
		int nomeAtual=((Vertice*) No_obterValor(cur))->dado.nome;
		if(nomeAtual==nome)
		{
			return (Vertice*) No_obterValor(cur);
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
		Vertice *tmp=(Vertice*) No_obterValor(cur);
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
	/*Lista_iterar(g->vertices, first, next, cur){
		if(cur) liberaVertice(cur);
	}*/

	Lista_destruir(g->vertices);
	free(g);
}

//imprime finish
void imprime(void* vertice)
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
		int *temporario=(int*) No_obterValor(cur);
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
	buscaEmProfundidadeAux(g,visitados, (Vertice*)No_obterValor(g->vertices->first),funcao);
	return visitados;
}

//imprimeGrafo finish
void imprimeGrafo (Grafo* g)
{
		Lista_iterar(g->vertices, first, next, cur)
		{
				printf("%d %.3f ",((Vertice*) (cur->info))->dado.nome, ((Vertice*)cur->info)->dado.id);
				Lista_iterar(((Vertice*)(cur->info))->vizinhos, first, next, cur2)
				{
						printf("%d %d ", ((Vizinhos*)(cur2->info))->indice, ((Vizinhos*)cur2->info)->custo);
				}
		}
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

int pegaCusto (Grafo* grafo, unsigned int i, unsigned int j)
{
		Lista_iterar(grafo->vertices, first, next, cur)
		{
				if(((Vertice*)(cur->info))->dado.nome==i)
				{
						Lista_iterar(((Vertice*)cur->info)->vizinhos, first, next, cur2)
						{
								if(((Vizinhos*)(cur2->info))->indice==j)
								{
										return ((Vizinhos*)cur2->info)->custo;
								}
						}
				}
		}
		return 0;
}

Grafo* removeAresta (Grafo* grafo, unsigned int i, unsigned int j)
{
		int contador=0;
		Lista_iterar(grafo->vertices, first, next, cur)
		{
				Vertice* tmp=(Vertice*)cur->info;
				if(tmp->dado.nome==i)
				{
						Lista_iterar(tmp->vizinhos, first, next, cur2)
						{
								Vizinhos* tmp2=(Vizinhos*)cur2->info;
								if(tmp2->indice==j)
								{
										Lista_remover_nome(tmp->vizinhos, j);
										contador++;
										if(contador==2)
												return grafo;
										break;
								}

						}
				}
				else if (tmp->dado.nome==j)
				{
						Lista_iterar(tmp->vizinhos, first, next, cur2)
						{
								Vizinhos* tmp2=(Vizinhos*)cur2->info;
								if(tmp2->indice==i)
								{
										Lista_remover_nome(tmp->vizinhos, i);
										contador++;
										if(contador==2)
												return grafo;
										break;
								}

						}
				}


		}
		return NULL;
}

Grafo* removeVertice(Grafo* g, unsigned int nome)
{
		Lista_iterar(g->vertices, first, next, cur)
		{
				Vertice* tmp=(Vertice*)cur->info;
				Lista_remover_nome(tmp->vizinhos, nome);
		}
		{
			Lista_iterar(g->vertices, first, next, cur2)
			{
					Vertice* tmp=(Vertice*)cur2->info;
					if(tmp->dado.nome==nome)
					{
						Lista_remover(g->vertices, cur2);
						return g;
					}
			}
		}
		return 	NULL;
}
