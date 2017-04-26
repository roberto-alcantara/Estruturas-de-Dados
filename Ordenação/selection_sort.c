void selection_sort ( int size, int *v )
{
	int i, j, k, cont = 1;
	for ( i = 0; i < size-1; i++ ) 
	{
		int pos = i;
		for ( j = i+1; j < size; j++ )
			if ( v[pos] > v[j] ) pos = j;

		if ( pos != i )
			swap(&v[i], &v[pos]);
	}
}
