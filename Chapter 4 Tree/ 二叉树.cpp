#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct BTNode
{
	ElemType Data;		//数据元素
	struct BTNode *Lchild;	//指向左孩子结点
	struct BTNode *Rchild;	//指向右孩子结点
}*BTree,*Position ;
void CreateBTree(BTree &T, char *str)  
{
	BTree St[MaxSize];
	Position P = NULL;
	int Top = -1, k, j = 0;
	char ch = str[j];
	T = NULL;		//建立的二叉树初始时为空
	while (ch != '\0')  	//str未扫描完时循环
	{
		switch (ch)
		{
		case '(':Top++; St[Top] = P; k = 1; break;		//为左孩子结点
		case ')':Top--; break;
		case ',':k = 2; break;                      		//为孩子结点右结点
		default:P = (BTNode*)malloc(sizeof(BTNode));
			P->Data = ch; P->Lchild = P->Rchild = NULL;
			if (T == NULL)                    	 	//P为二叉树的根结点
				T = P;
			else  						//已建立二叉树根结点
			{
				switch (k)
				{
				case 1:St[Top]->Lchild = P; break;
				case 2:St[Top]->Rchild = P; break;
				}
			}
		}
		ch = str[++j];
	}
}

Position FindNode(BTree T, ElemType X) //查找某一节点
{
	Position P;
	if (T == NULL)
		return NULL;
	else if (T->Data == X)   //找到了
		return T;
	else
	{
		P = FindNode(T->Lchild, X);           //递归查找左子树
		if (P != NULL)
			return P;                     //如果找到，返回节点位置
		else
			return FindNode(T->Rchild, X); //递归查找右子树
	}
}

Position LchildNode(Position P) //返回左孩子
{
	return P->Lchild;
}

Position RchildNode(Position P) //返回右孩子
{
	return P->Rchild;
}

int BTreeHeight(BTree T)
{
	int LHeight, RHeight;
	if (T == NULL) 
		return 0; 				//空树的高度为0
	else
	{
		LHeight = BTreeHeight(T->Lchild);	//求左子树的高度为LHeight
		RHeight = BTreeHeight(T->Rchild);	//求右子树的高度为RHeight
		return (LHeight > RHeight) ? (LHeight + 1) : (RHeight + 1);
	}
}

void DispBTree(BTree T)
{
	if (T != NULL)
	{
		printf("%c", T->Data);
		if (T->Lchild != NULL || T->Rchild != NULL)
		{
			printf("(");				//有孩子结点时才输出(
			DispBTree(T->Lchild);			//递归处理左子树
			if (T->Rchild != NULL) printf(",");	//有右孩子结点时才输出,
			DispBTree(T->Rchild);			//递归处理右子树
			printf(")");				//有孩子结点时才输出)
		}
	}
}

int NodeNum(BTree T) //计算树的节点个数
{
	if (T)
		return NodeNum(T->Lchild) + NodeNum(T->Rchild) + 1;
	else
		return 0;
}

void PreOrder(BTree T) //前序遍历
{
	if (T == NULL)
		return;
	printf("%c ", T->Data);
	PreOrder(LchildNode(T));
	PreOrder(RchildNode(T));
}

void InOrder(BTree T) //中序遍历
{
	if (T == NULL)
		return;
	InOrder(LchildNode(T));
	printf("%c ", T->Data);
	InOrder(RchildNode(T));
}

void PostOrder(BTree T)  //后序遍历
{
	if (T == NULL)
		return;
	PostOrder(LchildNode(T));
	PostOrder(RchildNode(T));
	printf("%c ", T->Data);
}

void PrintNodeAtLevel(BTree T, int Level) //打印当前层的节点
{
	// 空树或层级不合理
	if (T == NULL || Level < 1)
		return;
	if (Level == 1)
	{
		printf("%c ", T->Data);
		return;
	}
	// 左子树的 level - 1 级
	PrintNodeAtLevel(T->Lchild, Level - 1);
	// 右子树的 level - 1 级
	PrintNodeAtLevel(T->Rchild, Level - 1);
}

void TravLevel(BTree T)  //逐层遍历二叉树
{
	if (T == NULL)
		return;
	int Height = BTreeHeight(T);
	int i;
	for (i = 1; i <= Height; i++)
	{
		PrintNodeAtLevel(T, i);
		printf("\n");
	}
}


int main()
{
	BTree T;
	T = (BTNode*)malloc(sizeof(BTNode));
	CreateBTree(T, "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("输出二叉树:");
	DispBTree(T);
	printf("\n");
	Position N = FindNode(T, 'H');
	Position P = LchildNode(N);
	printf("H的左孩子是：%c ,", P->Data);
	P = RchildNode(N);
	printf("右孩子是： %c .\n", P->Data);
	printf("二叉树b的深度: %d.\n", BTreeHeight(T));
	printf("二叉树b的结点个数: %d.\n", NodeNum(T));
	printf(" 先序遍历序列:\n");
	printf("     递归算法:"); PreOrder(T); printf("\n");
	printf(" 中序遍历序列:\n");
	printf("     递归算法:"); InOrder(T); printf("\n");
	printf(" 后序遍历序列:\n");
	printf("     递归算法:"); PostOrder(T); printf("\n");
	printf(" 层次遍历序列:"); printf("\n");
	TravLevel(T); printf("\n");

	return 0;
}
