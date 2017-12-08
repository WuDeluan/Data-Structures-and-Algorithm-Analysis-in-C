/*
①选择基准(使A[Left] < R[Center] < A[Right]，交换A[Center],A[Right-1]。
② 令 i 从 Right-1 开始向前，j 从0开始向后。
③当 i 遇到比基准小的，停下，当 j 遇到比基准大的，停下。
④当 i，j 都停下时，交换指向的元素。
⑤当 i > j，退出循环，将基准与 i 指向的元素交换。
*/
#include <stdio.h>
#include <stdlib.h>
#define Cutoff 3

typedef int ElementType;
void Swap(ElementType *a, ElementType *b)
{
	ElementType Tmp;
	Tmp = *a;
	*a = *b;
	*b = Tmp;
}

void InsertionSort(ElementType A[], int N)
{
	int j, P;
	ElementType Tmp;
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > Tmp; j--)
			A[j] = A[j - 1];
		A[j] = Tmp;
	}
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
	//此时A[Left] <= A[Center] <= A[Right]
	
	Swap(&A[Center], &A[Right - 1]);     //将基准Pivot藏到右边;
	//此时A[Right]一定大于A[Right-1],接下来只需要考虑A[Left+1] … A[Right-2]
	return A[Right - 1];      //返回基准
}

void QSort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if (Right - Left >= Cutoff)      //如果序列元素大于阈值，进入快速排序
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (; ;)               //将序列中比基准小的移到基准左边，大的移到右边
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);//将基准换到正确的位置

		QSort(A, Left, i - 1);     //递归解决左边
		QSort(A, i + 1, Right);    //递归解决右边
	}
	else
		InsertionSort(A + Left, Right - Left + 1); //元素太少，用简单排序
}

void QuickSort(ElementType A[], int N)
{
	QSort(A, 0, N - 1);
}

/*
时间复杂度：O(NlogN)
稳定性：不稳定
*/
