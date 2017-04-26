#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void insertion_sort (double *v, int n)
{
	int i, j;
	for ( i = 1; i < n; i++ )
	{
		double aux = v[i];
		for ( j = i; j > 0 && aux < v[j-1]; j-- )
			v[j] = v[j-1];
		v[j] = aux;
	}
}

void bucket_sort (int n, double *v, int d)
{
	struct bucket
	{
		int tam;
		double balde[n];
	};

	struct bucket b[n];
	int i;

	for ( i = 0; i < n; i++ )
		b[i].tam = 0;

	for ( i = 0; i < n; i++ )
	{
		int aux = (v[i]*n)/d;
		b[aux].balde[b[aux].tam++] = v[i];
	}

	for ( i = 0; i < n; i++ )
		if ( b[i].tam > 0 )
			insertion_sort(b[i].balde, b[i].tam);
	
	int k = 0, j;
	for ( i = 0; i < n; i++ )
		if ( b[i].tam > 0 )
			for ( j = 0; j < b[i].tam; j++ )
				v[k++] = b[i].balde[j];
}

int main ()
{
	int n, i;
	scanf("%d", &n);
	double v[n], k = 0;
	for ( i = 0; i < n; i++ )
	{
		scanf("%lf", &v[i]);
		if ( v[i] > k ) k = v[i];		
	}
	int d;
	if ( k >= 1 ) d = pow(10, (int)log10(k)+1);
	else d = 1;
	bucket_sort(n, v, d);
	for ( i = 0; i < n; i++ )
		printf("%.2lf ", v[i]);
	printf("\n");
	return 0;
}
