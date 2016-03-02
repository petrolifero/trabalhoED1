typedef struct lista Lista;

Lista* empty (void);
int isEmpty (Lista* l);
Lista* cons (int info, Lista* l);
Lista* cdr (Lista* l);
int car (Lista* l);
