#include <stdio.h>
#include <string.h>

#define MAXN 1005//最大点数
#define MAXM 10005//最大边数

int head[MAXN];
//head[u]	    表示点 u 的第一条边的编号
//head[u] = -1	表示点 u 没有边
int to[MAXM];
//to[i]     表示第 i 条边指向哪个点
int next[MAXM];
//next[i]	表示和第 i 条边同一个起点的下一条边编号
int idx;
//idx	当前边的编号，也表示已经存了多少条边
int visited[MAXN];
/*
visited[u]	表示点 u 是否访问过
visited[u] = 0	没访问过
visited[u] = 1	已经访问过 
*/

// 初始化
void init() {
    memset(head, -1, sizeof(head));
    memset(visited, 0, sizeof(visited));
    idx = 0;
}

// 加边 u -> v
void addEdge(int u, int v) {
    to[idx] = v;          // 这条边指向 v
    next[idx] = head[u];  // 接到 u 的边表前面
    head[u] = idx++;      // 更新 u 的第一条边
}

// DFS 深度优先搜索
void dfs(int u) {
    visited[u] = 1;
    printf("%d ", u);

    // 遍历 u 的所有邻接点
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (!visited[v]) {
            dfs(v);
        }
    }
}

// BFS 广度优先搜索
void bfs(int start) {
    int q[MAXN];//队列
    int front = 0, rear = 0;

    visited[start] = 1;
    q[rear++] = start;

    while (front < rear) {
        int u = q[front++];
        printf("%d ", u);

        // 遍历 u 的所有邻接点
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if (!visited[v]) {
                visited[v] = 1;
                q[rear++] = v;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    init();

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        // 无向图加两条边
        addEdge(u, v);
        addEdge(v, u);

        // 有向图只写 addEdge(u, v)
    }

    printf("DFS: ");
    memset(visited, 0, sizeof(visited));
    dfs(1);

    printf("\nBFS: ");
    memset(visited, 0, sizeof(visited));
    bfs(1);

    return 0;
}