#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//最小堆不是 HuffmanTree，最小堆只是构造 HuffmanTree 的工具。

//构造结束后，最小堆中唯一剩下的那个结点指针，也就是 H->Data[1]，才是 HuffmanTree 的根结点。


#define MINDATA -1  /* 哨兵，应小于所有可能的权值 */

/* 哈夫曼树结点定义 */
typedef struct TreeNode *HuffmanTree;

struct TreeNode {
    int Weight;
    HuffmanTree Left;
    HuffmanTree Right;
};

/* 堆中存放的是 HuffmanTree，也就是 struct TreeNode* */
typedef HuffmanTree ElementType;

/* 最小堆定义 */
typedef struct HNode *MinHeap;

struct HNode {
    ElementType *Data;  /* Data 是 HuffmanTree 指针数组 */
    int Size;           /* 当前元素个数 */
    int Capacity;       /* 最大容量 */
};

/* 创建一个空的最小堆 */
MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));

    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;

    /* 创建哨兵结点 */
    H->Data[0] = (HuffmanTree)malloc(sizeof(struct TreeNode));
    H->Data[0]->Weight = MINDATA;
    H->Data[0]->Left = NULL;
    H->Data[0]->Right = NULL;

    return H;
}

/* 判断最小堆是否满 */
bool IsFull(MinHeap H)
{
    return H->Size == H->Capacity;
}

/* 判断最小堆是否为空 */
bool IsEmpty(MinHeap H)
{
    return H->Size == 0;
}

/* 创建一个哈夫曼树结点 */
HuffmanTree CreateTreeNode(int Weight)
{
    HuffmanTree T = (HuffmanTree)malloc(sizeof(struct TreeNode));

    T->Weight = Weight;
    T->Left = NULL;
    T->Right = NULL;

    return T;
}

/* 插入一个哈夫曼树结点到最小堆 */
bool Insert(MinHeap H, ElementType X)
{
    int i;

    if (IsFull(H)) {
        printf("最小堆已满\n");
        return false;
    }

    i = ++H->Size;

    /*
        最小堆上滤：
        如果父结点权值 > X 的权值，就把父结点往下移
    */
    for (; H->Data[i / 2]->Weight > X->Weight; i /= 2) {
        H->Data[i] = H->Data[i / 2];
    }

    H->Data[i] = X;

    return true;
}

/* 删除并返回最小堆中的最小元素 */
ElementType DeleteMin(MinHeap H)
{
    int Parent, Child;
    ElementType MinItem, X;

    if (IsEmpty(H)) {
        printf("最小堆已为空\n");
        return NULL;
    }

    /* 最小元素在根结点 */
    MinItem = H->Data[1];

    /*
        用最后一个元素 X 从根开始向下过滤
    */
    X = H->Data[H->Size--];

    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;

        /*
            Child 指向左右孩子中权值较小的那个
        */
        if ((Child != H->Size) &&
            (H->Data[Child]->Weight > H->Data[Child + 1]->Weight)) {
            Child++;
        }

        /*
            如果 X 比两个孩子都小或相等，位置合适
        */
        if (X->Weight <= H->Data[Child]->Weight) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }

    H->Data[Parent] = X;

    return MinItem;
}

/* 下滤：把以 H->Data[p] 为根的子堆调整为最小堆 */
void PercDown(MinHeap H, int p)
{
    int Parent, Child;
    ElementType X;

    X = H->Data[p];

    for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;

        /*
            Child 指向左右孩子中较小者
        */
        if ((Child != H->Size) &&
            (H->Data[Child]->Weight > H->Data[Child + 1]->Weight)) {
            Child++;
        }

        if (X->Weight <= H->Data[Child]->Weight) {
            break;
        } else {
            H->Data[Parent] = H->Data[Child];
        }
    }

    H->Data[Parent] = X;
}

/* 建造最小堆 */
void BuildMinHeap(MinHeap H)
{
    int i;

    /*
        从最后一个非叶子结点开始，向前逐个下滤
    */
    for (i = H->Size / 2; i > 0; i--) {
        PercDown(H, i);
    }
}

/* 构建哈夫曼树 */
HuffmanTree Huffman(MinHeap H)
{
    HuffmanTree T;

    BuildMinHeap(H);

    /*
        只要堆里还有至少两棵树，就合并
    */
    while (H->Size > 1) {
        T = (HuffmanTree)malloc(sizeof(struct TreeNode));

        /*
            取出两个权值最小的树，作为左右子树
        */
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);

        /*
            新根结点权值 = 左右子树权值之和
        */
        T->Weight = T->Left->Weight + T->Right->Weight;

        /*
            把新生成的子树重新插回最小堆
        */
        Insert(H, T);
    }

    /*
        最后堆里只剩一棵树，就是完整哈夫曼树
    */
    T = DeleteMin(H);

    return T;
}

/* 先序遍历哈夫曼树，用来测试 */
void PreOrderTraversal(HuffmanTree T)
{
    if (T == NULL) {
        return;
    }

    printf("%d ", T->Weight);
    PreOrderTraversal(T->Left);
    PreOrderTraversal(T->Right);
}

/* 释放哈夫曼树 */
void FreeHuffmanTree(HuffmanTree T)
{
    if (T == NULL) {
        return;
    }

    FreeHuffmanTree(T->Left);
    FreeHuffmanTree(T->Right);
    free(T);
}

int main()
{
    int weights[] = {5, 7, 10, 15, 20, 45};
    int n = sizeof(weights) / sizeof(weights[0]);

    MinHeap H = CreateHeap(n);

    /*
        先把每个权值变成一个单结点树，放进堆里
    */
    for (int i = 0; i < n; i++) {
        H->Data[++H->Size] = CreateTreeNode(weights[i]);
    }

    /*
        构建哈夫曼树
    */
    HuffmanTree HT = Huffman(H);

    printf("哈夫曼树先序遍历结果：");
    PreOrderTraversal(HT);
    printf("\n");

    FreeHuffmanTree(HT);

    /*
        释放堆
    */
    free(H->Data[0]);
    free(H->Data);
    free(H);

    return 0;
}