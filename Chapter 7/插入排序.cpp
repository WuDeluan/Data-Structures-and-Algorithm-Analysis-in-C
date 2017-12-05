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

/*for(P = 1;P < N;P++)
{
	for(j = P;j > 0;j--)
      {
	       if(Tmp < A[j - 1])
		     A[j] = A[j - 1];
	       else
		    break;    //!!!
      }
       A[j] = Tmp;
}*/
