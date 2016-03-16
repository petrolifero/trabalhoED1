#include <stdbool.h>

typedef struct lista Lista;



Lista* listaInit (void (*funcao) (void*));
bool estaVazia (Lista* l);
Lista* cons (void* info, Lista* l);
Lista* cdr (Lista* l);
void* car (Lista* l);
void listaLibera(Lista* l);
