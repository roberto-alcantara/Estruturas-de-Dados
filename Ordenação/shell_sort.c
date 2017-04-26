#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort ( int size, int *v, int n, int h )
{
	int i, j;
	for ( i = n; i < size; i += h )
	{
		int aux = v[i];
		for ( j = i; j > n-h && aux < v[j-h]; j -= h ) 
			v[j] = v[j-h];
		v[j] = aux;
	}
}

void shell_sort ( int size, int *v )
{
	int h = 1, i, k;
	while ( (3*h+1)*3+1 <= size )
		h = 3*h+1; 
	for ( ; h >= 1; h = (h-1)/3 )
		for ( i = 0; i < h; i++ )
			insertion_sort(size, v, i+h, h);
}

int main()
{
        int n ; scanf("%d", &n) ;
        int v[n], i = 0;
        for( ; i < n ; i++)
                scanf("%d", &v[i]);
                
		clock_t inicio;
		double tempo;

		inicio = clock();
		shell_sort(n, v);
		tempo = (double) (clock() - inicio) / (double) CLOCKS_PER_SEC;
		printf("\nShell Sort: %lf segundos\n", tempo);
        return 0;
       
}
