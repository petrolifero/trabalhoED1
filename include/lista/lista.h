#ifndef __lista_h__
#define __lista_h__

#include <stdbool.h>

/*No de cada elemento, contido na lista*/
typedef struct no
{
    void *info;
    struct no* next;
    struct no* prev;
}No;

/*A lista, que contem os nós*/
typedef struct lista {
	int count;
	No *first;
	No *last;
}Lista;

/*Itera na lista*/
#define Lista_iterar(L, S, M, V) No *_no = NULL;\
				No *V = NULL;\
for(V = _no = L->S; _no != NULL; V = _no = _no->M)

/*Retorna se a lista está vazia*/
#define Lista_vazia(L) (L == NULL)

/*Retorna o primeiro no da lista*/
#define Lista_first(A) ((A)->first != NULL ? (A)->first->info : NULL)

/*Retorna o último nó da lista*/
#define Lista_last(A) ((A)->last != NULL ? (A)->last->info : NULL)

/*Dá o proximo no (substituto de "cdr")*/
#define Lista_prox(N) ((N) != NULL ? (N)->prox : NULL)

/*Dá o tamanho da lista*/
#define Lista_count(A) ((A)->count)

void* Lista_obterValor (No* l);

/*Cria uma nova lista*/
Lista *Lista_cria();

/*Libera os elementos da @lista, destruindo-os*/
void Lista_destruir(Lista *lista);

/*Limpa a @lista liberando os valores dos nós*/
void Lista_limpar(Lista *lista); 

/*Limpa e libera a @lista*/
void Lista_limpar_destruir(Lista *lista);

/*Insere @value no fim da @lista*/
void Lista_push(Lista *lista, void *value);

/*Retira o último elemento da @lista*/
void *Lista_pop(Lista *lista);

/*Adiciona o @value à @lista*/
void Lista_unshift(Lista *lista, void *value);

/*Remove o @no da @lista*/
void *Lista_remover(Lista *lista, No *no);

/*Clears the elements of a list and destroys their values*/
void *Lista_shift(Lista *lista);

#endif
