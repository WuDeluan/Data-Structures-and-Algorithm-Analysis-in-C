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

Position FindMin(AvlTree T)  
{
	if (T == NULL)
		return NULL;
	if (T->Left == NULL)
		return T;
	else
		return FindMin(T->Right);
}

Position Delete(AvlTree T,ElementType X)
{
	Position Temp;
	if (T == NULL)
		return NULL;
	else if (X < T->Element)
	{
		T->Left = Delete(T->Left, X);
		if (Height(T->Right) - Height(T->Left) == 2)
			//由于在左子树的删除导致在T处平衡被破坏  
			if (Height(T->Right->Left) > Height(T->Right->Right))
				//如果T->Right的左子树比右子树高，执行双旋转  
				T = DoubleRotateWithRight(T);
			else
				//否则执行单旋转  
				T = SingleRotateWithRight(T);
	}
	else if (X > T->Element)
	{
		T->Right = Delete(T->Right, X);
		if (Height(T->Left) - Height(T->Right) == 2)
			//由于在右子树的删除导致在T处平衡被破坏  
			if (Height(T->Left->Right) > Height(T->Left->Left))
				//如果T->Left的左子树比右子树要高,执行单旋转  
				T = SingleRotateWithLeft(T);
			else
				//否则执行双旋转  
				T = DoubleRotateWithLeft(T);
	}
	else 
	{//正常的删除策略  
		if (T->Left && T->Right)
		{
			Temp = FindMin(T->Right);
			T->Element = Temp->Element;
			T->Right = Delete(T->Right, T->Element);
		}
		else
		{
			Temp = T;
			if (T->Left == NULL)
				T = T->Right;
			else if (T->Right == NULL)
				T = T->Left;
			free(Temp);
		}
	}	
	if (T)
		//最后更新高度,此处可能T已经被设置成了NULL，所以需要检测下  
	    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

	return T;
}

int main()
{
	AvlTree T = (AvlNode*)malloc(sizeof(AvlNode));
	T = NULL;
	int A[] = { 0,1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 10; i++)
		T = Insert(T, A[i]);
	return 0;
}
