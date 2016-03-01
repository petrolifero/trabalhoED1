#include <stdlib.h>
#include <include/lista/erros.h>

typedef struct
{
    int info;
    struct Lista* next;
}Lista;

inline Lista* empty ()
{
    return NULL;
}

inline int isEmpty (Lista* l)
{
    return l==NULL;
}

Lista* cons (int info, Lista* l)
{
    Lista* tmp;
    tmp=(Lista*)calloc(1,sizeof(Lista));
    if(tmp==NULL)
    {
        return NULL;
    }
    tmp->info=info;
    tmp->next=l;
    return tmp;
}

Lista* cdr (Lista* l)
{
    if(isEmpty(l))
    {
        errno=EMPTYLIST;
        return NULL;
    }
    return l->next;
}

int car (Lista* l)
{
    if(isEmpty(l))
    {
        errno=EMPTYLIST;
        return -1;
    }
    return l->info;
}


