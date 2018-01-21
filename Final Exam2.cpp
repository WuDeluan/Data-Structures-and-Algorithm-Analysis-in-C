void PreOrder(Tree T)
{
    if(T == NULL)
      return ;
    printf("%d ",T->Key);
    PreOrder(T->Left);
    PreOrder(T->Right);
}

void InOrder(Tree T)
{
    if(T == NULL)
      return ;
    InOrder(T->Left);
    printf("%d ",T->Key);
    InOrder(T->Right);
}

void PostOrder(Tree T)
{
    if(T == NULL)
      return ;
    PostOrder(T->Left);
    PostOrder(T->Right);
    printf("%d ",T->Key);
}

BST FindMin(BST T)
{
    if(T == NULL)
       return NULL;
    if(T->Left == NULL)
       return T;
    else
       return FindMin(T->Left);
}

BST FindMax(BST T)
{
     if(T != NULL){
        while(T->Right != NULL)
            T = T->Right;
     return T;
}

int IsBST(BST T)
{
    static int flag = 1;
    static KeyType LastKey = 0;
    if(T->Left && flag)
       IsBST(T->Left);
    if(T->Key < LastKey)
       flag = 0;
    LastKey = Key;
    if(T->Right && Flag)
       IsBST(T):
    return flag;
}

void InOrder(Tree T)
{
    if(T == NULL)
      return ;
    InOrder(T->Right);
    printf("%d ",T->Key);
    InOrder(T->Left);
} 
