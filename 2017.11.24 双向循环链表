#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node
{
	ElementType Data;
	struct Node *Next, *Prev;
}*List, *Position;

void Add(List L, ElementType X)
{
	Position P1 = (Node*)malloc(sizeof(Node));
	P1->Data = X;
	Position P2 = L->Next; //!!!
	if (P2) {
		while (P2->Next != L->Next) //!!!
			P2 = P2->Next;
		P2->Next = P1;
		P1->Prev = P2;
		P1->Next = L->Next;
		L->Next->Prev = P1;
	}
	else
	{
		L->Next = P1;
		P1->Next = P1;
		P1->Prev = P1;
	}
}

int Insert(List L, ElementType X, int i) 
{
	Position P1 = L->Next;
	Position P2 = (Node*)malloc(sizeof(Node));//!!!
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
		P1->Next->Prev = P2;
		P1->Next = P2;
		P2->Prev = P1;
		return 0;
	}
	return -1;
}

Position Find(List L, ElementType X)
{
	Position P = L->Next;
	while (P->Next != L->Next) //!!!
	{
		if (P->Data == X)
			return P;
		P = P->Next;
	}
	return NULL;
}

/*Position FindPrev(List L, ElementType X)
{
	Position P = L->Next;
	while (P->Next)
	{
		if (P->Next->Data == X)
			return P;
		P = P->Next;
	}
	return NULL;
}*/

int Delete(List L, ElementType X)
{
	Position P1 = Find(L, X);
	if (P1)
	{
		P1->Prev->Next = P1->Next;
		P1->Next->Prev = P1->Prev;
		free(P1);
		return 0;
	}
	return -1;
}

void PrintAll(List L)
{
	Position P;
	for (P = L->Next; P->Next != L->Next; P = P->Next)
		printf("%d ", P->Data);
	printf("%d\n",P->Data);  //!!!
}
int main()
{
	List L = (Node*)malloc(sizeof(Node));
	L->Next = L->Prev = NULL;
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
