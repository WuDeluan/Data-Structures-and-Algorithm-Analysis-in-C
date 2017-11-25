#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct StackRecord
{
	int Top;
	int Capacity;
	ElementType *Array;
}*Stack;

Stack CreatStack(int MaxSize)
{
	Stack S = (StackRecord*)malloc(sizeof(StackRecord));
	S->Capacity = MaxSize;
	S->Array = (ElementType*)malloc(sizeof(ElementType) * S->Capacity);
	return S;
}

void InitStack(Stack S)
{
	S->Top = 0;//!!!
}

int Push(Stack S,ElementType X)
{
	if (S->Top == S->Capacity)
		return -1;
	S->Array[++S->Top] = X; //!!!
	return 0;
}

ElementType Pop(Stack S)
{
	if (S->Top == 0)
		return -1;
	return S->Array[S->Top--]; //!!!
}

ElementType Peek(Stack S)
{
	if (S->Top == 0)
		return -1;
	return S->Array[S->Top]; //!!!
}

int main()
{
	Stack S = CreatStack(4);
	InitStack(S);//!!!
	printf("%d ", Push(S, 1));
	printf("%d ", Push(S, 2));
	printf("%d ", Push(S, 3));
	printf("%d ", Push(S, 4));
	printf("%d ", Push(S, 5));
	printf("%d ", Peek(S));
	printf("%d ", Pop(S));
	printf("%d ", Pop(S));
	printf("%d ", Pop(S));
	printf("%d ", Pop(S));
	printf("%d ", Pop(S));

	return 0;
}
