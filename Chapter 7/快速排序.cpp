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

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];
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

void QSort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (; ;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		QSort(A, Left, i - 1);
		QSort(A, i + 1, Right);
	}
	else
		InsertionSort(A + Left, Right - Left + 1);
}

void QuickSort(ElementType A[], int N)
{
	QSort(A, 0, N - 1);
}
