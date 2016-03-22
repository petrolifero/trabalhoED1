#include <stdlib.h>
#include <errno.h>
#include <lista/lista.h>
#include <lista/erros.h>
#include <util/dbg.h>

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

Lista *Lista_cria(void (*liberaFunction) (void*)){
	//Da no mesmo que verificar se é null e retornar null
	//vamos encapsular a lista como uma coisa, os nós como outra
	Lista* tmp=calloc(1, sizeof(Lista));
	if(!tmp)
	{
		errno=ENOMEM;
		return NULL;
	}
	tmp->liberaElemento=liberaFunction;
	return tmp;
}

void Lista_destruir(Lista *lista){
	check(!Lista_vazia(lista), "Lista Vazia.");
	check(lista->count > 0 && !Lista_vazia(lista->first), "Lista Vazia.");
	Lista_iterar(lista, first, next, cur){
		lista->liberaElemento(cur->info);
		if(cur->prev){
			free(cur->prev);
		}
	}

	free(lista->last);
	free(lista);

	//esse label não era chamado em nenhuma parte da função
	//e se não existir um bom motivo, quero evitar goto's
	error:
	//desnecessario numa função void
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

	//esse label não era chamado em nenhuma parte da função
	//e se não existir um bom motivo, quero evitar goto's
	error:

	//desnecessario  numa função void
	return;
}

void *Lista_pop(Lista * lista){
	check(!Lista_vazia(lista), "Lista Inválida");
	check(lista->count > 0 && lista->first != NULL, "Lista Vazia.");
	No *no = lista->last;
	return no != NULL ? Lista_remover(lista, no) : NULL;

	//esse label não era chamado em nenhuma parte da função
	//e se não existir um bom motivo, quero evitar goto's
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

void Lista_imprimir(Lista* l)
{
		int *i;
		if(Lista_vazia(l))
		{
				return;
		}
		i=(int*)l->first->info;
		printf("%d ", *i);
		Lista_imprimir(Lista_prox(l));
}


void Lista_remover_val (Lista* l, void *val)
{
	Lista_iterar(l, first, next, cur){
		if(cur->info == nome) Lista_remover(l, cur);
	}
}

void Lista_remover_nome(Lista *lista, int nome){
	Lista_remover_val(lista, (void *) &nome);
}
