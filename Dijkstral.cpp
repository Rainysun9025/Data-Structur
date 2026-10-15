#include <stdio.h>
#include <stdbool.h>

#define MAXV 1000
#define INF 0x3f3f3f3f

int graph[MAXV][MAXV];

void initial()
{
    for(int i=0;i<MAXV;i++){
        for(int u=0;u<MAXV;u++){
            graph[i][u]=INF;
        }
    }
    return;
}
bool Dijkstral(int n,int start)
{
    int dis[n+1];
    bool visit[n+1];
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        visit[i]=false;
    }
    dis[start]=0;
    int cnt=1;
    while(cnt<=n-1){
        int min=INF;
        int k=-1;
        for(int i=1;i<=n;i++){
            if(!visit[i]&&dis[i]<min){
                min=dis[i];
                k=i;
            }
        }
        if(k==-1) {printf("不连通\n"); return false;}
        visit[k]=true;
        //开始松弛
        for(int i=1;i<=n;i++){
            //w(k,i)+dis[k]<dis[i]
            if(graph[k][i]!=INF&&graph[k][i]+dis[k]<dis[i]){
                dis[i]=graph[k][i]+dis[k];
            }
        }
        cnt++;
    }
    return true;
}