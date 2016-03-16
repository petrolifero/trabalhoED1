#include <stdbool.h>

typedef struct lista Lista;



Lista* listaInit (void);
bool isEmpty (Lista* l);
Lista* cons (int info, Lista* l);
Lista* cdr (Lista* l);
void* car (Lista* l);
