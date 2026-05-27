#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 10000
int dsu[MAXSIZE];
void Initial()
{
    int i;
    for(i=0;i<MAXSIZE;i++) dsu[i]=-1;
    return;
}
int Find(int x)//查找第x台电脑所属于哪个集合（找他的根）
{
    int root=dsu[x];
    if(root<0) return x;
    return dsu[x]=Find(dsu[x]);//路径压缩
}
void Check()
{
    int a,b;
    scanf("%d %d",&a,&b);
    //检查a b之间是否联通
    int r1=Find(a);
    int r2=Find(b);
    if(r1==r2) printf("Yes\n");
    else printf("No\n");
    return;
}
void Union()
{
    int a,b;
    scanf("%d %d",&a,&b);
    //在a b之间接线
    int r1=Find(a);
    int r2=Find(b);
    if(r1==r2) return;
    if(dsu[r1]<dsu[r2]) {
        dsu[r1]+=dsu[r2];
        dsu[r2]=r1;//r2是小集合，r1是大集合,然后按大小合并 
        //注意要先保存大小，再合并
    }
    else  {
        dsu[r2]+=dsu[r1];
        dsu[r1]=r2;
    }
    return;
}
void LastCheck(int n)
{
    //检查有几个联通集
    int i;
    int cnt=0;
    for(i=1;i<=n;i++)
    {
        if(dsu[i]<0) cnt++;
    }
    if(cnt==1) printf("All computers have been connected!\n");
    else printf("There are %d connected sets!\n",cnt);
    return;
}
int main()
{
    int n;
    scanf("%d",&n);//n台计算机
    char in;
    do{
        scanf(" %c",&in);
        if(in=='C') Check();
        if(in=='I') Union();
        if(in=='S') LastCheck(n);
    }while(in!='S');
    return 0;
}
