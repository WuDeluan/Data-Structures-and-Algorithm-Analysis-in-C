#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100   //最大顶点数设为100
#define INFINITY 65535     //∞设为双字节无符号整数的最大值65535
typedef int Vertex;        //顶点下标表示顶点
typedef int WeightType;    //边的权值
typedef char DataType;     //顶点存储

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
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(GNode));  //建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接矩阵
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->Weight[V][W] = INFINITY;

	return Graph;
}

//边的插入
void InsertEdge(MGraph Graph,Edge E)
{
	Graph->Weight[E->V1][E->V2] = E->Weight; 
	Graph->Weight[E->V2][E->V1] = E->Weight;
}

//构建一个图
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	scanf("%d", &Nv);      //读入顶点个数
	Graph = CreateGraph(Nv);  //初始化图

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

	for (V = 0; V < Graph->Nv; V++)
		scanf("%c", &Graph->Data[V]);

	return Graph;
}
