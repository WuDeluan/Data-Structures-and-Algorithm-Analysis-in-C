#include <stdio.h>

typedef int ElementType;
void BubbleSort(ElementType A[], int N)
{
	int i, j, Tmp;
	for (i = 0; i < N - 1; i++)
	{
		for (j = 0; j < N - 1 - i; j++)
		{
			if (A[j] > A[j + 1])
			{
				Tmp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = Tmp;
			}
		}
	}
}
/*
  最好情况：顺序O(N);
  最坏情况：逆序O(N2);
  稳定性：稳定；
*/
