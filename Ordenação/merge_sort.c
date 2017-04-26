#include <stdio.h>

void merge(int a, int b, int posfim, int *v )
{
	int size = posfim-a+1, i = a, j = b;
	int k = 0; int aux[size];
	
	while ( i < b && j <= posfim )
	{
		if ( v[i] <= v[j] )
			aux[k++] = v[i++];
		else
			aux[k++] = v[j++];
	}
	while ( i < b )
		aux[k++] = v[i++];
	while ( j <= posfim )
		aux[k++] = v[j++];

	for ( k = 0; k < size; k++ )
		v[a++] = aux[k];
}

void merge_sort ( int i, int j, int *v )
{
	if ( i < j )
	{
		merge_sort(i, (j+i)/2, v);
		merge_sort(((j+i)/2+1), j, v);
		merge(i, ((j+i)/2+1), j, v);
	}
}

int main()
{
        int n ; scanf("%d", &n) ;
        int v[n], i = 0;
        for( ; i < n ; i++)
                scanf("%d", &v[i]);
        merge_sort( 0, n-1 , v ) ;
        return 0;
}
