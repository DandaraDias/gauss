#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

double** ler(const char *nome, int *k)
{
	double **L;
	double a;
	int i, j, dim;
	
	FILE *ler;
	
	ler = fopen("matriz.dat", "r");
	i = fscanf(ler, "%d", &dim);
	
	L = malloc(dim*sizeof(double *));
	
	for(i=0; i<dim; i++)
	{
		L[i] = (double *)malloc((dim+1)*sizeof(double));
	}
	
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim+1; j++)
		{
			fscanf(ler, "%lf", &a);
			L[i][j] = a;
		}
	}
	
	*k = dim;

	return L;
}

void imprime(double **M, int dim)
{
	int i, j;
	
	puts(" ");
	for(i=0; i<dim; i++)
	{
		for(j=0; j<dim+1; j++)
		{
			printf("%3g", M[i][j]);
		}
		
		puts(" ");
	}
}

double** triangsup(double **M, int dim)
{
	int i, j, l;
	double lambda;

	for(j=0; j<dim+1; j++)
	{
		for(i=0; i<dim; i++)
		{
			if(i>j)
			{
				lambda = M[i][j]/M[j][j];
				
				for(l=0; l<dim+1; l++)
				{
					M[i][l] = M[i][l] - lambda*M[j][l];
				}
			}
		}
	}
	
	return M;
}

void subsreversa(double **M, double *raizes, int dim)
{
	int i, j;
	double soma;
	
	for(i=dim-1; i>=0; i--)
	{
		soma=0;
				
		for(j=i+1; j<dim; j++)
		{
			soma += M[i][j]*(raizes[j]);	
		}
			
		raizes[i] = (M[i][dim] - soma)/M[i][i];
	}
	
	
}

int main(int argc, char **argv)
{
	double **M;
	double *raizes;
	int i, dim;
	
	M = ler(argv[1], &dim);
	imprime(M, dim);
	triangsup(M, dim);
	imprime(M, dim);
	
	raizes = malloc(dim*sizeof(double));
	
	subsreversa(M, raizes, dim);
	
	for(i=0; i<dim; i++)
	{
		printf("\nx%1d = %5.2lf", i, raizes[i]);
	}
	
	return 0;
}
