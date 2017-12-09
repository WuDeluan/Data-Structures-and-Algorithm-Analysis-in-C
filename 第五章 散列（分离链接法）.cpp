#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define KEYLENGTH 15                     // 关键词字符串的最大长度
typedef char ElementType[KEYLENGTH + 1]; // 关键词类型用字符串
#define MAXTABLESIZE 100000              // 允许开辟的最大散列表长度 
typedef int Index;                      // 散列地址类型

// 定义单链表
typedef struct Node {
	ElementType Data;
	struct Node *Next;
}*Position, *List;

// 散列表类型 
typedef struct TableNode {   // 散列表结点定义
	int TableSize; // 表的最大长度
	List Heads;    // 指向链表头结点的数组
} *HashTable;

// 返回大于N且不超过MAXTABLESIZE的最小素数
int NextPrime(int N)
{
	int i, p = (N % 2) ? N + 2 : N + 1; //从大于N的下一个奇数开始

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i>2; i--)
			if (!(p%i)) break;  // p不是素数
		if (i == 2) break;          // for正常结束，说明p是素数 
		else  p += 2;               // 否则试探下一个奇数
	}
	return p;
}

HashTable CreateTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(TableNode));
	//保证散列表最大长度是素数
	H->TableSize = NextPrime(TableSize);

	// 以下分配链表头结点数组
	H->Heads = (List)malloc(H->TableSize * sizeof(Node));
	//初始化表头结点
	for (i = 0; i<H->TableSize; i++) {
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
	}

	return H;
}

//哈希函数
int Hash(ElementType Key, int TableSize)
{
	return (int)Key % 13;
}


Position Find(HashTable H, ElementType Key)
{
	Position P;
	Index Pos;

	Pos = Hash(Key, H->TableSize); // 初始散列位置 
	P = H->Heads[Pos].Next; // 从该链表的第1个结点开始
							//  当未到表尾，并且Key未找到时
	while (P && strcmp(P->Data, Key))
		P = P->Next;

	return P; // 此时P或者指向找到的结点，或者为NULL
}

bool Insert(HashTable H, ElementType Key)
{
	Position P, NewCell;
	Index Pos;

	P = Find(H, Key);
	if (!P) { // 关键词未找到，可以插入
		NewCell = (Position)malloc(sizeof(Node));
		strcpy(NewCell->Data, Key);
		Pos = Hash(Key, H->TableSize); // 初始散列位置
									   // 将NewCell插入为H->Heads[Pos]链表的第1个结点 
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		return true;
	}
	else { // 关键词已存在
		printf("键值已存在");
		return false;
	}
}

void DestroyTable(HashTable H)
{
	int i;
	Position P, Tmp;

	// 释放每个链表的结点 
	for (i = 0; i<H->TableSize; i++) {
		P = H->Heads[i].Next;
		while (P) {
			Tmp = P->Next;
			free(P);
			P = Tmp;
		}
	}
	free(H->Heads); // 释放头结点数组 
	free(H);        // 释放散列表结点
}
