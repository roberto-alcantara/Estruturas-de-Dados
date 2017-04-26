#include <stdio.h>
#include <string.h>

void counting_sort (int k, int n, int *v, int *ord)
{
	int c[k+1], i;
	memset(c, 0, sizeof(c));
	for ( i = 0; i < n; i++ )
		c[v[i]]++;
	for ( i = 1; i <= k; i++ )
		c[i] += c[i-1];
	for ( i = n-1; i >= 0; i-- )
	{
		ord[c[v[i]]-1] = v[i];
		c[v[i]]--;
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
	counting_sort(k, n, v, ord);
	for ( i = 0; i < n; i++ )
		printf("%d ", ord[i]);
	printf("\n");
	return 0;
}
