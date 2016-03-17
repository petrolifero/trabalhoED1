#include <util/minunit.h>
#include <lista/lista.h>
#include <assert.h>

static Lista *lista = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_criacao(){
	lista = Lista_cria();
	mu_assert(lista != NULL, "Falha na criação da lista.");

	return NULL;
}

char *test_destruicao(){
	Lista_destruir(lista);
	return NULL;
}

char *test_push_pop(){
	Lista_push(lista, test1);
	mu_assert(Lista_last(lista) == test1, "wrong last value");

	Lista_push(lista, test2);
	mu_assert(Lista_last(lista) == test2, "wrong last value");

	Lista_push(lista, test3);
	mu_assert(Lista_last(lista) == test3, "wrong last value.");

	mu_assert(Lista_count(lista) == 3, "wrong count on push");

	char *val = Lista_pop(lista);
	mu_assert(val == test3, "Wrong value on pop.");

	val = Lista_pop(lista);
	mu_assert(val == test2, "Wrong value on pop.");
	
	val = Lista_pop(lista);
	mu_assert(val == test1, "Wrong value on pop.");

	mu_assert(Lista_count(lista) == 0, "Wrong count after pop.");

	return NULL;
}

char *test_push(){
	Lista_push(lista, test1);
	mu_assert(Lista_last(lista) == test1, "wrong last value");

	Lista_push(lista, test2);
	mu_assert(Lista_last(lista) == test2, "wrong last value");

	Lista_push(lista, test3);
	mu_assert(Lista_last(lista) == test3, "wrong last value.");

	mu_assert(Lista_count(lista) == 3, "wrong count on push");
	return NULL;

}

char *test_unshift(){
	Lista_unshift(lista, test1);
	mu_assert(Lista_first(lista) == test1, "Wrong first value.");

	Lista_unshift(lista, test2);
	mu_assert(Lista_first(lista) == test2, "Wrong first value");
	
	Lista_unshift(lista, test3);
	mu_assert(Lista_first(lista) == test3, "Wrong last value.");
	mu_assert(Lista_count(lista) == 3, "Wrong count on unshift.");

	return NULL;
}

char *test_remocao(){
	// we only need to test the middle remove case since push/shift
	// already tests the other cases
	
	char *val = Lista_remover(lista, lista->first->next);
	mu_assert(val == test2, "Wrong removed element.");
	mu_assert(Lista_count(lista) == 2, "Wrong count after remove.");
	mu_assert(Lista_first(lista) == test3, "Wrong first after remove.");
	mu_assert(Lista_last(lista) == test1, "Wrong last after remove.");
	
	return NULL;	
}

char *test_shift(){
	mu_assert(Lista_count(lista) != 0, "Wrong count before shift.");
		
	char *val = Lista_shift(lista);
	mu_assert(val == test3, "Wrong value on shift.");
	
	val = Lista_shift(lista);
	mu_assert(val == test1, "Wrong value on shift.");
	mu_assert(Lista_count(lista) == 0, "Wrong count after shift.");
	
	return NULL;	
}

char *all_tests(){
	mu_suite_start();
	
	mu_run_test(test_criacao);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remocao);
	mu_run_test(test_shift);
	mu_run_test(test_push);
	mu_run_test(test_destruicao);

	return NULL;
}

RUN_TESTS(all_tests);
