/*
  最好情况：O(N)
  最差情况：O（N2）
  稳定性：稳定
*/
#include <stdio.h>

typedef int ElementType;
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
