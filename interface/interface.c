#include <grafo/grafo.h>
#include <dbg.h>
#include <stdio.h>

#define MAXBUF 1024

Grafo *recuperarGrafo(FILE *arquivo);

int main(int argc, char *argv[]){
	FILE *arquivo;
	Grafo *g;
	char acao='c';
	char *rc;
	if(argc == 1){
		char buffer[MAXBUF];
		printf("Digite o nome do arquivo contendo as informações do grafo: \n");
		rc = fgets(buffer, MAXBUF, stdin);
		check(rc, "Erro na inserção do nome.");
		buffer[MAXBUF-1] = '\0';
		arquivo = fopen(buffer, "r");
		check(arquivo, "O arquivo não pode ser aberto.");
	} else{
		char *buffer = argv[1];
		arquivo = fopen(buffer, "r");
		check(arquivo, "O arquivo não pode ser aberto. Modo de uso: ./interface <nome do arquivo>");
	}

	g = recuperarGrafo(arquivo);
	check(g, "Falha na criação do grafo. Seu arquivo é no formato correto?");
	while(acao != 's'){
		printf("Digite a ação: ");
		check(scanf("%c%*c", &acao) == 1, "Passe uma das ações aceitas: 'l':listar vértices e custos\n 'a':adicionar vértice\n 'A':adicionar aresta \n \
				'r':remover vértice \n 'R':remover aresta \n 'v':verificar se o grafo é conexo \n 'c':encontrar caminho\n 's':sair");

		unsigned int inicio, fim, v;
		//Se não pedimos ao usuario o peso da aresta, valor é desnecessario
	//	double valor;
		switch(acao){
			case 'l':
				imprimeGrafo(g);
				break;
			case 'a':
				addVertice(g);
				printf("Vértice adicionado à rede.\n");
				break;
			case 'A':
				printf("\tDigite os indices inicial e final da aresta separados por espaço:\n");
				check(scanf("%u %u", &inicio, &fim)== 2, "É necessário que sejam digitados dois índices.");
				addAresta(g, inicio, fim);
				break;
			case 'r':
				printf("\tDigite o indice do vértice:\n");
				check(scanf("%u", &v) == 1, "É necessário que seja digitado um índice.");
				liberaVertice((void *) &v);
				break;
			case 'R':
				printf("\tDigite os indices inicial e final da aresta:\n");
				check(scanf("%u %u", &inicio, &fim)== 2, "É necessário que sejam digitados dois índices.");
				removeAresta(g, inicio, fim);
				break;
			case 'v':
				if(estaConexo(g)) printf("\tO Grafo é conexo.\n");
				else printf("\tO Grafo não é conexo.\n");
				break;
			case 'c':
				printf("\tDigite os indices inicial e final para saber se há um caminho:\n");
				check(scanf("%u %u", &inicio, &fim)== 2, "É necessário que sejam digitados dois índices.");
				if(existeCaminho(g, inicio, fim)){
					printf("\tExiste um caminho, e o caminho mínimo é:\n");
					Lista_imprimir(djikstra(g, inicio, fim));
				}
				break;
			case 's':
				imprimeGrafo(g);
				if(estaConexo(g)) printf("\tO Grafo é conexo.\n");
				else printf("\tO Grafo não é conexo.\n");
				printf("\t----\n");
				break;
			default:
				printf("Ações aceitas: 'l':listar vértices e custos\n 'a':adicionar vértice\n 'A':adicionar aresta \n \
				'r':remover vértice \n 'R':remover aresta \n 'v':verificar se o grafo é conexo \n 'c':encontrar caminho\n 's':sair\n");
				break;
		}
	}

	fclose(arquivo);
	return 0;
error:
	return 1;
}

Grafo *recuperarGrafo(FILE *arquivo){
	int tamanho=1, rc, i = 0, vizinho, id;
	//double nome;
	Grafo *grafo = initGrafo(1);
	
	
/*
	for(i = 0; i < tamanho; i++){
		grafo = addVertice(grafo);
		id = numeroVertices(grafo) - 1;
		//rc = fread(&id, sizeof(int), 1, arquivo);
		//rc = fread(&nome, sizeof(double), 1, arquivo);
		do{
			rc = fread(&vizinho, sizeof(int), 1, arquivo);
			grafo = addAresta(grafo, id, vizinho);
		}while(rc == 1);
	}*/
	return initGrafo(1);
error:
	return NULL;
}
