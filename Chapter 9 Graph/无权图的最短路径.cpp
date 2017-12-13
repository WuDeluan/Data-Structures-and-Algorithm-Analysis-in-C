#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
#define INFINITY 65535

typedef int DistType;
typedef int Vertex;
typedef int WeightType;     //边的权值设为整数
typedef char DataType;      //顶点的数据存储
typedef int ElementType;
typedef struct QueueRecord
{
	int Front;
	int Rear;
	int Capacity;
	ElementType *Array;
}*Queue;

void InitQueue(Queue Q)
{
	Q->Front = 0;
	Q->Rear = 0;
}

Queue CreatQueue(int MaxSize)
{
	Queue Q = (QueueRecord*)malloc(sizeof(QueueRecord));
	Q->Capacity = MaxSize;
	Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxSize);
	InitQueue(Q);
	return Q;
}

int Enqueue(Queue Q, ElementType X)
{
	if ((Q->Rear + 1) % Q->Capacity == Q->Front)
		return -1;
	Q->Rear = (Q->Rear + 1) % Q->Capacity;
	Q->Array[Q->Rear] = X;
	return 0;
}

ElementType Dequeue(Queue Q)
{
	if (Q->Front == Q->Rear)
		return -1;
	Q->Front = (Q->Front + 1) % Q->Capacity;
	return Q->Array[Q->Front];
}

//边的定义
typedef struct ENode
{
	Vertex V1, V2;        //有向边<V1,V2>
}*Edge;

//邻接点的定义
typedef struct AdjVNode
{
	Vertex AdjV;           //邻接点下标
	struct AdjVNode *Next; //指向下一邻接点的指针
}*PtrToAdjVNode;

//顶点表头结点的定义
typedef struct VNode
{
	PtrToAdjVNode FirstEdge;   //边表头指针
	DataType Data;             //存顶点的数据
}AdjList[MaxVertexNum];        //AdjList是邻接表类型

							   //图结点的定义
typedef struct GNode
{
	int Nv;     //顶点数
	int Ne;     //边数
	AdjList G;  //邻接表
}*LGraph;       //以邻接表方式存储图类型

				//初始化邻接表图
LGraph CreateGraph(int VertexNum)
{
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接表表头
	for (V = 0; V <= Graph->Nv; V++)    //注意等号
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

//插入边
void InsertEdge(LGraph Graph, Edge E)
{
	PtrToAdjVNode NewNode;

	//插入边<V1,V2>
	//为V2建立新的邻接点
	NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
	NewNode->AdjV = E->V2;
	//将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
}

//创建一个邻接表图
LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);          //读入顶点个数
	Graph = CreateGraph(Nv);   //初始化有Nv个顶点但没有边的图

	scanf("%d", &Graph->Ne);   //读入边数
	if (Graph->Ne != 0)        //如果有边
	{
		E = (Edge)malloc(sizeof(ENode)); //建立边结点
		for (i = 0; i < Graph->Ne; i++)
		{
			//读入边，格式为“起点”，“终点”，“权重”
			scanf("%d %d", &E->V1, &E->V2);
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}
typedef struct TableNode
{
	int Known;
	DistType Distence;
	Vertex Path;
}Table;


void InitTable(Vertex Start, LGraph Graph, Table *T)
{
	int i;
	for (i = 0; i <= Graph->Nv; i++)
	{
		T[i].Distence = INFINITY;
		T[i].Known = 0;
		T[i].Path = 0;
	}
	T[Start].Distence = 0;
}

void Unweighted(Table *T, LGraph Graph, Vertex S)
{
	Queue Q;
	Q = CreatQueue(Graph->Nv);
	InitQueue(Q);
	Vertex V;

	Enqueue(Q, S);   //将初始点S入队

	while (Q->Front != Q->Rear)    //队列非空
	{
		V = Dequeue(Q);        //将一个结点出队
		T[V].Known = 1;        //标记该结点

		PtrToAdjVNode W;
		//遍历当前结点的所有邻接点
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
		{
			if (T[W->AdjV].Distence == INFINITY)
			{
				T[W->AdjV].Distence = T[V].Distence + 1;
				T[W->AdjV].Path = V;
				Enqueue(Q, W->AdjV);
			}
		}
	}
}

//测试函数
int main()
{
	LGraph Graph = BuildGraph();
	Table  T[MaxVertexNum];
	InitTable(3, Graph, T);

	Unweighted(T, Graph, 3);

	Vertex V;
	for (V = 1; V <= Graph->Nv; V++)
		printf("%d ", T[V].Distence);
}
