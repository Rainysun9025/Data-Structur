#include <stdio.h>
#include <stdlib.h>

/* ================= 补充的基础定义 ================= */
#define MaxVertexNum 100       // 最大顶点数
typedef int Vertex;            // 顶点下标类型
typedef int WeightType;        // 边权类型
typedef int DataType;          // 顶点数据，可以是任意类型

/* ================= 结构体定义 ================= */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;          /* 一条边指向的邻接点下标 */   //比如 V1-->V2  这里存储的就是V2
    WeightType Weight;    /* 边权重 */
    PtrToAdjVNode Next;   /* 指向下一条边的指针 */
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;  /* 指向第一条边的指针 */   //最后插入进来的边
    DataType Data;            /* 存顶点的数据 */
} AdjList[MaxVertexNum];      /* AdjList是邻接表类型 */
//AdjList指的是 元素为 struct Vnode，长度为 MaxVertexNum 的数组

typedef struct GNode *PtrToGNode;
struct GNode {//总体
    int Nv;               /* 顶点数 */
    int Ne;               /* 边数 */
    AdjList G;            /* 邻接表 */
};
typedef PtrToGNode LGraph;    /* 以邻接表方式存储的图类型 */

/* 定义边结构（配合InsertEdge使用） */
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;       /* 有向边 <V1, V2> */
    WeightType Weight;   /* 权重 */
};
typedef PtrToENode Edge;

/* ================= 图的初始化 ================= */
LGraph CreateGraph( int VertexNum )
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    if (!Graph) {
        printf("内存分配失败\n");
        return NULL;
    }
    
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for ( V=0; V<Graph->Nv; V++ ) {
        Graph->G[V].FirstEdge = NULL;  // 初始化每个顶点的链表头为空
    }

    return Graph;
}

/* ================= 插入边================= */
void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;

    /********** 插入边 <V1, V2> **********/
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    /* 将V2插入V1的表头（头插法） */
    NewNode->Next = Graph->G[E->V1].FirstEdge;//先保存节点V1已经插好的数据到新节点的Next里面
    Graph->G[E->V1].FirstEdge = NewNode;//再把节点V1指向新节点

    /********** 若是无向图，还要插入边 <V2, V1> **********/
    /* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    /* 将V1插入V2的表头（头插法） */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;

    Graph->Ne++; // 边数加1
}

/* ================= 简单的测试用例 ================= */
int main() {
    // 创建包含5个顶点的图
    LGraph Graph = CreateGraph(5);

    // 创建一条边：0 -> 1，权重为 10
    Edge E = (Edge)malloc(sizeof(struct ENode));
    E->V1 = 0;
    E->V2 = 1;
    E->Weight = 10;

    // 将边插入图中
    InsertEdge(Graph, E);

    printf("图创建成功！\n");
    printf("顶点数: %d\n", Graph->Nv);
    printf("边数: %d\n", Graph->Ne);
    printf("邻接表首节点 (顶点0) 指向的顶点: %d\n", Graph->G[0].FirstEdge->AdjV);

    // 释放内存（略，实际工程需注意内存释放）
    free(E);
    free(Graph);
    return 0;
}