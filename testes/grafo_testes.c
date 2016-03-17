#include <util/minunit.h>
#include <grafo/grafo.h>
#include <errno.h>

Grafo *a;

char *teste_initGrafo()
{
	a = initGrafo(3);
	mu_assert(a, "Falha na criação");

    return NULL;
}

char *teste_addAresta()
{
	a = addAresta(a,0,1);
	a = addAresta(a,0,2);
	a = addAresta(a,1,2);
    return NULL;
}

char *teste_imprime()
{
	imprimeGrafo(a);

    return NULL;
}

char *teste_libera()
{
    liberaGrafo(a);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(teste_initGrafo);
    mu_run_test(teste_addAresta);
    mu_run_test(teste_imprime);
    mu_run_test(teste_libera);

    return NULL;
}

RUN_TESTS(all_tests);
