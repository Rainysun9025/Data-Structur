#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int

typedef struct QNode {
    ElementType *Data;
    int front, rear;
    int cursize;
    int Maxsize;
} Deque;

Deque* CreateQueue(int Max) {
    Deque *Q = (Deque*)malloc(sizeof(Deque));
    Q->Data = (ElementType*)malloc(sizeof(ElementType) * Max);
    Q->front = 0;//front指向当前队头元素的位置
    Q->rear = 0;//rear指向下一个可插入的位置（即队尾元素的下一个空位）
    Q->cursize = 0;
    Q->Maxsize = Max;
    return Q;
}

bool IsFull(Deque *Q) {
    return Q->cursize == Q->Maxsize;
}

bool IsEmpty(Deque *Q) {
    return Q->cursize == 0;
}

// tag = 1: 队尾插入; tag = 0: 队头插入
bool AddQ(Deque *Q, int tag, ElementType value) {
    if (IsFull(Q)) {
        printf("队列已满\n");
        return false;
    }
    if (tag == 1) {          // 队尾插入
        Q->Data[Q->rear] = value;
        Q->rear = (Q->rear + 1) % Q->Maxsize;
    } else {                 // 队头插入
        Q->front = (Q->front - 1 + Q->Maxsize) % Q->Maxsize;
        Q->Data[Q->front] = value;
    }
    Q->cursize++;
    return true;
    //队尾插入先赋值再移动
    //队头插入先移动再赋值
}

// tag = 1: 删除队尾; tag = 0: 删除队头
ElementType DeleteQ(Deque *Q, int tag) {
    if (IsEmpty(Q)) {
        printf("队列为空\n");
        return (ElementType)0;   // 简单处理，实际可改用传址方式
    }
    ElementType value;
    if (tag == 1) {          // 删除队尾
        Q->rear = (Q->rear - 1 + Q->Maxsize) % Q->Maxsize;
        value = Q->Data[Q->rear];
    } else {                 // 删除队头
        value = Q->Data[Q->front];
        Q->front = (Q->front + 1) % Q->Maxsize;
    }
    Q->cursize--;
    return value;
}