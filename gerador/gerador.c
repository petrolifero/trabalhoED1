#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <lista/lista.h>
#include <time.h>
#include <grafo/grafo.h>

void usage(const char* nameOfProgram)
{
		fprintf(stderr, "usage : %s -n numberOfNodes -k meanDegree -b probability\n\nmeanDegree is even\n", nameOfProgram);
}


int parseInput(int argc, char *argv[], int *n, int *k, float *b)
{
	int i;
	*n=0;
	*k=0;
	*b=0;
	for(i=1; i<argc; i++)
	{
			if(!strcmp(argv[i], "-n") && i+1<argc)
			{
					char *receiveDigitError;
					*n=strtol(argv[i+1],&receiveDigitError , 10);
					if(*receiveDigitError!='\0')
					{
							*n=0;
							*k=0;
							*b=0;
							return -1;
					}
			}
			else if(!strcmp(argv[i], "-k") && i+1<argc)
			{
					char *receiveDigitError;
					*k=strtol(argv[i+1],&receiveDigitError , 10);
					if(*receiveDigitError!='\0')
					{
							*n=0;
							*k=0;
							*b=0;
							return -1;
					}
	
			}
			else if(!strcmp(argv[i], "-b") && i+1<argc)
			{
					char *receiveDigitError;
					*b=strtod(argv[i+1],&receiveDigitError);
					if(*receiveDigitError!='\0')
					{
							*n=0;
							*k=0;
							*b=0;
							return -1;
					}
	
			}
	}
	if(*n<=0 || *k<=0 || *b<0.0 || *b>1|| *k%2!=0)
	{
		return -1;
	}
	return 0;
}



int writeSmallWorld(int n, int k, float beta)
{
	int i,j;
	srand(time(NULL));

	typedef struct 
	{
			int i,j;
	}trocaArestas;

	Lista* colocacaoArestas=Lista_Cria(free);
	for(i=n-1; i>=0; i--) //para cada vertice
	{
			float indice = ((float)(rand()%1000))/1000.0;
			printf("%d %.3f ", i, indice);
			for(j=0; j<n; j++) //para cada possivel vizinho
			{
					int edgeOnLattice=abs(i-j)%(n-1-k/2);
					float perderAresta = (rand()%1000)/1000.0;
					float ganharAresta = (rand()%1000)/1000.0;
					int c;
					if((c=temAlgumaTroca(colocacaoArestas,i,j) )!=-1)
					{
							int custo=rand()%100+1;
							printf("%d %d", j, custo);
							Lista_remove();
					}
					
			}
			putchar('\n');
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int n, k;
	float beta;
	if(argc<4)
	{
		usage(argv[0]);
		return -1;
	}
	if(!parseInput(argc, argv, &n, &k, &beta))
	{
			return -1;
	}
	printf("n = %d\nk=%d\nbeta=%f\n", n, k, beta);
	return writeSmallWorld(n, k, beta);
}
