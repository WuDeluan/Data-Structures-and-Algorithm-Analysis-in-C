#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
}*Heap;

Heap Initialize(int MaxElements)
{
	Heap H;
	H = (HeapStruct*)malloc(sizeof(HeapStruct));
	H->Capacity = MaxElements;
	H->Elements = (ElementType*)malloc(sizeof(ElementType) * MaxElements + 1);
	H->Size = 0;

	return H;
}

int Insert(Heap H, ElementType X)
{
	int i;
	if (H->Size == H->Capacity)
		return -1;
	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
}

int main()
{
	Heap H = Initialize(10);
	int i;
	int A[] = { 3,4,2,6,5,1,9,0,8,7 };
	for (i = 1; i < 11; i++)
		Insert(H,A[i - 1]);
	for (i = 1; i < 11; i++)
		printf("%d ", H->Elements[i]);
}
