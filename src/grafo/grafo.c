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



void updateDistance(Grafo *grafo, Distance *dist,int newDistance, Vertices *cur2){
			int tam = grafo->numeroVertices;
				int i;	
					for(i = 0; i < tam; i++){
									if(dist[i]->no->dado->nome == cur2->dado->nome){
														dist[i]->no->custo = newDistance;
																	return;
																			}
										}
}
int getDistance(Grafo *grafo,Distance *dist, Vertices *cur2){
			int tam = grafo->numeroVertices;
				int i;	
					for(i = 0; i < tam; i++){
									if(dist[i]->no->dado->nome == cur2->dado->nome){
														return dist[i]->no->custo; 
																}
										}
						return -1;
}
void updateParent(Parents *p, Vertices *v, Vertices *c){
			int i;
				while(p[i]->filho != NULL){
								i++;
									}
					p[i]->filho = v;
						p[i]->pai =c; 
}

bool existOnHeap(Minheap *heap, Vertices *cur2){
			//Percorrer todos os vertices da heap, e ver se ainda existe
			for(i = 0; i < tam; i++){
							if(heap[i]->heap != NULL){
												if(heap[i]->heap->dado->nome == cur2->dado->nome){
																		return true;
																					}
														}
								}
				return false;
}

MinHeap *extractMinNode(MinHeap *heap){
			int min = heap[0]->custoHeap;
				int temp,ind;
					for(i = 1; i < tam; i++){
									temp = heap[i]->custoHeap;
											if(temp < min){
																min = temp;
																			ind = i;
																					}
												}
						return heap[ind];
}

bool HeapEmpty(MinHeap *aux){
			if(aux == NULL) return true;
				return false;
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
	if(grafo != NULL){
		int tam = grafo->numeroVertices;
		int i,j;
		Lista *minPath = Lista_cria(free);								
		MinHeap *minNodes = (MinHeap*) calloc(tam,sizeof(MinHeap));
		Distance *dist = (Distance*) calloc(tam,sizeof(MinHeap));
		Parents *parent = (Parents*) calloc(tam,sizeof(Distance));
		Vertice current;
		for(i = 0; i < tam; i++){
			current = grafo->pegaVertice(grafo,i);
			parent[i]->pai = NULL;
			parent[i]->filho = NULL;
			minNodes[i]->heap = current;
			minNodes[i]->custo = 999:
			dist[i]->no = current;
		}
		minNodes[nomeOrigem]->custo = 0;
		parent[nomeOrigem]->filho = grafo->pegaVertice(grafo,nomeOrigem);
		Lista_push(minPath,parent[nomeOrigem]->filho);
		while(HeapEmpty(MinHeap)){
			MinHeap *minNode = extractMinNode(minNodes);
			current = minNode->heap;
			//atualizarDistance
			updateDistance(grafo,dist,minNode->custoHeap,current);
			Lista_iterar(((Vertice*)(minNode->info))->vizinhos, first, next, cur2)
			{
				if(!existOnHeap(minNodes,cur2)){
					continue;
				}
				int newDistance = getDistance(grafo,dist,current) + pegaCusto(grafo,current,cur2) //Como pegaria o custo ate o vertice cur2?
				if(newDistance < minNodes.getWeight(cur2)){					
					updateDistance(grafo,dist,newDistance,cur2); //ATTUALIZA A NOVA DISTANCIA NO NO CORRESPONDENTE DA LISTA DIST
					updateParent(parent,cur2,current); //ATUALIZA O PARENTESCO ENTRE O NOATUAL COM O ANTERIOR NA LISTA PARENT
					Lista_push(minPath,cur2);
				}
			}
		} 
		return minPath;
	}	
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
