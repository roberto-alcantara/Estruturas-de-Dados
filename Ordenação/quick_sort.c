#include <stdio.h>

void swap ( int *a, int *b )
{
	int c = *a;
	*a = *b;
	*b = c;
}

int partition ( int p, int r, int *v )
{
	int x = v[r];
	int i = p-1, j = p;
	for ( ; j < r; j++ )
	{
		if ( v[j] <= x )
		{
			i++;
			swap(&v[i], &v[j]);
		}
	}
	i++;
	swap(&v[i], &v[r]);
	return i;
}

void quick_sort ( int p, int r, int *v )
{
	if ( p < r )
	{
		int q = partition(p, r, v);
		quick_sort(p, q-1, v);
		quick_sort(q+1, r, v);
	}
}

int main ()
{
	int v[] = {4,1,3,2};
	quick_sort(0, 3, v);
	int i = 0;
	for ( ; i < 4; i++ )
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}
