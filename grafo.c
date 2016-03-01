#include <stdlib.h>
#include <errno.h>

typedef struct
{
    unsigned int numeroVertices;
    unsigned int numeroArestas;
    unsigned int **matrizAdjacencia;
}Grafo;

Grafo* initGrafo (unsigned int numeroVertices)
{
        Grafo* grafoTemporario;
        unsigned int controlaFor;
        grafoTemporario=(Grafo*)calloc(numeroVertices, sizeof(Grafo));
        if(grafoTemporario==NULL)
        {
                errno=ENOMEM;
                return NULL;
        }
        grafoTemporario->numeroVertices=numeroVertices;
        grafoTemporario->matrizAdjacencia=(unsigned int**)calloc(numeroVertices, sizeof(unsigned int*));
        if (grafoTemporario->matrizAdjacencia==NULL)
        {
                free(grafoTemporario);
                errno=ENOMEM;
                return NULL;
        }
        for(controlaFor=0; controlaFor<numeroVertices; controlaFor++)
        {
                grafoTemporario->matrizAdjacencia[controlaFor]=(unsigned int*)calloc(numeroVertices, sizeof(unsigned int));
                if(grafoTemporario->matrizAdjacencia[controlaFor]==NULL)
                {
                        unsigned int i;
                        for(i=0; i<controlaFor; i++)
                        {
                                free(grafoTemporario->matrizAdjacencia[i]);
                        }
                        free(grafoTemporario->matrizAdjacencia);
                        free(grafoTemporario);
                        errno=ENOMEM;
                        return NULL;
                }
        }
        return grafoTemporario;
}

Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal)
{
        if (grafo==NULL)
                return NULL;
        if(verticeInicial>=grafo->numeroVertices || verticeFinal>=grafo->numeroVertices)
                return grafo;
        grafo->matrizAdjacencia[verticeInicial][verticeFinal]=1;
        grafo->matrizAdjacencia[verticeInicial][verticeFinal]=1;
        grafo->numeroArestas++;
        return grafo;
}

Grafo* addVertice (Grafo* grafo)
{
    unsigned int controlaFor;
    unsigned int** novaMatrizAdjacencia;
    if (grafo==NULL)
        return NULL;
    novaMatrizAdjacencia=(unsigned int**)calloc(grafo->numeroVertices+1, sizeof(unsigned int*));
    if(novaMatrizAdjacencia==NULL)
    {
        errno=ENOMEM;
        return grafo;
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices+1; controlaFor++)
    {
        novaMatrizAdjacencia[controlaFor]=(unsigned int*)calloc(grafo->numeroVertices+1, sizeof(unsigned int));
        if (novaMatrizAdjacencia[controlaFor]==NULL)
        {
            unsigned int i;
            for (i=0; i<controlaFor; i++)
            {
                free(novaMatrizAdjacencia[i]);
            }
            free(novaMatrizAdjacencia);
            errno=ENOMEM;
            return grafo;
        }
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices; controlaFor++)
    {
        unsigned int i;
        for(i=0; i<grafo->numeroVertices; i++)
        {
            novaMatrizAdjacencia[controlaFor][i]=grafo->matrizAdjacencia[controlaFor][i];
        }
    }
    for(controlaFor=0; controlaFor<grafo->numeroVertices ; controlaFor++)
    {
        free(grafo->matrizAdjacencia[controlaFor]);
    }
    free(grafo->matrizAdjacencia);
    grafo->numeroVertices++;
    grafo->matrizAdjacencia=novaMatrizAdjacencia;
    return grafo;
}


