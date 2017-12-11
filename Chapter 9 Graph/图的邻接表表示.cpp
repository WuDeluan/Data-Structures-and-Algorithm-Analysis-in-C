#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100    //最大顶点数设为100
typedef int Vertex;         //用顶点下标表示顶点
typedef int WeightType;     //边的权值设为整数
typedef char DataType;      //顶点的数据存储

//边的定义
typedef struct ENode
{
	Vertex V1, V2;        //有向边<V1,V2>
	WeightType Weight;    //权重
}*Edge;

//邻接点的定义
typedef struct AdjVNode
{
	Vertex AdjV;           //邻接点下标
	WeightType Weight;     //边权重
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
	for (V = 0; V < Graph->Nv; V++)
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
	NewNode->Weight = E->Weight;
	//将V2插入V1的表头
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	//若是无向图，还要插入边<V2,V1>
	//为V1建立新的邻接点
	NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	//将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

//创建一个邻接表图
LGraph BuildGraph()
{
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;

	scanf("%d", &Nv);          //读入顶点个数
	Graph = CreateGraph(Nv);   //初始化有Nv个顶点但没有边的图

	scanf("%d", &Graph->Ne);   //读入边数
	if (Graph->Ne != 0)        //如果有边
	{
		E = (Edge)malloc(sizeof(ENode)); //建立边结点
		for (i = 0; i < Graph->Ne; i++)
		{
			//读入边，格式为“起点”，“终点”，“权重”
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}

	//如果顶点有数据的话，读入数据
	for (V = 0; V < Graph->Nv; V++)
		scanf("%c", &Graph->G[V].Data);

	return Graph;
}

//测试函数
int main()
{
	LGraph Graph = BuildGraph();
	Vertex V;
	PtrToAdjVNode P;
	for (V = 0; V < Graph->Nv; V++)
	{
		for (P = Graph->G[V].FirstEdge; P; P = P->Next)
			printf("%d ", P->AdjV);
		printf("\n");
	}
}
