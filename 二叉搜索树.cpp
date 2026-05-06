#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElementType int
struct TreeNode{
    ElementType Element;
        struct TreeNode* left;
    struct TreeNode* right;
};



struct TreeNode* Search(struct TreeNode* root,ElementType x)
{
    if(root==NULL){
        return NULL;
    }


    //基于递归的实现，但是可能有栈溢出的风险，尤其是在搜索树退化为链表的时候
    /*if(x>root->Element){
        return Search(root->right,x);
    }
    else if(x<root->Element){
        return Search(root->left,x);
    }
    else{
        return root;
    }*/


   //基于迭代的实现 
   while(root!=NULL)
    {
        if(x>root->Element){
            root=root->right;
        }
        else if(x<root->Element){
            root=root->left;
        }
        else{
            break;
        }
    }
    return root;

}


ElementType SearchMin(struct TreeNode* root)
{
    if(root==NULL){
        printf("空树,没有最小值\n");
        return NULL;
    }
    while(root->left!=NULL){
        root=root->left;
    }
    return root->Element;
}


ElementType SearchMax(struct TreeNode* root)
{
    if(root==NULL){
        printf("空树,没有最大值\n");
        return NULL;
    }
    while(root->right!=NULL){
        root=root->right;
    }
    return root->Element;
}


struct TreeNode* Insert(struct TreeNode* root,ElementType x)
{
    if(root==NULL){
        root=(struct TreeNode* )malloc( sizeof(struct TreeNode) );
        if(root==NULL){
            printf("系统内存不足,无法malloc\n");
            return NULL;
        }
        root->Element=x;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    while(1){
        if(x>root->Element){
            if(root->right==NULL) break;
            root=root->right;
        }
        else if(x<root->Element){
            if(root->left==NULL) break;
            root=root->left;
        }
        else if(x==root->Element){
            printf("二叉搜索树已经存在了这个元素，禁止插入相同元素\n");
            return NULL;
        }
    }
    struct TreeNode* newnode=(struct TreeNode *)malloc( sizeof(struct TreeNode) );
    if(newnode==NULL){
        printf("系统内存不足,无法malloc\n");
        return NULL;
    }
    if(x>root->Element){
        newnode->Element=x;
        newnode->left=NULL;
        newnode->right=NULL;
        root->right=newnode;
        return root->right;
    }
    else if(x<root->Element){
        newnode->Element=x;
        newnode->left=NULL;
        newnode->right=NULL;
        root->left=newnode;
        return root->left;
    }
}


struct TreeNode* Delete(struct TreeNode* root,ElementType x)
{
    struct TreeNode* reallyroot=root;
    //struct TreeNode* Search(struct TreeNode* root,ElementType x)
    struct TreeNode* last=NULL;
    struct TreeNode* cur=NULL;
    struct TreeNode* next=NULL;
    while(1){
        if(x>root->Element){
            last=root;
            if(root->right==NULL){
                printf("二叉搜索树不存在该元素,无法删除\n");
                return reallyroot;
            }
            root=root->right;
        }
        else if(x<root->Element){
            last=root;
            if(root->left==NULL){
                printf("二叉搜索树不存在该元素,无法删除\n");
                return reallyroot;
            }
            root=root->left;
        }
        else if(x==root->Element){
            cur=root;
            break;
        }
    }
    if(cur->left==NULL&&cur->right==NULL){
        if(last==NULL){
            //说明要删除的是根节点，并且根节点没有左右子树
            free(root);
            return NULL;
        }
        if(cur->Element>last->Element){
            //在右子树
            last->right=NULL;
            free(cur);
        }
        else if(cur->Element<last->Element){
            //在左子树
            last->left=NULL;
            free(cur);
        }
        return reallyroot;
    }
    else if(cur->left==NULL||cur->right==NULL){
        
        if(cur->left==NULL){
            next=cur->right;
        }
        else if(cur->right==NULL){
            next=cur->left;
        }
        if(last==NULL){
            if(root->left==NULL){
                root=root->right;
                free(cur);
                return root;
            }
            else{
                root=root->left;
                free(cur);
                return root;
            }
        }
        if(cur->Element>last->Element){
            //在右子树
            last->right=next;
            free(cur);
        }
        else if(cur->Element<last->Element){
            //在左子树
            last->left=next;
            free(cur);
        }
        return reallyroot;
    }
    else if(cur->left!=NULL&&cur->right!=NULL){
        //要找到左子树的最大值，或者右子树的最小值，然后替换cur
        //这里来找左子树的最大值
        next=cur->left;
        if(next->right==NULL){
            cur->Element=next->Element;
            if(next->left==NULL){
                cur->left=NULL;
                free(next);
                return reallyroot;
            }
            else{
                cur->left=next->left;
                free(next);
                return reallyroot;
            }
        }

        struct TreeNode* Llast=cur;
        while(1){

            if(next->right==NULL) break;
            Llast=next;
            next=next->right;
        }
        if(next->left==NULL){
            cur->Element=next->Element;
            Llast->right=NULL;
            free(next);
            return reallyroot;
        }
        else{
            cur->Element=next->Element;
            Llast->right=next->left;
            free(next);
            return reallyroot;
        }
    }

}
