void bubble_sort ( int size, int *v )
{
	int i, j;
	for ( i = 0; i < size-1; i++ )
		for ( j = size-1; j > i; j-- )
			if ( v[j] < v[j-1] ) 
				swap(&v[j], &v[j-1]);
}
