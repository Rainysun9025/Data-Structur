#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100          // 最大顶点数
typedef int WeightType;           // 权重的类型（设为 int）
typedef int DataType;             // 顶点数据的类型（设为 int）

/* 2. 原来的代码 */
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv; /* 顶点数 */
    int Ne; /* 边数 */
    WeightType G[MaxVertexNum][MaxVertexNum]; // 邻接矩阵
    DataType Data[MaxVertexNum];              // 顶点数据数组
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */
typedef int Vertex; /* 用顶点下标表示顶点，为整型 */
MGraph CreateGraph( int VertexNum )
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        for (W=0; W<Graph->Nv; W++)
            Graph->G[V][W] = 0; /* 或INFINITY */

    return Graph;
}
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 4. 插入边的函数 */
void InsertEdge( MGraph Graph, Edge E )
{
    /* 插入边 <V1, V2> */
    Graph->G[E->V1][E->V2] = E->Weight;

    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[E->V2][E->V1] = E->Weight;

    Graph->Ne++; // 边数加1
}
void DestroyGraph(MGraph Graph) {
    //释放内存
    free(Graph);
}