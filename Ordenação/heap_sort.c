#include <stdio.h>

void swap ( int *a, int *b )
{
	int c = *a;
	*a = *b;
	*b = c;
}

void heap ( int *v, int size, int pos )
{
	int no, i, j, filho;
	for ( i = pos; i >= 0; i-- )
	{
		no = i;
		while ( no*2+1 < size )
		{
			filho = no*2+1;
			if ( filho+1 < size && v[filho+1] > v[filho] )
				filho++;
			if ( v[no] < v[filho] )
			{
				swap(&v[no], &v[filho]);
				no = filho;
			}
			else break;
		}
	}
}

void heap_sort ( int *v, int size )
{
	heap(v, size, size/2-1);
	int i, j;
	for ( i = size-1; i > 0; i-- )
	{
		swap(&v[0], &v[i]);
		heap(v, i, 0);
	}
}

int main ()
{
	int v[] = {2, 8, 6, 1, 10, 15, 3, 12, 11}, size = 9;
	int i;
	heap_sort(v, size);
	for ( i = 0; i < 9; i++ )
		printf("%d ", v[i]);
	printf("\n");
	return 0;
}
