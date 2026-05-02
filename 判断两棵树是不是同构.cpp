#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define ElementType char

int root1=-1,root2=-1;
int num1=0,num2=0;


struct TreeNode{
    ElementType Element;
    int left;
    int right;
};

struct TreeNode* T1;
struct TreeNode* T2;


void ReadData_CreatTree()
{
    int i;
    scanf("%d",&num1);
    int* check1=(int *)malloc(sizeof(int)*num1);
    for(i=0;i<num1;i++) check1[i]=0;
    struct TreeNode* t1=(struct TreeNode*)malloc(sizeof(struct TreeNode)*num1);
    T1=t1;
    if(num1)
    {
        char a,b,c;
        for(i=0;i<num1;i++)
        {
            scanf(" %c %c %c",&a,&b,&c);
            T1[i].Element=a;
            if(b!='-')
            {
                T1[i].left=b-'0';
                check1[T1[i].left]=1;
            }
            else T1[i].left=-1;
            if(c!='-')
            {
                T1[i].right=c-'0';
                check1[T1[i].right]=1;
            }
            else T1[i].right=-1;
        }
        for(i=0;i<num1;i++)
        {
            if(!check1[i]) break;
        }
        root1=i;
    }
    scanf("%d",&num2);
    int* check2=(int *)malloc(sizeof(int)*num2);
    for(i=0;i<num2;i++) check2[i]=0;
    struct TreeNode* t2=(struct TreeNode*)malloc(sizeof(struct TreeNode)*num2);
    T2=t2;
    if(num2)
    {
        char a,b,c;
        for(i=0;i<num2;i++)
        {
            scanf(" %c %c %c",&a,&b,&c);
            T2[i].Element=a;
            if(b!='-')
            {
                T2[i].left=b-'0';
                check2[T2[i].left]=1;
            }
            else T2[i].left=-1;
            if(c!='-')
            {
                T2[i].right=c-'0';
                check2[T2[i].right]=1;
            }
            else T2[i].right=-1;
        }
        for(i=0;i<num2;i++)
        {
            if(!check2[i]) break;
        }
        root2=i;
    }
}
bool Isomorphism(int rootIndex1,int rootIndex2)
{

    /*00 00
    00 01
    00 10
    00 11
    
    01 00
    01 01
    01 10
    01 11

    11 00
    11 01
    11 10
    11 11

    10 00
    10 01
    10 10
    10 11*/
    
    /*//两个子树都空
    if(rootIndex1==-1&&rootIndex2==-1) return true;
    //其中一个空，另一个不空
    if(rootIndex1==-1&&rootIndex2!=-1) return false;
    if(rootIndex1!=-1&&rootIndex2==-1) return false;
    
    //根的值不一样
    if(T1[rootIndex1].Element!=T2[rootIndex2].Element) return false;
    
    // 核心：判断是否需要交换子树
    // 如果左子树都为空，只需看右子树
    if (T1[rootIndex1].left == -1 && T2[rootIndex2].left == -1) {
        return Isomorphism(T1[rootIndex1].right, T2[rootIndex2].right);
    }
    // 如果右子树都为空，只需左子树
    if(T1[rootIndex1].right == -1 && T2[rootIndex2].right == -1)
    {
        return Isomorphism(T1[rootIndex1].left, T2[rootIndex2].left);
    }
    //左空右不空vs左不空右空
    if(T1[rootIndex1].left==-1&&T1[rootIndex1].right!=-1&&T2[rootIndex2].left!=-1&&T2[rootIndex2].right==-1)
    {
        return Isomorphism(T1[rootIndex1].right, T2[rootIndex2].left);
    }
    //左不空右空vs左空右不空
    if(T1[rootIndex1].left!=-1&&T1[rootIndex1].right==-1&&T2[rootIndex2].left==-1&&T2[rootIndex2].right!=-1)
    {
        return Isomorphism(T1[rootIndex1].left, T2[rootIndex2].right);
    }
    //只有左空
    if(T1[rootIndex1].left==-1&&T1[rootIndex1].right!=-1&&T2[rootIndex2].left!=-1&&T2[rootIndex2].right!=-1)
    {
        return Isomorphism(T1[rootIndex1].right, T2[rootIndex2].left)||Isomorphism(T1[rootIndex1].right, T2[rootIndex2].right);
    }
    if(T1[rootIndex1].left!=-1&&T1[rootIndex1].right!=-1&&T2[rootIndex2].left==-1&&T2[rootIndex2].right!=-1)
    {
        return Isomorphism(T1[rootIndex1].left, T2[rootIndex2].right)||Isomorphism(T1[rootIndex1].right, T2[rootIndex2].right);
    }
    //只有右空
    if(T1[rootIndex1].left!=-1&&T1[rootIndex1].right==-1&&T2[rootIndex2].left!=-1&&T2[rootIndex2].right!=-1)
    {
        return Isomorphism(T1[rootIndex1].left, T2[rootIndex2].left)||Isomorphism(T1[rootIndex1].left, T2[rootIndex2].right);
    }
    if(T1[rootIndex1].left!=-1&&T1[rootIndex1].right!=-1&&T2[rootIndex2].left!=-1&&T2[rootIndex2].right==-1)
    {
        return Isomorphism(T1[rootIndex1].left, T2[rootIndex2].left)||Isomorphism(T1[rootIndex1].right, T2[rootIndex2].left);
    }
    //根在，但是四大皆空
    if(T1[rootIndex1].left==-1&&T1[rootIndex1].right==-1&&T2[rootIndex2].left==-1&&T2[rootIndex2].right==-1) return true;
    //根在，但是有一个是叶子节点，有一个不是
    if((T1[rootIndex1].left==-1&&T1[rootIndex1].right==-1)&&(T2[rootIndex2].left!=-1||T2[rootIndex2].right!=-1)) return false;
    if((T1[rootIndex1].left!=-1||T1[rootIndex1].right!=-1)&&(T2[rootIndex2].left==-1&&T2[rootIndex2].right==-1)) return false;

    //如果左右子树都不为空
    if(T1[rootIndex1].left != -1 && T2[rootIndex2].left != -1)
    {
        return (Isomorphism(T1[rootIndex1].left, T2[rootIndex2].left)&&Isomorphism(T1[rootIndex1].right, T2[rootIndex2].right))||
        (Isomorphism(T1[rootIndex1].left, T2[rootIndex2].right)&&Isomorphism(T1[rootIndex1].right, T2[rootIndex2].left));
    }*/
     // 1. 两个都空 -> 同构
    if (rootIndex1 == -1 && rootIndex2 == -1) return true;
    // 2. 一个空一个不空 -> 不同构
    if (rootIndex1 == -1 || rootIndex2 == -1) return false;
    // 3. 根节点元素不同 -> 不同构
    if (T1[rootIndex1].Element != T2[rootIndex2].Element) return false;

    // 4. 尝试“不交换”：左对左，右对右
    bool direct = Isomorphism(T1[rootIndex1].left, T2[rootIndex2].left) && 
                  Isomorphism(T1[rootIndex1].right, T2[rootIndex2].right);
    // 5. 尝试“交换”：左对右，右对左
    bool swapped = Isomorphism(T1[rootIndex1].left, T2[rootIndex2].right) && 
                   Isomorphism(T1[rootIndex1].right, T2[rootIndex2].left);

    return direct || swapped;
}