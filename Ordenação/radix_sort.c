#include <stdio.h>
#include <string.h>

void radix_sort (int n, int *v, int k, int *ord)
{
	int c[10], i, ex = 1;
	
	while ( k/ex )
	{
		memset(c, 0, sizeof(0));
		for ( i = 0; i < n; i++ )
			c[(v[i]/ex)%10]++;
		for ( i = 1; i < 10; i++ )
			c[i] += c[i-1];
		for ( i = n-1; i >= 0; i-- )
		{	
			ord[c[v[(v[i]/ex)%10]]-1] = v[i];
			c[v[(v[i]/ex)%10]]--;
		}
		for ( i = 0; i < n; i++ )
			v[i] = ord[i];
		ex *= 10;
	}
}

int main ()
{
	int n;
	scanf("%d", &n);
	int v[n], i, k = 0;
	for ( i = 0; i < n; i++ )
	{
		scanf("%d", &v[i]);
		if ( v[i] > k ) k = v[i];
	}
	int ord[n];
	radix_sort(n, v, k, ord);
	for ( i = 0; i < n; i++ )
		printf("%d ", ord[i]);
	printf("\n");
	return 0;
}
