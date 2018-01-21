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

void DFS(Vertex Start, MGraph G,int Visit[])  
{
	Vertex V, W;
	V = Start;
	printf("%d  ", V);
	Visit[Start] = 1;
	for (W = 0; W < G->Nv; W++)
	{
		if (G->Weight[V][W] != 0 && Visit[W] == 0)
			DFS(W, G, Visit);
	}
}


void BFS(Vertex Start, MGraph G)
{
	Vertex V, W;
	Vertex Queue[MaxVertexNum];
	int Visit[MaxVertexNum];
	int Rear = 0, Front = 0;
	Queue[Rear++] = Start;
	for (V = 0; V < G->Nv; V++)
		Visit[V] = 0;
	while (Rear != Front)
	{
		V = Queue[Front++];
		printf("%d  ", V);
		Visit[V] = 1;
		for (W = 0; W < G->Nv; W++)
		{
			if (G->Weight[V][W] != 0 && Visit[W] == 0)
			{
				Visit[W] = 1;
				Queue[Rear++] = W;
			}
		}
	}
}
void Judge（Graph G）
{
    int i = 0;
    DFS(1，G,Visit，i);
    if(i == G->Nv) //遍历的结点总数与图的结点总数比较
       return 1; //是连通图
    else
       return 0;//不是连通图
}

void DFS(Vertex V, Graph G,int Visit[],int i)  
{
	Vertex W;
	i++;   //遍历一个结点，i加一
	Visit[V] = true;
	for (W = 0; W < G->Nv; W++)
	{
		if (G->Weight[V][W] != 0 && Visit[W] == flase)
			DFS(W, G, Visit,i);
	}
}
