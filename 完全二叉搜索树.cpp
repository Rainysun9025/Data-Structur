#include <stdio.h>
#include <stdlib.h>

// 对完全二叉树进行中序遍历，并依次填入排序后的数字
// root: 当前节点下标
// n: 节点总数
// sorted: 已排序的输入数组
// tree: 存储完全二叉树的层序数组
// idx: 指向下一个待填入数字在 sorted 中的位置
void inorderFill(int root, int n, int sorted[], int tree[], int *idx) {
    if (root >= n) return;                   // 空节点，返回
    inorderFill(2 * root + 1, n, sorted, tree, idx); // 左子树
    tree[root] = sorted[(*idx)++];           // 填入根节点，并后移指针
    inorderFill(2 * root + 2, n, sorted, tree, idx); // 右子树
}

// 用于 qsort 的比较函数（升序）
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    scanf("%d", &n);

    // 分配并读取输入数组
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 排序，得到 BST 所需的中序序列
    qsort(arr, n, sizeof(int), cmp);

    // 分配存储完全二叉树的层序数组
    int *tree = (int*)malloc(n * sizeof(int));

    int idx = 0;  // 初始指向排序数组的第一个元素
    inorderFill(0, n, arr, tree, &idx);

    // 输出层序遍历结果（即 tree 数组本身）
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", tree[i]);
    }
    printf("\n");

    // 释放内存
    free(arr);
    free(tree);

    return 0;
}