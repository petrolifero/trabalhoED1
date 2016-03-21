#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

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
							printf("Primeiro if");
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
							printf("SEGUNDO IF");
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
							printf("Terceiro if");
							*n=0;
							*k=0;
							*b=0;
							return -1;
					}
	
			}
	}
	if((*n)<=0 || (*k)<=0 || (*b)<0.0 || (*b)>1|| (*k)%2 != 0)
	{
		printf("Quarto if");
		return -1;
	}
	return 0;
}


void exibeGrafo(int **matriz, int n)
{
		int i;
		int j;
		FILE* fp=fopen("grafo.txt", "w");
		if(!fp)
		{
				fprintf(stderr, "Não pude abrir o arquivo");
				return;
		}
		for(i=0; i<n; i++)
		{
				fprintf(fp, "%d %.3f ", i, (rand()%1000)/1000.0);
				for(j=0; j<n; j++)
				{
						if(matriz[i][j])
						{
								fprintf(fp, "%d %d ", j, matriz[i][j]);
						}
				}
				fputc('\n', fp);
		}
}


int writeSmallWorld(int n, int k, float beta)
{
	int i,j;
	srand(time(NULL));
	int **matriz;

	matriz=(int**)calloc(sizeof(int*), n);
	for(i=0; i<n; i++)
	{
			matriz[i]=(int*)calloc(sizeof(int), n);
	}


	for(i=n-1; i>=0; i--) //para cada vertice
	{
			for(j=0; j<n; j++) //para cada possivel vizinho
			{
					int edgeOnLattice=abs(i-j)%(n-1-k/2);
					if(edgeOnLattice>0 && edgeOnLattice<=k/2)
					{
							int tmp = rand()%100+1;
							matriz[i][j]=tmp;
							matriz[j][i]=tmp;
					}
			}
	}

	for(i=n-1; i>=0 ; i--)
	{
			for(j=i-1; j>=0 ; j--)
			{
					if(matriz[i][j])
					{
							float lanceDeProbabilidade = (rand()%1000)/1000.0;
							if(lanceDeProbabilidade<=beta)
							{
									int k;
									int tmp;
									matriz[i][j]=0;
									matriz[j][i]=0;
									do
									{
											k=rand()%n;
									}while(k==i||matriz[i][k]);
									tmp=rand()%100+1;
									matriz[i][k]=tmp;
									matriz[k][i]=tmp;
							}
					}
			}
	}
	exibeGrafo(matriz, n);
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

	if(parseInput(argc, argv, &n, &k, &beta)==-1)
	{
			printf("Problemas ao parsear sua entrada\n");
			usage(argv[0]);
			return -1;
	}
	return writeSmallWorld(n, k, beta);


}
