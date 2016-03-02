typedef struct grafo Grafo;

Grafo* initGrafo (unsigned int numeroVertices);
Grafo* addAresta (Grafo* grafo, unsigned int verticeInicial, unsigned int verticeFinal);
Grafo* addVertice (Grafo* grafo);
void liberaGrafo (Grafo* grafo);
void imprimeGrafo(Grafo* grafo);
