#include <stdio.h>
#include <malloc.h>
typedef int KeyType;
typedef char InfoType[10];
typedef struct TreeNode           		//记录类型
{
	KeyType Key;              		//关键字项
	InfoType Data;             		//其他数据域
	struct TreeNode *Lchild, *Rchild;	//左右孩子指针
} *BSTree,*Position;
int InsertBST(BSTree &T, KeyType K)
{
	if (T == NULL)				//原树为空, 新插入的记录为根结点
	{
		T = (TreeNode*)malloc(sizeof(TreeNode));
		T->Key = K;
		T->Lchild = T->Rchild = NULL;
		return 0;
	}
    if (K == T->Key) 				//树中存在相同关键字的结点,返回-1
		return -1;
	else if (K < T->Key)
		return InsertBST(T->Lchild, K);	//插入到T的左子树中
	else if(K > T->Key)
		return InsertBST(T->Rchild, K);  //插入到T的右子树中
}

void DispBST(BSTree T)		                 //输出一棵排序二叉树
{
	if (T != NULL)
	{
		printf("%d", T->Key);
		if (T->Lchild != NULL || T->Rchild != NULL)
		{
			printf("(");					//有孩子结点时才输出(
			DispBST(T->Lchild);				//递归处理左子树
			if (T->Rchild != NULL)
				printf(",");	//有右孩子结点时才输出,
			DispBST(T->Rchild);				//递归处理右子树
			printf(")");					//有孩子结点时才输出)
		}
	}
}
Position CreateBST(KeyType a[], int n)	//返回BST树根结点
{
	BSTree T = NULL;         			//初始时T为空树
	int i = 0;
	while (i < n)
	{
		printf("   第%d步,插入%d元素:", i + 1, a[i]);
		InsertBST(T, a[i++]);  			//将关键字a[i]插入二叉排序树T中
		DispBST(T); printf("\n");
	}
	return T;               			//返回建立的二叉排序树的根
}
Position SearchBST(BSTree T, KeyType K)
{
	if (T == NULL)      	
		return T;
	if (K < T->Key)
		return SearchBST(T->Lchild, K);  //在左子树中递归查找
	else if (K > T->Key)
		return SearchBST(T->Rchild, K);  //在右子树中递归查找
	else
		return T;
}
Position SearchBST1(BSTree T, KeyType K, BSTree f1, BSTree &f)
/*在T中查找关键字为k的结点,若查找成功,该函数返回该结点的指针,
  f返回其双亲结点;否则,该函数返回NULL。其调用方法如下:
  SearchBST(bt,x,NULL,f);
  这里的第3个参数f1仅作中间参数,用于求f,初始设为NULL*/
{
	if (T == NULL)
	{
		f = NULL;
		return NULL;
	}
	else if (K == T->Key)
	{
		f = f1;
		return T;
	}
	else if (K < T->Key)
		return SearchBST1(T->Lchild, K, T, f);  //在左子树中递归查找
	else 
		return SearchBST1(T->Rchild, K, T, f);  //在右子树中递归查找
}

Position FindMin(BSTree T)    //递归实现
{
	if (T == NULL)
		return NULL;
	if (T->Lchild == NULL)
		return T;
	else
		return FindMin(T->Lchild);
}

Position FindMax(BSTree T)   //非递归实现
{
	if (T != NULL)
		while (T->Rchild != NULL)
			T = T->Rchild;
	return T;
}

Position DeleteBST(BSTree T, KeyType K)
{
	Position TmpCell;
	if (T == NULL) //树T为空
		return T;
	if (K < T->Key)
		T->Lchild = DeleteBST(T->Lchild, K);   //递归查找左子树
	else if (K > T->Key)
		T->Rchild = DeleteBST(T->Rchild, K);   //递归查找右子树
	else  //找到节点
	{
		if (T->Lchild && T->Rchild)            //有两个孩子
		{
			TmpCell = FindMin(T->Rchild);  //查找右子树中最小的节点
			T->Key = TmpCell->Key;
			T->Rchild = DeleteBST(T->Rchild, T->Key);
		}
		else                                   //只有一个孩子或没有孩子
		{
			TmpCell = T;
			if (T->Lchild == NULL)         //没有左孩子
				T = T->Rchild;
			else if (T->Rchild == NULL)    //没有右孩子
				T = T->Rchild;
			free(TmpCell);
		}
	}
	return T;
}

Position Search1(BSTree T, KeyType K) //递归查找某一节点
{
	if (T == NULL)
		return NULL;
	printf("%d ",T->Key);
	if (K < T->Key)
		return Search1(T->Lchild, K);
	else if (K > T->Key)
		return Search1(T->Rchild, K);
	else
		return T;
}

Position Search2(BSTree T, KeyType K) //非递归查找某一节点
{
	if (T == NULL)
		return NULL;
	while (T) {
		printf("%d ", T->Key);
		if (K < T->Key)
			T = T->Lchild;
		else if (K > T->Key)
			T = T->Rchild;
		else
			return T;
	}
}

int IsBST(BSTree T)    //判断该树是否为二叉排序树 
{
	                       //静态变量，只执行一次！！！
	static int  flag = 1;  //标记节点是否符合二叉排序树的要求
	static int LastKey = 0;//记录上一节点的关键值
	                       //类似中序遍历！！！
	if (T->Lchild && flag)
		IsBST(T->Lchild);
	if (T->Key < LastKey)
		flag = 0;
	LastKey = T->Key;
	if (T->Rchild && flag)
		IsBST(T->Rchild);
	return  flag;
}

int Compare(BSTree T, BSTree P)  //比较两棵二叉树是否相同
{
	if (T == NULL && P == NULL)
		return 1;
	else if (T != NULL && P != NULL)
	{
		if (T->Key == P->Key)
			return Compare(T->Lchild, P->Lchild) && Compare(T->Rchild, P->Rchild);
		else
			return 0;
	}
	else
		return 0;
}
void main()
{
	BSTree T;
	int x = 46, i;
	KeyType a[] = { 4,9,0,1,8,6,3,5,2,7 };
	int n = 10;
	printf(" 创建一棵BST树:\n");
	T = CreateBST(a, n);
	printf("   BST:"); DispBST(T); printf("\n");
	(IsBST(T) == 1) ? printf("bt是一棵BST树 \n") : printf("bt不是一棵BST树\n");
	printf("查找关键字（递归）：");
	Search1(T, 6);
	printf("\n");
	printf("查找关键字（非递归）：");
	Search2(T, 6);
	printf("\n");
	printf("删除操作：\n");
	printf("原BFS：");
	DispBST(T); printf("\n");
	printf("删除节点4：");
	DeleteBST(T, 4);
	DispBST(T); printf("\n");
	printf("删除节点5：");
	DeleteBST(T, 5);
	DispBST(T); printf("\n");
}
