#include <grafo/grafo.h>
#include <string/bstrlib.h>
#include <util/dbg.h>
#include <stdio.h>

#define MAXBUF 1024

Grafo *recuperarGrafo(FILE *arquivo);

int main(int argc, char *argv[]){
	FILE *arquivo;
	Grafo *g;
	char acao;
	int rc;
error:
	if(argc == 1){
		char buffer[MAXBUF];
		printf("Digite o nome do arquivo contendo as informações do grafo: \n");
		rc = scanf("%s", buffer);
		check(rc == 1, "Erro na inserção do nome.");
		buffer[MAXBUF-1] = '\0';

		arquivo = fopen(buffer, "r");
		check(arquivo, "O arquivo não pode ser aberto.");
	} else{
		char *buffer = argv[1];
		arquivo = fopen(buffer, "r");
		check(arquivo, "O arquivo não pode ser aberto. Modo de uso: ./interface <nome do arquivo>");
	}
	g = recuperarGrafo(arquivo);
	while(acao != 's'){
		rc = scanf("%c", &acao);
		check(rc == 1, "Passe uma das ações aceitas: 'l':listar vértices e custos\n 'a':adicionar vértice\n 'A':adicionar aresta \n \
				'r':remover vértice \n 'R':remover aresta \n 'v':verificar se o grafo é conexo \n 'c':encontrar caminho\n 's':sair");

		/*
		 *	TODO: identificação das opções do usuário
		 *
		 */
	}

	fclose(arquivo);
	return 0;
}

Grafo *recuperarGrafo(FILE *arquivo){
	/*
	 *	TODO: Parsing do arquivo para um grafo
	 */
	return initGrafo(1);
}
