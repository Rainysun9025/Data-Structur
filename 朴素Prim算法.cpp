
/*
Prim 算法结局的问题:有n个点构成的图（不一定联通），生成一个最小生成树(不连通时不生成)
Prim 算法思想：
1.将图分为 最小生成树集合U，和非最小生成树集合V-U 
(显然U初始为空，可任意加入一个点作为起点，起点的不同并不影响最小生成树的权值和(只影响树的形态)，因为MST虽然不唯一，但其权值和一定唯一)
2.维护一个lowcost数组，lowcost[i]表示点i（属于集合V）到U的最短路径权值
(最开始时，lowcost[start]=0,其他根据邻接矩阵初始化，不直接相连设置为int_max)
3.贪心的思想，每次从lowcost数组拿出最小（并且他要属于V）的那个点（记作k），把他加入U，(显然，这里要维护一个visit数组来区分点是属于U or V)
(这里可以初始化k=-1，如果无法更新k，说明图不连通，无法生成最小生成树)
4.接下来因为U和V都更新了（k加入了U，离开了V），所以要更新lowcost数组，具体是遍历graph[k][...],如果跟k相连的这个点的权值小于了lowcost，那么更新lowcost
5.自然的，我们可以维护一个closest数组来确认一个点是如何连接到MST的，比如closest[i]=u表示点i是通过u连接到MST的
*/
#include <stdio.h>
#include <stdbool.h>

#define MAXV 1000
#define INF 0x3f3f3f3f
int graph[MAXV][MAXV];//邻接矩阵 graph[u][v]表示u---v的权值
int lowcost[MAXV];
int closest[MAXV];
bool visit[MAXV];
long Prim(int n,int start)
{
    //n为图的点数
    //start作为MST的起点
    long total=0;//MST权值和
    for(int i=0;i<n;i++){
        lowcost[i]=graph[start][i];
        closest[i]=start;
        visit[i]=false;
    }
    lowcost[start]=0;
    visit[start]=true;//start加入MST
    for(int cnt=1;cnt<n;cnt++){//cnt代表已经加入MST的点的个数
        int min=INF;
        int k=-1;
        for(int i=0;i<n;i++){
            if(!visit[i]&&lowcost[i]<min){
                k=i;
                min=lowcost[i];
            }
        }
        if(k==-1){
            printf("不连通\n");
            return -1;
        }
        //将k加入U,并更新total
        visit[k]=true;
        total+=lowcost[k];
        //更新lowcost
        for(int i=0;i<n;i++){
            if(!visit[i]&&graph[k][i]<lowcost[i]){
                lowcost[i]=graph[k][i];
                closest[i]=k;
            }
        }
    }
    return total;
}