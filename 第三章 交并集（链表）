#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node
{
	ElementType Data;
	struct Node *Next;
}*List, *Position;

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

void PrintAll(List L)
{
	Position P;
	for (P = L->Next; P; P = P->Next)
		printf("%d ", P->Data);
	printf("\n");
}

int CreatList(List &L, int a[], int n)
{
	L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	Position P, TmpCell;
	P = L;
	for (int i = 0; i < n; i++)
		Add(L, a[i]);
	if (L->Next)
		return 0;
	else
		return -1;
}

List Union(List L1, List L2)
{
	List L3;
	L3 = (Node*)malloc(sizeof(Node));
	L3->Next = NULL;
	Position P1, P2;
	P1 = L1->Next;
	P2 = L2->Next;
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->Data = P2->Data)
		{
			Add(L3, P1->Data);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->Data > P2->Data)
		{
			Add(L3, P2->Data);
			P2 = P2->Next;
		}
		else if (P1->Data < P2->Data)
		{
			Add(L3, P1->Data);
			P1 = P1->Next;
		}
	}
	while (P1)
	{
		Add(L3, P1->Data);
		P1 = P1->Next;
	}
	while (P2)
	{
		Add(L3, P2->Data);
		P2 = P2->Next;
	}
	return L3;
}

List Intersection(List L1, List L2)
{

	List L3;
	L3 = (Node*)malloc(sizeof(Node));
	L3->Next = NULL;
	Position P1, P2;
	for (P1 = L1->Next; P1; P1 = P1->Next)
		for (P2 = L2->Next; P2; P2 = P2->Next)
			if (P1->Data == P2->Data)
				Add(L3, P1->Data);
	return L3;
}

int main()
{
	List L, P;
	int a[5] = { 2,4,6,8,10 };
	int b[10] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("%d\n", CreatList(P, b, 10));
	printf("%d\n", CreatList(L, a, 5));
	List K = Intersection(L, P);
	PrintAll(K);
    K = Union(L, P);
	PrintAll(K);
	return 0;
}
