#include <stdlib.h>
#include <dbg.h>
#include <lista/erros.h>
#include <lista/lista.h>
#include <errno.h>

void* Lista_obterValor (No* n)
{
	//macros são genéricos, 
	//podemos usálos para verificar qualquer tipo
    if(Lista_vazia(n))
    {
        errno=EMPTYLIST;
        return NULL;
    }
    return n->info;
}

Lista *Lista_cria(){
	//Da no mesmo que verificar se é null e retornar null
	//vamos encapsular a lista como uma coisa, os nós como outra
	return calloc(1, sizeof(Lista)); 
}

void Lista_destruir(Lista *lista){
	check(!Lista_vazia(lista), "Lista Vazia.");
	check(lista->count > 0 && !Lista_vazia(lista->first), "Lista Vazia.");
	Lista_iterar(lista, first, next, cur){
		if(cur->prev){
			free(cur->prev);
		}
	}

	free(lista->last);
	free(lista);
error:
	return;
}

void Lista_limpar(Lista *lista){
	check(!Lista_vazia(lista), "Lista inválida");
	check(lista->count > 0 && lista->first != NULL, "Lista vazia.");
	Lista_iterar(lista, first, next, cur){
		free(cur->info);
	}
error:
	return;
}

void Lista_limpar_destruir(Lista * lista){
	check(!Lista_vazia(lista), "Lista Invalida.");
	check(lista->count > 0 && lista->first != NULL, "Lista Vazia.");
	Lista_iterar(lista, first, next, cur){
		free(cur->info);
		if(cur->prev){
			free(cur->prev);
		}
	}
error:
	return;
}

void Lista_push(Lista * lista, void *value){
	check(!Lista_vazia(lista), "Lista Inválida");
	No *no = calloc(1, sizeof(No));
	check_mem(no);
	no->info = value;

	if(lista->last == NULL){
		lista->first = no;
		lista->last = no;
	} else {
		lista->last->next = no;
		no->prev = lista->last;
		lista->last = no;
	}

	lista->count++;
error:
	return;
}

void *Lista_pop(Lista * lista){
	check(!Lista_vazia(lista), "Lista Inválida");
	check(lista->count > 0 && lista->first != NULL, "Lista Vazia.");
	No *no = lista->last;
	return no != NULL ? Lista_remover(lista, no) : NULL;
error:
	return NULL;
}

void Lista_unshift(Lista *lista, void *value){
	check(!Lista_vazia(lista), "Lista Inválida");
	No *no = calloc(1, sizeof(No));
	check_mem(no);

	no->info = value;

	if(lista->first == NULL){
		lista->first = no;
		lista->last = no;
	} else {
		no->next = lista->first;
		lista->first->prev = no;
		lista->first = no;
	}

	lista->count++;
error:
	return;
}

void *Lista_shift(Lista * lista){
	check(!Lista_vazia(lista), "Lista Inválida");
	check(lista->count > 0 && lista->first != NULL, "Lista Vazia.");
	No *no = lista->first;
	return no != NULL ? Lista_remover(lista,no) : NULL;
error:
	return NULL;
}

void *Lista_remover(Lista * lista, No * no){
	void *result = NULL;
	check(!Lista_vazia(lista), "Lista Inválida.");
	check(lista->first && lista->last, "Lista vazia");
	check(no, "nó não pode ser NULL");

	if(no == lista->first && no == lista->last){
		lista->first = NULL;
		lista->last = NULL;
	} else if(no == lista->first){
		lista->first = no->next;
		check(lista->first != NULL, "Lista Inválida, De algum modo obteve um primeiro que é NULL.");
		lista->first->prev = NULL;
	} else if(no == lista->last){
		lista->last = no->prev;
		check(lista->last != NULL, "Lista Inválida, de algum modo obteve um prox que é NULL.");
		lista->last->next = NULL;
	} else {
		No *after = no->next;
		No *before = no->prev;
		after->prev = before;
		before->next = after;
	}

	lista->count--;
	result = no->info;
	free(no);
//fallthrough
error:
	return result;
}
