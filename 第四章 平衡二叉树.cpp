#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AvlNode
{
	ElementType Element;
	struct AvlNode *Left;
	struct AvlNode *Right;
	int Height;
}*AvlTree,*Position;

int Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K1->Height = Max(Height(K1->Right), Height(K1->Left)) + 1;
	K2->Height = Max(Height(K2->Right), Height(K2->Left)) + 1;

	return K1;
}

Position SingleRotateWithRight(Position K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;

	return K1;
}

Position DoubleRotateWithLeft(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);

	return SingleRotateWithRight(K3);
}

AvlTree Insert(AvlTree T, ElementType X)
{
	if (T == NULL)
	{
		T = (AvlNode*)malloc(sizeof(AvlNode));
		T->Element = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	}
	else
	{
		if (X < T->Element)
		{
			T->Left = Insert(T->Left, X);
			if (Height(T->Left) - Height(T->Right) == 2)
			{
				if (X < T->Left->Element)
					T = SingleRotateWithLeft(T);
				else
					T = DoubleRotateWithLeft(T);
			}
		}
		else if (X > T->Element)
		{
			T->Right = Insert(T->Right, X);
			if (Height(T->Right) - Height(T->Left) == 2)
			{
				if (X > T->Right->Element)
					T = SingleRotateWithRight(T);
				else
					T = DoubleRotateWithRight(T);
			}
		}
	}
	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

	return T;
}
