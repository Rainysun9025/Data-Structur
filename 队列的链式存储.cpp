#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int
#define ERROR false

struct Node {
    ElementType Data;
    struct Node *Next;
};

struct QNode {
    struct Node *Front;   // 队列的头指针
    struct Node *Rear;    // 队列的尾指针
};

bool IsEmpty(struct QNode *Q) {
    return (Q->Front == NULL);
}

ElementType DeleteQ(struct QNode *Q) {
    struct Node *FrontCell;
    ElementType FrontElem;

    if (IsEmpty(Q)) {
        printf("队列空");
        return ERROR;
    } else {
        FrontCell = Q->Front;
        if (Q->Front == Q->Rear)   // 若队列只有一个元素
            Q->Front = Q->Rear = NULL; // 删除后队列置为空
        else
            Q->Front = Q->Front->Next;
        FrontElem = FrontCell->Data;

        free(FrontCell);   // 释放被删除结点空间
        return FrontElem;
    }
}

bool AddQ(struct QNode *Q, ElementType X) {
    struct Node *NewNode = (struct Node *)malloc(sizeof(struct Node));
    if (NewNode == NULL) {
        printf("内存不足\n");
        return false;
    }
    NewNode->Data = X;
    NewNode->Next = NULL;

    // 如果队列为空，则头尾都指向新结点
    if (IsEmpty(Q)) {
        Q->Front = Q->Rear = NewNode;
    } else {
        Q->Rear->Next = NewNode;   // 原队尾的next指向新结点
        Q->Rear = NewNode;         // 更新队尾指针
    }
    return true;
}