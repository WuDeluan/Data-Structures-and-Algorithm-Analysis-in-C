#include <stdio.h>
#include <stdlib.h>
#define SpaceSize 10

typedef int ElementType;
typedef int List;
typedef int Position;
struct Node CursorSpace[SpaceSize];
typedef struct Node
{
	ElementType Element;
	Position Next;
};

Position CursorAlloc()
{
	Position P;
	P = CursorSpace[0].Next;
	return P;
}

void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

int IsEmpty(List L)
{
	return CursorSpace[L].Next == 0;
}

int IsLast(List L,Position P)
{
	return CursorSpace[P].Next == 0;
}

Position Find(List L, ElementType X)
{
	Position P;
	P = CursorSpace[L].Next;
	while (P && CursorSpace[P].Element != X)
		P = CursorSpace[P].Next;
	return P;
}

int Delete(List L, ElementType X)
{
	Position P, TmpCell;
	P = Find(L, X);
	if (!IsLast(L, P))
	{
		TmpCell = CursorSpace[P].Next; 
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree(TmpCell);
		return 0;
	}
	return -1;
}

int Insert(List L, ElementType X, Position P)
{
	Position TmpCell = CursorAlloc();
	if (TmpCell == 0)
		return -1;
	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
	CursorSpace[P].Next = TmpCell;
}
