#include <stdio.h>
#include <stdlib.h>

/* 节点类型 */
typedef enum { ATOM, LIST } NodeType;
//ATOM（0）：原子
//LIST（1）：子表

/* 广义表节点结构 */
typedef struct GNode {
    NodeType tag;//用于标记这是原子结构还是子表结构
    union {
        int atom;           /* 原子值 */
        struct GNode *list; /* 子表的头节点指针 */
    } data;
    struct GNode *next;     /* 指向同一层的下一个节点 */
} GNode;

/* 创建一个原子节点 */
GNode* createAtom(int val) {
    GNode *p = (GNode*)malloc(sizeof(GNode));
    p->tag = ATOM;
    p->data.atom = val;
    p->next = NULL;
    return p;
}

/* 创建一个子表节点（list 参数指向子表的第一个节点） */
GNode* createList(GNode *listHead) {
    GNode *p = (GNode*)malloc(sizeof(GNode));
    p->tag = LIST;
    p->data.list = listHead;
    p->next = NULL;
    return p;
}

/* 在广义表（节点链）末尾添加一个新节点 */
void append(GNode **head, GNode *newNode) {
    //head 指向指针的指针
    if (*head == NULL) {
        //头节点为空的情况
        *head = newNode;
    } else {
        GNode *p = *head;
        while (p->next) p = p->next;//直到p->next==NULL才停下来，意味着找到了尾巴
        p->next = newNode;
    }
}

/* 打印广义表 */
void printGList(GNode *l) {
    if (l == NULL) {
        printf("()");   /* 空表 */
        return;
    }
    printf("(");
    GNode *p = l;
    while (p) {
        if (p->tag == ATOM) {
            printf("%d", p->data.atom);
        } else {  /* LIST */
            printGList(p->data.list);//递归调用来打印子表
        }
        p = p->next;
        if (p) printf(", ");
    }
    printf(")");
}

/* 求广义表的深度
   空表深度 = 1
   原子深度 = 0
   表的深度 = 1 + 所有子表元素深度的最大值
*/
int depth(GNode *l) {
    if (l == NULL) return 1;          /* 空表深度为1 */
    if (l->tag == ATOM) return 0;     /* 原子深度为0 */
    /* l 是子表节点，计算该子表内所有元素的深度最大值 */
    int maxSubDepth = 0;
    GNode *p = l->data.list;          /* 指向子表的第一个元素 */
    while (p) {
        int d;
        if (p->tag == ATOM)
            d = 0;
        else
            d = depth(p->data.list);  /* 递归求子表深度 */
        if (d > maxSubDepth) maxSubDepth = d;
        p = p->next;
    }
    return maxSubDepth + 1;           /* 本层深度加1 */
}

/* 复制广义表 */
GNode* copyGList(GNode *l) {
    if (l == NULL) return NULL;
    GNode *newNode = (GNode*)malloc(sizeof(GNode));
    newNode->tag = l->tag;
    newNode->next = copyGList(l->next);   /* 复制兄弟节点链 */
    if (l->tag == ATOM) {
        newNode->data.atom = l->data.atom;
    } else {
        newNode->data.list = copyGList(l->data.list);
    }
    return newNode;
}

/* 销毁广义表（释放所有节点） */
void destroyGList(GNode *l) {
    if (l == NULL) return;
    /* 先递归销毁子表，再释放兄弟节点 */
    if (l->tag == LIST && l->data.list != NULL) {
        destroyGList(l->data.list);
    }
    destroyGList(l->next);   /* 释放同层后续节点 */
    free(l);
}

/* 示例：构建广义表 L = (a, (b, c), d) 其中 a=1, b=2, c=3, d=4 */
int main() {
    /* 构建子表 (b, c) : b=2, c=3 */
    GNode *subList = NULL;
    append(&subList, createAtom(2));
    append(&subList, createAtom(3));
    GNode *subNode = createList(subList);   /* 子表节点 */

    /* 构建主表 (a, (b,c), d) */
    GNode *mainList = NULL;
    append(&mainList, createAtom(1));       /* a=1 */
    append(&mainList, subNode);              /* 子表 */
    append(&mainList, createAtom(4));       /* d=4 */

    printf("广义表: ");
    printGList(mainList);
    printf("\n");

    printf("深度: %d\n", depth(mainList));

    /* 测试复制 */
    GNode *copyList = copyGList(mainList);
    printf("复制后的广义表: ");
    printGList(copyList);
    printf("\n");

    /* 测试销毁 */
    destroyGList(mainList);
    destroyGList(copyList);

    return 0;
}