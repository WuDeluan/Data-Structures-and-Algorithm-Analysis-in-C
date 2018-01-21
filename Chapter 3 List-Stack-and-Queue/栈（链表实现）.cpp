#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node
{
   ElementType Element;
   struct Node *Next;
}*Stack;

Stack InitStack()
{
   Stack S = (Node*)malloc(sizeof(Node));
   S->Next = NULL;
   return S;
}

void Push(Stack S,ElementType X)
{
     Node *Tmp = (Node*)malloc(sizeof(Node));
     Tmp->Element = X;
     Tmp->Next = S->Next;
     S->Next = Tmp;
}

int Pop(Stack S)
{
   if(S->Next == NULL)
       return -1;
   Node *Tmp = S->Next;
   S->Next = Tmp->Next;
   free(Tmp);
   return 0;
}

int main()
{
   Stack S = InitStack();
   Push(S,1);
   Pop(S);
}
