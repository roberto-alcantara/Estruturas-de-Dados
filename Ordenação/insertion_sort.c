void insertion_sort ( int size, int *v )
{
	int i, j, k, cont = 1; 
	for ( i = 1; i < size; i++ ) 
	{
		int aux = v[i];
		for ( j = i; j > 0 && aux < v[j-1]; j-- )
			v[j] = v[j-1];
		v[j] = aux;
	}
}
