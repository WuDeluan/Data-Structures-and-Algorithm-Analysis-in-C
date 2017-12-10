#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct QueueRecord
{
	int Front;
	int Rear;
	int Capacity;
	ElementType *Array;
}*Queue;

void InitQueue(Queue Q)
{
	Q->Front = 0;
	Q->Rear = 0;
}

Queue CreatQueue(int MaxSize)
{
	Queue Q = (QueueRecord*)malloc(sizeof(QueueRecord));
	Q->Capacity = MaxSize;
	Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
	InitQueue(Q);
	return Q;
}

int Enqueue(Queue Q, ElementType X)
{
	if((Q->Rear + 1) % Q->Capacity == Q->Front)
		return -1;
	Q->Rear = (Q->Rear + 1) % Q->Capacity;
	Q->Array[Q->Rear] = X;
	return 0;
}

ElementType Dequeue(Queue Q)
{
	if (Q->Front == Q->Rear)
		return -1;
	Q->Front = (Q->Front + 1) % Q->Capacity;
	return Q->Array[Q->Front];
}

int main()
{
	Queue Q = CreatQueue(4);
	printf("%d ", Enqueue(Q, 1));
	printf("%d ", Enqueue(Q, 2));
	printf("%d ", Enqueue(Q, 3));
	printf("%d ", Enqueue(Q, 4));
	printf("%d ", Dequeue(Q));
	printf("%d ", Dequeue(Q));
	printf("%d ", Dequeue(Q));
	printf("%d ", Dequeue(Q));
}
