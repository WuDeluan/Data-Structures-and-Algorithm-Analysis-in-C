#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node
{
	ElementType Data;
	struct Node *Next;
}*List,*Position;

void Add(List L, ElementType X)
{
	Position P1 = (Node*)malloc(sizeof(Node));
	P1->Data = X;
	P1->Next = NULL;
	Position P2 = L;
	while (P2->Next)
		P2 = P2->Next;
	P2->Next = P1;
}

int Insert(List L, ElementType X, int i)
{
	Position P1 = L->Next;
	Position P2 = (Node*)malloc(sizeof(Node));//Creat
	int k = 0;
	while (P1)
	{
		k++;
		if (k == i)
			break;
		P1 = P1->Next;
	}
	if (P1)
	{
		P2->Data = X;
		P2->Next = P1->Next;
		P1->Next = P2;
		return 0;
	}
	return -1;
}

Position Find(List L, ElementType X)
{
	Position P = L->Next;
	while (P)
	{
		if (P->Data == X)
			return P;
		P = P->Next;
	}
	return NULL;
}

Position FindPrev(List L, ElementType X)
{
	Position P = L->Next;
	while (P->Next)
	{
		if (P->Next->Data == X)
			return P;
		P = P->Next;
	}
	return NULL;
}

int Delete(List L, ElementType X)
{
	Position P1 = FindPrev(L, X);
	if (P1)
	{
		Position P2 = P1->Next;
		P1->Next = P2->Next;
		free(P2);
		return 0;
	}
	return -1;
}

void PrintAll(List L)
{
	Position P;
	for (P = L->Next; P; P = P->Next)
		printf("%d ", P->Data);
	printf("\n");
}
int main()
{
	List L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	for (int i = 0; i < 10; i++)
	{
		Add(L, i);
	}
	PrintAll(L);
	(Delete(L, 1) == 0) ? PrintAll(L) : printf("删除失败！\n");
	(Find(L, 11) == NULL) ? printf("找不到！\n") : printf("%d ", Find(L, 11)->Data);
	(Insert(L, 10, 9) == 0) ? PrintAll(L) : printf("插入失败！\n");

	return 0;
}
