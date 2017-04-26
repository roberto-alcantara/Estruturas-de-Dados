#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

typedef struct tree
{
	int value;
	struct tree *left;
	struct tree *right;
}tree;

typedef tree* PTtree;

typedef struct noQueue
{
	PTtree no;
	struct noQueue *next;
}noQueue;

typedef noQueue* PTNoqueue;

typedef struct queue
{
	PTNoqueue front;
	PTNoqueue end;
}queue;

typedef queue* PTqueue;

void insertTree ( PTtree *t, int value )
{
	if ( (*t) == NULL )
	{
		(*t) = (PTtree)malloc(sizeof(tree));
		if ( (*t) == NULL ) 
			return;
		(*t)->value = value;
		(*t)->left = NULL;
		(*t)->right = NULL;
	}
	else
	{
		if ( value < (*t)->value )
			insertTree ( &(*t)->left, value );
		else
			insertTree ( &(*t)->right, value );
	}
}

PTtree check ( PTtree t )
{
	if ( t->left == NULL ) return t;
	return check (  t->left );
}

void remover ( PTtree *t, int value )
{
	if ( (*t) == NULL ) return;
	if ( (*t)->value > value ) remover ( &(*t)->left, value );
	else if ( (*t)->value < value ) remover ( &(*t)->right, value );
	else if ( (*t)->left != NULL && (*t)->right != NULL )
	{
		PTtree aux = NULL;
		aux = check ( (*t)->right );
		(*t)->value = aux->value;
		remover ( &(*t)->right, aux->value );
	}
	else
	{
		PTtree aux = (*t);
		if ( (*t)->left == NULL )
			(*t) = (*t)->right;
		else
			(*t) = (*t)->left;
		free (aux);
	}
}

void printOrd ( PTtree t )
{
	if ( t == NULL ) 
		return;
	printOrd ( t->left );
	printf("%d ", t->value);
	printOrd ( t->right );
}

void printPre ( PTtree t )
{
	if ( t == NULL ) 
		return;
	printf("%d ", t->value);
	printPre ( t->left );
	printPre ( t->right );
}

void printPos ( PTtree t )
{
	if ( t == NULL ) 
		return;
	printPos ( t->left );
	printPos ( t->right );
	printf("%d ", t->value);
}

void initQueue ( PTqueue *q )
{
	(*q) = (PTqueue)malloc(sizeof(queue));
	(*q)->front = NULL;
	(*q)->end = NULL;
}

void push_queue ( PTqueue *q, PTtree t )
{
	PTNoqueue new = NULL;
	new = (PTNoqueue)malloc(sizeof(noQueue));
	if ( new == NULL ) puts("Erro");
	else
	{
		new->no = t;
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

PTtree front_queue ( PTqueue q )
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
			PTtree aux = front_queue(q);
			pop_queue(&q);
			printf("%d ", aux->value);
			if ( aux->left != NULL )
				push_queue(&q, aux->left);
			if ( aux->right != NULL )
				push_queue(&q, aux->right);
		}
	}
}

void print ( PTtree t, int k )
{
	if ( t == NULL )
		return;
	print ( t->right, k+1 );
	printf("%*d\n", k*4, t->value);
	print ( t->left, k+1 );
}

int main ()
{
	setlocale(LC_ALL, "portuguese");
	PTtree t = NULL;
	int value, n, op;
	do{
		printf("\n***Árvore Binária***\n\n");
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
			printf("Elementos: ");
			while ( n-- )
			{
				scanf("%d", &value);
				insertTree ( &t, value );
			}
		}
		if ( op == 2 )
		{
			printf("Elemento a ser removido: ");
			scanf("%d", &value );
			remover ( &t, value);
		}
		if ( op == 3 )
		{
			printf("\n\n");
			print ( t, 1 );
		}
		if ( op == 4 )
		{  
			printf("\nPré Ordem: ");
			printPre ( t );
		}
		if ( op == 5 )
		{
			printf("\nOrdem Simétrica: ");
			printOrd ( t );
		}
		if ( op == 6 )
		{	
			printf("\nPós Ordem: ");
			printPos ( t );
		}
		if ( op == 7 )
		{
			PTqueue q;
			initQueue(&q);
			push_queue ( &q, t );
			printf("\nPor Nível: ");
			printNivel( q );
			printf("\n");
		}
	}while ( op != 0 );
	return 0;
}
