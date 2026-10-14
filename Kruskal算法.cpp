//Kruskal 算法用于求 无向带权连通图的最小生成树 MST
/*Kruskal 算法思想：
1.将所有边按权值从小到大排序
2.每次选出最小的边，若该边的两个点不是联通的点，就加入MST,并将它们联通
3.对于点是否联通，可以通过并查集判断

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u,v;
    int w;
}Edge;


int cmp(const void* a,const void* b){
    const Edge* pa=(const Edge* )a;
    const Edge* pb=(const Edge* )b;
    if(pa->w < pb->w) return -1;
    if(pa->w > pb->w) return 1;
    return 0;
}
int *parent;//parent[i]代表点i的父亲，若其为负数，说明该点是根节点，并且其值的绝对值代表树的大小
int find_Edge(int n){
    if(parent[n]<0) return n;
    return parent[n]=find_Edge(parent[n]);
}

int Union(int x,int y){
    int parent_x=find_Edge(x);
    int parent_y=find_Edge(y);
    if(parent_x==parent_y) return 0;
    if(-parent[parent_x]<-parent[parent_y]){
        parent[parent_y]+=parent[parent_x];
        parent[parent_x]=parent_y;
    }
    else{
        parent[parent_x]+=parent[parent_y];
        parent[parent_y]=parent_x;
    }
    return 1;
    
}
long long Kruskal(Edge* edges,int m,int n)
{
    parent = (int *)malloc((n + 1) * sizeof(int));
    for(int i=1;i<=n;i++) parent[i]=-1;
    long long total=0;
    int cnt=0;//边数
    qsort(edges,m,sizeof(Edge),cmp);
    for(int i=0;i<m&&cnt<n-1;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;
        if(find_Edge(u)!=find_Edge(v)){
            Union(u,v);
            total+=w;
            cnt++;
        }
    }
    if(cnt==n-1) return total;
    else return -1;
}