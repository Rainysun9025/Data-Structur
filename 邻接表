#include <stdio.h>
#include <string.h>

#define MAXN 1005    // 最大点数
#define MAXM 10005   // 最大边数（无向图要开两倍）

int head[MAXN];      // head[u] = 以 u 为起点的第一条边的编号
int to[MAXM];        // to[i]   = 第 i 条边指向的点
int nxt[MAXM];       // nxt[i]  = 和第 i 条边同起点的下一条边编号
int idx;             // 当前已经用了多少条边（每加一条 idx++）

// 初始化
void init() {
    memset(head, -1, sizeof(head));
    idx = 0;
}

// 加一条有向边 u -> v
void addEdge(int u, int v) {
    to[idx] = v;          // 这条边指向 v
    nxt[idx] = head[u];  // 接到 u 的边表前面
    head[u] = idx++;      // 更新 u 的第一条边
}