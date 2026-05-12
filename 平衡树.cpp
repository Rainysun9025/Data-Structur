#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

int max(int a, int b) {
    return a > b ? a : b;
}

int height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

//LL
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度，先更新下面的 y，再更新新的根 x
    updateHeight(y);
    updateHeight(x);

    return x;

/*      y          
       /
      x
     / \
    T1  T2  
                                      
        x
       / \
      T1  y
         /
        T2             */ 
}

//RR
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度，先更新下面的 x，再更新新的根 y
    updateHeight(x);
    updateHeight(y);

    return y;


    /*
        x
       / \
      T1  y
         / \
        T2  T3
    
        y
       / \
      x   T3
     / \
    T1  T2

    */
}
// AVL 插入
AVLNode* insert(AVLNode* root, int key) {
    // 1. 先按普通 BST 插入
    if (root == NULL)
        return newNode(key);
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        // 不插入重复值
        return root;
    }
    // 2. 更新高度
    updateHeight(root);
    // 3. 计算平衡因子
    int balance = getBalance(root);
    // 4. LL 型：左左
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    // 5. RR 型：右右
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    // 6. LR 型：左子树的右边高
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // 7. RL 型：右子树的左边高
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}