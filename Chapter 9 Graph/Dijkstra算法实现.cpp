/*伪码描述：
void Dijkstra(Graph G,Table T)
{
     Vertex V,W;
     
     for(; ;)
     {
         V = smallst unknown distance vertex;
	 if(V == NotAVertex)
	    break;
	  T[V].konwn = ture;
	  for each W adjancent to V;
	  if(!T[W}.konwn)
	     if(T[V].dis + Cvw < T[W].dis)
	     {
	        Decrease(T[W].dis to T[V}.dis + Cvw);
		T[W].path = V;
	      }
        }
}
*/
	 

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
	Vertex V1, V2;       //边的两个顶点
	WeightType Weight;   //边的权重
}*Edge;

//图的结点定义
typedef struct GNode
{
	int Nv;         //顶点数
	int Ne;         //边数
	WeightType Weight[MaxVertexNum][MaxVertexNum];   //邻接矩阵
	DataType Data[MaxVertexNum];     //存顶点的数据
}*MGraph;

//初始化一个图
MGraph CreateGraph(int VertexNum)
{
	//初始化一个有VertexNum个结点但没有边的图
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(GNode));  //建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接矩阵,将权重置为∞
	for (V = 0; V <= Graph->Nv; V++)
		for (W = 0; W <= Graph->Nv; W++)
			Graph->Weight[V][W] = INFINITY;

	return Graph;
}

//边的插入
void InsertEdge(MGraph Graph, Edge E)
{
	Graph->Weight[E->V1][E->V2] = E->Weight;
}

//构建一个图
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);      //读入顶点个数
	Graph = CreateGraph(Nv);  //初始化一个有VertexNum个结点但没有边的图

	scanf("%d", &(Graph->Ne));  //读入边数
	if (Graph->Ne != 0)         //如果有边
	{
		E = (Edge)malloc(sizeof(ENode));  //建立边结点
										  //读入边，格式为“起点”，“终点”，“权重”
		for (i = 0; i < Graph->Ne; i++)
		{
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);   //插入边
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


void InitTable(Vertex Start, MGraph Graph, Table *T)
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

Vertex FindMinDist(MGraph Graph, Table *T)
{
	Vertex MinV, V;
	int MinDist = INFINITY;

	for (V = 0; V <= Graph->Nv; V++)
	{
		if (T[V].Known == 0 && T[V].Distence < MinDist)
		{
			MinDist = T[V].Distence;
			MinV = V;
		}
	}
	if (MinDist < INFINITY)
		return MinV;
	else
		return 0;
}

void PrintPath(Vertex V, Table *T)
{
	if (T[V].Path != 0)
	{
		PrintPath(T[V].Path, T);
		printf("to ");       //递归出口
	}
	printf("V%d ", V);
}

void Dijkstra(MGraph Graph, Table *T)
{
	Vertex V, W;
	for (;;)
	{
		V = FindMinDist(Graph, T);
		if (V == 0)
			break;
		T[V].Known = 1;
   		for (W = 0; W <= Graph->Nv; W++)
		{
			if(Graph->Weight[V][W] != INFINITY && T[W].Known == 0)
				if (T[V].Distence + Graph->Weight[V][W] < T[W].Distence)
				{
					T[W].Distence = T[V].Distence + Graph->Weight[V][W];
					T[W].Path = V;
				}
		}
	}
}

int main()
{
	MGraph Graph = BuildGraph();
	Table T[MaxVertexNum];
	InitTable(1,Graph,T);
	Dijkstra(Graph, T);
	Vertex V;
	for (V = 1; V <= Graph->Nv; V++)
	{
		printf("The distence of V%d is %d,and the path is ", V,T[V].Distence);
		PrintPath(V, T);
		printf("\n");
	}
	
}
/*
7 12
3 1 4
1 2 2
2 5 10
5 7 6
7 6 1
3 6 5
4 3 2
1 4 1
2 4 3
4 5 2
4 7 4
4 6 8
*/
