#include <stdio.h>
#include <string.h>

#define MAXN 1005    // 最大点数
#define MAXM 10005   // 最大边数（无向图要开两倍）

int head[MAXN];      // head[u] = 以 u 为起点的第一条边的编号 //实际上,就是最后一插入进来的边的编号
int to[MAXM];        // to[i]   = 第 i 条边指向的点
int nxt[MAXM];       // nxt[i]  = 和第 i 条边同起点的下一条边编号
int idx;             // 当前已经用了多少条边（每加一条 idx++）
int weight[MAXM];

// 初始化
void init() {
    memset(head, -1, sizeof(head));
    idx = 0;
}

// 加一条有向边 u -> v 边的权重是w
void addEdge(int u, int v,int w) {
    weight[idx] = w;     // 记录权重
    to[idx] = v;          // 这条边指向 v
    nxt[idx] = head[u];  // 接到 u 的边表前面
    head[u] = idx++;      // 更新 u 的第一条边
}
// 无向边加两次
void addUndirectedEdge(int u, int v, int w) {
    addEdge(u, v, w);
    addEdge(v, u, w);
}

/*
    for (int i = head[u]; i != -1; i = nxt[i]) {
    int v = to[i];
    int w = weight[i];   // 取出这条边的权重
    // 对 v 和 w 做需要的操作
    
    }
*/
/*
    举个例子
    head数组:              边数组 (to / nxt)
    [1] 0 ──────> [0] to=2 nxt=-1

    [2] 2 ──> [2] to=3 nxt=1 ──> [1] to=1 nxt=-1

    [3] 3 ──> [3] to=2 nxt=-1
*/