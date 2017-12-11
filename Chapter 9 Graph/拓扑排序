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
	/*NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	//将V1插入V2的表头
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;*/
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
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			InsertEdge(Graph, E);
		}
	}

	//如果顶点有数据的话，读入数据
	/*for (V = 0; V < Graph->Nv; V++)
		scanf("%c", &Graph->G[V].Data);
		*/

	return Graph;
}

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

// 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标
bool TopSort( LGraph Graph, Vertex TopOrder[] )
{  
    int Indegree[MaxVertexNum], Index;
    Vertex V;
    PtrToAdjVNode W;
       Queue Q = CreatQueue( Graph->Nv );
  
    // 初始化Indegree[]
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;
         
    // 遍历图，得到Indegree[]
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; // 对有向边<V, W->AdjV>累计终点的入度
             
    // 将所有入度为0的顶点入列
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 )
            Enqueue(Q, V);
             
    // 下面进入拓扑排序 
    Index = 0; 
    while( Q->Front != Q->Rear){
        V = Dequeue(Q);       // 弹出一个入度为0的顶点
        TopOrder[Index++] = V; // 将之存为结果序列的下一个元素
        // 对V的每个邻接点W->AdjV
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
            if ( --Indegree[W->AdjV] == 0 )   // 若删除V使得W->AdjV入度为0 
                Enqueue(Q, W->AdjV);          // 则该顶点入列 
    } 
     
    if ( Index != Graph->Nv )
        return false; // 说明图中有回路, 返回不成功标志 
    else
        return true;
}

//测试函数
int main()
{
	LGraph Graph = BuildGraph();
	Vertex Top[MaxVertexNum];
	TopSort(Graph, Top);
	for (Vertex V = 0; V < Graph->Nv; V++)
		printf("%d ", Top[V]);
}
