#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Element int
#define MAXSIZE 100000
long long m;//多少个数据
struct dsu{
    Element data;
    int parent;//存储父节点下标
    //等于负数表示没有父亲，即自己就是根节点
    //如果等于负数，其绝对值表示集合的大小，用于并操作
};
struct dsu arr[MAXSIZE];

int Find(struct dsu *arr,Element X)
{
    int i;
    for(i=1; i<=m && arr[i].data!=X ;i++);
    if(i>m) return -1;
    //找到了节点x所在的下标

    for(;arr[i].parent>=0;i=arr[i].parent);
    //一直去找节点的父亲，直到找到了根节点

    return i;
}
void Union(struct dsu *arr,int x,int y)
{
    int rx = Find(arr,x);
    int ry = Find(arr,y);
    if (rx == -1 || ry == -1) return;
    if (rx == ry) return;
    if (arr[rx].parent > arr[ry].parent) {
        int tmp = rx;
        rx = ry;
        ry = tmp;
    }//保证大集合是rx
    arr[rx].parent += arr[ry].parent;//注意集合大小要改变
    arr[ry].parent = rx;//把小集合接到大集合上
    return;
}
void read_dsu(struct dsu* arr)
{
    long long i;
    printf("请输入有多少个数据: ");
    scanf("%lld",&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d",&arr[i].data);
        arr[i].parent=-1;
    }
    printf("请输入有多少组相连边: ");
    long long n;
    scanf("%lld",&n);
    printf("\n");
    
    for(i=0;i<n;i++)
    {
        Element a,b;
        scanf("%d %d",&a,&b);
        Union(arr,a,b);
    }
}