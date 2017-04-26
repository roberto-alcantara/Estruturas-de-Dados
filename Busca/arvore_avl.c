#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct avl
{
	int value, balance;
	struct avl *left;
	struct avl *right;
}avl;

typedef avl* PTavl;

typedef struct noQueue
{
	PTavl no;
	struct noQueue *next;
}noQueue;

typedef noQueue* PTNoqueue;

typedef struct queue
{
	PTNoqueue front;
	PTNoqueue end;
}queue;

typedef queue* PTqueue;

int max ( int a, int b )
{
	return a > b ? a : b;
}

int height ( PTavl a )
{
	if ( a == NULL ) return 0;
	else return a->balance;
}

void rotation_left ( PTavl *a )
{
	PTavl aux = NULL;
	aux = (*a);
	(*a) = (*a)->right;
	aux->right = (*a)->left;
	aux->balance = max( height(aux->left), height(aux->right) ) + 1;
	(*a)->left = aux;
	(*a)->balance = max( height((*a)->left), height((*a)->right) ) + 1;
}

void rotation_right ( PTavl *a )
{
	PTavl aux = NULL;
	aux = (*a);
	(*a) = (*a)->left;
	aux->left = (*a)->right;
	aux->balance = max( height(aux->left), height(aux->right) ) + 1;
	(*a)->right = aux;
	(*a)->balance = max( height((*a)->left), height((*a)->right) ) + 1;
}

void double_rotation_left ( PTavl *a )
{
    rotation_right( &(*a)->right );
    rotation_left( &(*a) );
}

void double_rotation_right ( PTavl *a )
{
    rotation_left( &(*a)->left );
    rotation_right( &(*a) );
}

void insere_node ( PTavl *a, int n )
{
	if ( (*a) == NULL )
	{
		(*a) = (PTavl)malloc(sizeof(avl));
		if ( (*a) == NULL )
		{
			puts("ERRO!");
			return;
		}
		(*a)->value = n;
		(*a)->balance = 1;
		(*a)->left = NULL;
		(*a)->right = NULL;
		return;
	}

    if ( n > (*a)->value )
	    insere_node(&(*a)->right, n);
    else
	    insere_node(&(*a)->left, n);	
    (*a)->balance = max( height((*a)->left), height((*a)->right) ) + 1;
   
	int bal = height(((*a)->left)) - height(((*a)->right));
	
	if ( bal > 1 )
	{
		if ( ( height(((*a)->left)->left) - height(((*a)->left)->right) ) >= 0 )
			rotation_right( &(*a) );
		else
			double_rotation_right( &(*a) );
		return;
	}
	if ( bal < -1 )
	{
		if ( ( height(((*a)->right)->left) - height(((*a)->right)->right) ) <= 0 )
			rotation_left( &(*a) );
		else
			double_rotation_left( &(*a) );
	}
}

PTavl check ( PTavl a )
{
    if ( a->left == NULL ) return a;
    else check ( a->left ); 
}

void remove_node ( PTavl *a, int n )
{
    if ( (*a) == NULL ) return;
    else if ( n > (*a)->value ) remove_node ( &(*a)->right, n );
    else if ( n < (*a)->value ) remove_node ( &(*a)->left, n );
    else if ( (*a)->left != NULL && (*a)->right != NULL )
    {
        PTavl aux = NULL;
        aux = check( (*a)->right );
        (*a)->value = aux->value;
        (*a)->balance = aux->balance;
        remove_node( &(*a)->right, (*a)->value );
        
    }
    else
    {
        PTavl aux = NULL;
        aux = (*a);
        if ( (*a)->left == NULL )
            (*a) = (*a)->right;
        else 
            (*a) = (*a)->left;
        free(aux);
    }
    
    if ( (*a) == NULL ) return;
    
    (*a)->balance = max( height((*a)->left), height((*a)->right) ) + 1;
   
	int bal = height(((*a)->left)) - height(((*a)->right));
	
	if ( bal > 1 )
	{
		if ( ( height(((*a)->left)->left) - height(((*a)->left)->right) ) >= 0 )
			rotation_right( &(*a) );
		else
			double_rotation_right( &(*a) );
		return;
	}
	if ( bal < -1 )
	{
		if ( ( height(((*a)->right)->left) - height(((*a)->right)->right) ) <= 0 )
			rotation_left( &(*a) );
		else
			double_rotation_left( &(*a) );
	}
}

void printOrd ( PTavl a )
{
	if ( a == NULL ) 
		return;
	printOrd ( a->left );
	printf("%d ", a->value);
	printOrd ( a->right );
}

void printPre ( PTavl a )
{
	if ( a == NULL ) 
		return;
	printf("%d ", a->value);
	printPre ( a->left );
	printPre ( a->right );
}

void printPos ( PTavl a )
{
	if ( a == NULL ) 
		return;
	printPos ( a->left );
	printPos ( a->right );
	printf("%d ", a->value);
}

void initQueue ( PTqueue *q )
{
	(*q) = (PTqueue)malloc(sizeof(queue));
	(*q)->front = NULL;
	(*q)->end = NULL;
}

void push_queue ( PTqueue *q, PTavl a )
{
	PTNoqueue new = NULL;
	new = (PTNoqueue)malloc(sizeof(noQueue));
	if ( new == NULL ) puts("Erro");
	else
	{
		new->no = a;
		new->next = NULL;
		if ( (*q)->front == NULL )
		{
			(*q)->front = new;
			(*q)->end = new;
		}
		else
		{
			(*q)->end->next = new;
			(*q)->end = new;
		}
	}
}

PTavl front_queue ( PTqueue q )
{
	return q->front->no;
}

void pop_queue ( PTqueue *q )
{
	if ( (*q)->front == NULL ) puts("Árvore Vazia");
	else
	{
		PTNoqueue aux = (*q)->front;
		(*q)->front = (*q)->front->next;
		free(aux);
	}
}

void printNivel ( PTqueue q )
{
	if ( q->front == NULL ) puts("Árvore vazia!");
	else
	{
		while ( q->front != NULL )
		{
			PTavl aux = front_queue(q);
			pop_queue(&q);
			printf("%d ", aux->value);
			if ( aux->left != NULL )
				push_queue(&q, aux->left);
			if ( aux->right != NULL )
				push_queue(&q, aux->right);
		}
	}
}

void print ( PTavl a, int k )
{
	if ( a == NULL ) return;
	print( a->right, k+1 );
	printf("%*d\n", k*4, a->value);
	print( a->left, k+1 );
}

int main ()
{
	setlocale(LC_ALL, "portuguese");
	PTavl a = NULL;
	int value, n, op;
	do{
		printf("\n***Árvore AVL***\n\n");
		printf("1 - Inserir\n");
		printf("2 - Remover\n");
		printf("3 - Imprimir\n");
		printf("4 - Busca em Pré-Ordem\n");
		printf("5 - Busca em Ordem Simétrica\n");
		printf("6 - Busca em Pos-Ordem\n");
		printf("7 - Busca por Nível\n");
		printf("0 - Sair\n");
		scanf("%d", &op);
		
		#ifdef __linux
		system("clear");
		#else
		system("cls");
		#endif	
	
		if ( op == 1 )
		{
			printf("\nQuantidade de elementos: ");
			scanf("%d", &n);
			while ( n-- )
			{
				scanf("%d", &value);
				insere_node ( &a, value );
				printf("\n");
				print ( a, 1 );
			}
		}
		if ( op == 2 )
		{
			printf("Elemento a ser removido: ");
			scanf("%d", &value );
			remove_node ( &a, value);
		}
		if ( op == 3 )
		{
			printf("\n\n");
			print ( a, 1 );
		}
		if ( op == 4 )
		{  
			printf("\nPré Ordem: ");
			printPre ( a );
		}
		if ( op == 5 )
		{
			printf("\nOrdem Simétrica: ");
			printOrd ( a );
		}
		if ( op == 6 )
		{	
			printf("\nPós Ordem: ");
			printPos ( a );
		}
		if ( op == 7 )
		{
			PTqueue q;
			initQueue(&q);
			push_queue ( &q, a );
			printf("\nPor Nível: ");
			printNivel( q );
			printf("\n");
		}
	}while ( op != 0 );
	return 0;
}
