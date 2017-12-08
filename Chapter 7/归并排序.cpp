/*
  时间复杂度：O(NlogN)
  稳定性：稳定
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

//将有序的A[Lpos]~A[Rpos-1]和A[Rpos]~A[RightEnd]归并成一个有序序列
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	// Lpos = 左边起始位置, Rpos = 右边起始位置, RightEnd = 右边终点位置
	int i, LeftEnd, NumElements, TmpPos;
	LeftEnd = Rpos - 1;                   //左边终点位置
	TmpPos = Lpos;                        //有序序列的起始位置
	NumElements = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd)              
	{
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];//将左边元素复制到TmpA
		else
			TmpArray[TmpPos++] = A[Rpos++];//将右边元素复制到TmpA
	}

	while (Lpos <= LeftEnd)                                  
		TmpArray[TmpPos++] = A[Lpos++];  //直接复制左边剩下的
	while (Rpos <= RightEnd)                                 
		TmpArray[TmpPos++] = A[Rpos++];  //直接复制右边剩下的

	for (i = 0; i < NumElements; i++, RightEnd--)            
		A[RightEnd] = TmpArray[RightEnd]; //将有序的TmpA[]复制回A[] 
}

//递归实现
void MSort_Recursion(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right) / 2;                  
		MSort_Recursion(A, TmpArray, Left, Center);            //递归解决左边
		MSort_Recursion(A, TmpArray, Center + 1, Right);       //递归解决右边
		Merge(A, TmpArray, Left, Center + 1, Right); //合并两段有序序列
	}
}

void MergeSort_Recursion(ElementType A[], int N)
{
	ElementType  *TmpArray;
	TmpArray = (ElementType*)malloc(sizeof(ElementType) * N);  
	if (TmpArray != NULL)
	{
		MSort_Recursion(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
	else printf("空间不足");
}

//非递归实现
//两两归并相邻有序子列 
void Merge_NonRecursive(ElementType A[], ElementType TmpArray[], int N, int Length)
{ 
	//length = 当前有序子列的长度
	int i, j;

	for (i = 0; i <= N - 2 * Length; i += 2 * Length) //归并到倒数第二对子列
		Merge(A, TmpArray, i, i + Length, i + 2 * Length - 1);
	if (i + Length < N)                               //归并最后2个子列(1对+1个）
		Merge(A, TmpArray, i, i + Length, N - 1);
	else                                              //最后只剩1个子列(0对+1个），直接赋给TmpA[]
		for (j = i; j < N; j++) 
			TmpArray[j] = A[j];
}

void MergeSort_NonRecursive(ElementType A[], int N)
{
	int Length;
	ElementType *TmpArray;

	Length = 1;       //初始化子序列长度
	TmpArray = (ElementType*)malloc(N * sizeof(ElementType));
	if (TmpArray != NULL) {
		while (Length < N) { 
			Merge_NonRecursive(A, TmpArray, N, Length);
			Length *= 2;
			Merge_NonRecursive(TmpArray, A, N, Length);
			Length *= 2;
		}             //两次归并，保证出循环时，排序后的结果在A[]中
		free(TmpArray);
	}
	else printf("空间不足");
}
