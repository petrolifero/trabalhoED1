#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUMEROMAXARESTAS (n-2)

void usage(char* nome)
{
		fprintf(stderr, "%s numeroVertices\n", nome);
}


int main(int argc, char* argv[])
{
		int i,j;
		int n;
		int contador=0;
		FILE* fp=fopen("grafo.txt", "w");
		if(!fp)
		{
				fprintf(stderr, "Algo deu errado na abertura do arquivo\nfavor verificar as permissoes");
				return -1;
		}

		srand(time(NULL));
		if(argc!=2)
		{
				usage(argv[0]);
				return -1;
		}
		n=atoi(argv[1]);
		int matriz[n][n];
		for(i=0; i<n; i++)
		{
				for(j=0; j<n; j++)
				{
						matriz[i][j]=0;
				}
		}

		while(contador<NUMEROMAXARESTAS)
		{
				int k=rand()%n;
				int l=rand()%n;
				matriz[k][l]=rand()%100+1;
				matriz[l][k]=matriz[k][l];
				contador++;
		}


		for(i=0; i<n; i++)
		{
				fprintf(fp, "%d %.3f ", i, (rand()%1000)/1000.0);
				for(j=0; j<n; j++)
				{
						if(matriz[i][j])
						{
								fprintf(fp,"%d %d ", j, matriz[i][j]);
						}
				}
				fputc('\n', fp);
		}
		fclose(fp);
		return 0;
}
