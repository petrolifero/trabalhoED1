#include <grafo.h>

int main(void)
{
	Grafo* a;
	a=initGrafo(3);
	a=addAresta(a,0,1);
	a=addAresta(a,0,2);
	a=addAresta(a,1,2);
	imprimeGrafo(a);
	liberaGrafo(a);
	return 0;
}
