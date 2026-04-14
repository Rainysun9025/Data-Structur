#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int Position;
#define  ElementType int
typedef int Position;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = 0;
    Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

bool IsFull( Queue Q )
{
    //这种循环队列是少用了一个位置
    //也就是说，当队列头尾相等时，队列为空
    //队列头尾差1时，队列为满
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
    //返回1——满
    //返回0——空
}

bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

ElementType DeleteQ(Queue Q) {
    if (IsEmpty(Q)) {
        printf("队列空");
        return false;
    }
    else {
        ElementType val = Q->Data[Q->Front];          // 先取出队头
        Q->Front = (Q->Front + 1) % Q->MaxSize;       // 再移动指针
        return val;                                   // 返回取出的值
    }
}