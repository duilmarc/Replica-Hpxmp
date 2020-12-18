#include <stdio.h> 
#include <omp.h>
#include <stdlib.h>

void daxpy(int n, double a, double *x, double *y, double *z){ 
#pragma omp parallel default(none) shared(n,x,y,a,z)   
{ 
	int i; 
	#pragma omp for     
	for (i=0; i<n; i++){       
		x[i] = (double)i*(double)i;       
		y[i] = (i+1.)*(i-1.);     
	} 
	#pragma omp for     
	for (i=0; i<n; i++)       
		z[i] += a * x[i] + y[i];   
	} 
}


int main(){ 
	int n=1e6; 
	for( int i = 0 ; i < 4 ; ++i)
	{
		double *x = malloc(sizeof(double)*n);   
		double *y = malloc(sizeof(double)*n);   
		double *z = malloc(sizeof(double)*n);   
		double a = 5./3.; 
		double start; 
		double end; 
		start = omp_get_wtime();	
		daxpy(n,a,x,y,z);
		end = omp_get_wtime();    
		free(x);   
		free(y);   
		free(z); 
		printf("Test with %d size\n", n);
		printf("Work took %f seconds\n", end - start);
		printf("Exiting test...\n");
		printf("\n");
		n= n/10;
	}
	return(0);
}
