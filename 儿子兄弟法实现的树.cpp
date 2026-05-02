#include <stdio.h>
typedef struct CSNode *CSTree;   // 树类型
#define ElementType int
struct CSNode {
    ElementType Data;            // 结点数据
    CSTree FirstChild;           // 指向第一个孩子（左孩子）
    CSTree NextSibling;          // 指向下一个兄弟（右兄弟）
};