#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int
//CreateDeque
//IsEmpty
//AddQ
//DeleteQ
struct Node{
    ElementType value;
    struct Node* last;
    struct Node* next;
    //由元素和指向下一个结构体的指针和指向上一个结构体的指针构成
    //可以理解为队列的元素
};


struct QNode{
    struct Node* front;//front指向上一个可插入的位置（即队头元素的上一个空位）
    struct Node* rear;//rear指向下一个可插入的位置（即队尾元素的下一个空位）
    //该队列的头和尾
};


struct QNode* CreatDeque()
{
    struct QNode* Q=(struct QNode* )malloc(sizeof(struct QNode));
    if(Q==NULL)
    {
        printf("内存不足\n");
        return NULL;
    }
    Q->front=(struct Node*)malloc(sizeof(struct Node));
    if (Q->front == NULL) {
    printf("内存不足\n");
    free(Q);
    return NULL;
    }
    Q->rear=(struct Node* )malloc(sizeof(struct Node));
    if (Q->rear == NULL) {
        printf("内存不足\n");
        free(Q->front);
        free(Q);
        return NULL;
    }
    Q->front->next=Q->rear;
    Q->front->last=NULL;
    Q->rear->last=Q->front;
    Q->rear->next=NULL;
    return Q;
}

bool IsEmpty(struct QNode* Q)
{
    if(Q->front->next==Q->rear) return true;
    else return false;

}

bool AddQ(struct QNode* Q,ElementType val,int tag)//tag=1代表插在头，=0代表插在尾
{
    struct Node* NewQ=(struct Node* )malloc(sizeof(struct Node));
    if(NewQ==NULL)
    {
        printf("内存已满\n");
        return false;
    }
    NewQ->value=val;
    if(IsEmpty(Q))
    {
        //当没有元素的时候
        Q->front->next=NewQ;
        Q->rear->last=NewQ;
        NewQ->last=Q->front;
        NewQ->next=Q->rear;
    }
    else if(tag==1)
    {
        NewQ->next=Q->front->next;//新元素的下一个节点是原头节点的下一个元素(更新新元素的下一个节点)
        Q->front->next->last=NewQ;//原头节点的下一个元素的上一个元素应该是新元素
        Q->front->next=NewQ;//更新头节点，使其下一个节点是新元素
        NewQ->last=Q->front;//更新新元素的上一个节点
    }
    else if(tag==0)
    {
        NewQ->last=Q->rear->last;//新元素的上一个节点是原尾节点的上一个元素(更新新元素的上一个节点)
        Q->rear->last->next=NewQ;//原尾节点的上一个元素的下一个元素应该是新元素
        Q->rear->last=NewQ;//更新尾节点。使其上一个节点是新元素
        NewQ->next=Q->rear;//更新新节点的下一个元素
    }
    return true;
}

ElementType DeleteQ(struct QNode* Q,int tag)
{
    if(IsEmpty(Q))
    {
        printf("双端队列是空的\n");
        return false;
    }
    ElementType val;
    struct Node* Elem;

    if(tag==1)
    {
        val=Q->front->next->value;//提取值
        Elem=Q->front->next;//要被删除的元素，即头节点的下一个元素
        Elem->next->last=Q->front;//被删除元素的下一个节点的上一个节点更新为头节点
        Q->front->next=Elem->next;//头节点的下一个节点更新为被删除元素的下一个节点
    }

    else if(tag==0)
    {
        val=Q->rear->last->value;//提取值
        Elem=Q->rear->last;//需要释放的节点
        Elem->last->next=Q->rear;//被删除元素的上一个节点的下一个节点更新为尾节点
        Q->rear->last=Elem->last;//尾节点的上一个节点更新为被删除元素的上一个节点
    }
    free(Elem);
    return val;
} 