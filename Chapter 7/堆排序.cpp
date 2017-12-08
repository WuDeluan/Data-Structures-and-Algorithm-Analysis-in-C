/*
①将关键字构造成树。
②下滤形成初始堆。
*/
#include <stdio.h>
#include <stdlib.h>
#define LeftChild(i)(2 * (i) + 1)

typedef int ElementType;
void Swap(ElementType *a, ElementType *b)
{
	ElementType Tmp;
	Tmp = *a;
	*a = *b;
	*b = Tmp;
}

void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;

	for (Tmp = A[i]; LeftChild(i) < N; i = Child)           //取出根节点存放的值
	{
		Child = LeftChild(i);                           //得到左孩子的值
		if (Child != N - 1 && A[Child + 1] > A[Child])  //取左右孩子中较大的
			Child++; 
		if (Tmp < A[Child])      //下滤
			A[i] = A[Child];
		else                     //找到合适位置            
			break;
	}
	A[i] = Tmp;                      //赋值
}

void HeapSort(ElementType A[], int N)
{
	int i;
	ElementType Tmp;
	for (i = N / 2; i >= 0; i--)     //从最后一个不为叶子的节点开始下滤
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)   
	{
		Swap(&A[0], &A[i]);      //“删除”最大根
		PercDown(A, 0, i);       //调整大根堆
	}
}

/*
  时间复杂度：O(NlogN)
  稳定性：不稳定
*/
