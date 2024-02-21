#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define PARENT(i) ((i) / 2)
#define MAXN 10000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
int cout;
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode TreeNode;
TreeNode *pPath[MAXN];
TreeNode *qPath[MAXN];
int pSize = 0, qSize = 0;
typedef struct _HashNode {
    void *key;
    int index;
    UT_hash_handle hh;
} HashNode;

TreeNode *findNode(TreeNode *root, int key) {
    if (!root || root->val == key) {
        return root;
    }
    if (root->val > key) {
        return findNode(root->left, key);
    }
    else {
        return findNode(root->right, key);
    }
}
TreeNode *deleteMax(TreeNode *root, int *max) {
    if (root->right == NULL) {
        *max = root->val;
        TreeNode *tmp = root->left;
        free(root);
        return tmp;
    }
    root->right = deleteMax(root->right, max);
    return root;
}
TreeNode* deleteNode(TreeNode* root, int key){
    if (!root) {
        return root;
    }
    if (root->val > key) {
        root->left = deleteNode(root->left, key);
    }
    else if (root->val < key) {
        root->right = deleteNode(root->right, key);
    }
    else if (root->left && root->right) {
        int max;
        root->left = deleteMax(root->left, &max);
        root->val = max;
    }
    else {
        TreeNode *pNode = root;
        if (root->left == NULL)
            root = root->right;
        else
            root = root->left;
        free(pNode);
        
    }
    return root;
}

int kthSmallest(struct TreeNode* root, int k){
    if (!root) {
        return -1;
    }
    int ret = kthSmallest(root->left, k);
    if (ret >= 0) {
        return ret;
    }
    cout++;
    if (cout == k) {
        cout = 0;
        return root->val;
    }
    return kthSmallest(root->right, k);
}
int *preOder(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    TreeNode *stack[MAXN], *pNode = root;
    int *ret, top = -1;
    *returnSize = 0;
    ret = (int*)malloc(sizeof(int) * MAXN);
    while (pNode != NULL || top >= 0) {
        while (pNode) {
            ret[*returnSize] = pNode->val;
            (*returnSize)++;
            stack[++top] = pNode;
            pNode = pNode->left;
        }
        pNode = stack[top--];
        pNode = pNode->right;
    }
    return ret;
}

int *inOrder(TreeNode *root, int *returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    TreeNode *stack[MAXN], *pNode = root;
    int *ret, top = -1;
    *returnSize = 0;
    ret = (int*)malloc(sizeof(int) * MAXN);
    while (pNode != NULL || top >= 0) {
        while (pNode) {
            stack[++top] = pNode;
            pNode = stack[top]->left;
        }
        pNode = stack[top];
        ret[*returnSize] = pNode->val;
        (*returnSize)++;
        top--;
        pNode = pNode->right;
    }
    return ret;
}

TreeNode *TreeConstruct(int *nums, int numsSize) {
    TreeNode **nodeList, *root;
    nodeList = (TreeNode**)malloc(sizeof(TreeNode*) * numsSize);
    nodeList[0] = (TreeNode*)malloc(sizeof(TreeNode));
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] >= 0) {
            nodeList[i] = (TreeNode*)malloc(sizeof(TreeNode));
            nodeList[i]->left = NULL;
            nodeList[i]->right = NULL;
            nodeList[i]->val = nums[i];
            if (i % 2) {
                nodeList[PARENT(i)]->right = nodeList[i];
            }
            else {
                nodeList[PARENT(i)]->left = nodeList[i];
            }
        }
    }
    root = nodeList[0]->right;
    free(nodeList[0]);
    free(nodeList);
    return root;
}
void TreeDestroy(TreeNode *root) {
    if (!root) {
        return ;
    }
    TreeDestroy(root->left);
    TreeDestroy(root->right);
    free(root);
    return ;
}
struct TreeNode* lowestCommonAncestorForBST(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) { //适用于二叉搜索树
    int min = MIN(p->val, q->val);
    int max = MAX(p->val, q->val);
    if (min > root->val) {
        return lowestCommonAncestorForBST(root->right, p, q);
    }
    else if (max < root->val) {
        return lowestCommonAncestorForBST(root->left, p, q);
    }
    return root;
}

bool dfsPath(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (pSize > 0 && qSize > 0 && pPath[pSize - 1] == p && qPath[qSize - 1] == q) {
        return true;
    }
    if (!root) {
        return false;
    }
    if (pSize == 0 || pPath[pSize - 1] != p) {
        pPath[pSize++] = root;
    }
    if (qSize == 0 || qPath[qSize - 1] != q) {
        qPath[qSize++] = root;
    } 
    if (dfsPath(root->left, p, q) || dfsPath(root->right, p, q)) {
        return true;
    }
    if (pPath[pSize - 1] != p) {
        pSize--;
    }
    if (qPath[qSize - 1] != q) {
        qSize--;
    } 
    return false;
}
/** Encodes a tree to a single string. */
// char* serialize(struct TreeNode* root) {
//     int preSize, inSize;
//     int *preArr = preOder(root, &preSize);
//     int *inArr = inOrder(root, &inSize);
//     int seqSize = preSize + inSize + 1;
//     char *retSeque = (char*)malloc(sizeof(int) * seqSize);
//     int *pWrite = (int*)(void*)retSeque;
//     *pWrite = inSize;
//     for (int i = 1; i <= preSize; i++) {
//         pWrite[i] = preArr[i - 1];
//         pWrite[preSize + i] = inArr[i - 1];
//     }
//     return retSeque;
// }
void getSubTreeSize(int *nums, int numsSize, int obj, int *leftSize, int *rightSize) {
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == obj) {
            *leftSize = i;
            *rightSize = numsSize - i - 1;
            return;
        }
    }
    return;
}
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if (preorderSize == 0) {
        return NULL;
    }
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    int leftSize, rightSize;
    root->val = preorder[0];
    getSubTreeSize(inorder, inorderSize, root->val, &leftSize, &rightSize);
    root->left = buildTree(preorder + 1, leftSize, inorder, leftSize);
    root->right = buildTree(preorder + 1 + leftSize, rightSize, inorder + leftSize + 1, rightSize);
    return root;
}
/** Decodes your encoded data to tree. */

// struct TreeNode* deserialize(char* data) {
//     int *preArr, *inArr, preSize, inSize, *pRead;
//     pRead = (int*)(void*)data;
//     preSize = *pRead;
//     inSize = *pRead;
//     preArr = pRead + 1;
//     inArr = pRead + preSize + 1;
//     TreeNode *root =  buildTree(preArr, preSize, inArr, inSize);
//     return root;
// }
typedef enum {
    LEFT,
    RIGHT,
    BUTT
} ChirdType;
typedef struct _BinNode {
    int val;
    int parent;
    int flag;
} BinNode;
HashNode *user = NULL;
void user_add(void *key, int index) {
    HashNode *s = (HashNode*)malloc(sizeof(HashNode));
    s->key = key;
    s->index = index;
    HASH_ADD_PTR(user, key, s);
}
int user_find(void *key) {
    HashNode *s;
    HASH_FIND_PTR(user, &key, s);
    return s->index;
}
void user_del_all() {
    HashNode *p, *tmp;
    HASH_ITER(hh, user, p, tmp) {
        HASH_DEL(user, p);
        free(p);
    }
}
char* serialize(struct TreeNode* root) {
    if (!root) {
        return NULL;
    }
    TreeNode *queue[MAXN], *curNode;
    BinNode tmpArr[MAXN], binNode;
    int tail = 0, head = 0, seqSize, tmpSize = 0;
    char *retSeq;
    queue[0] = root;
    user_add(root, 0);
    binNode.val = root->val;
    binNode.flag = RIGHT;
    binNode.parent = -1;
    tmpArr[tmpSize++] = binNode;
    while (tail >= head) {
        curNode = queue[head];
        if (curNode->left) {
            tmpArr[tmpSize].flag = LEFT;
            tmpArr[tmpSize].val = curNode->left->val;
            tmpArr[tmpSize].parent = user_find(curNode);
            queue[++tail] = curNode->left;
            user_add(curNode->left, tmpSize);
            tmpSize++;
        }
        if (curNode->right) {
            tmpArr[tmpSize].flag = RIGHT;
            tmpArr[tmpSize].val = curNode->right->val;
            tmpArr[tmpSize].parent = user_find(curNode);
            queue[++tail] = curNode->right;
            user_add(curNode->right, tmpSize);
            tmpSize++;
        }
        head++;
    }
    user_del_all();
    retSeq = (char*)malloc(sizeof(BinNode) * tmpSize + sizeof(int));
    *(int*)(void*)retSeq = tmpSize;
    memcpy((void*)(retSeq + sizeof(int)), (void*)tmpArr, sizeof(BinNode) * tmpSize);
    return retSeq;
}

struct TreeNode* deserialize(char* data) {
    int treeSize = *(int*)(void*)data;
    HashNode *s, tmp;
    BinNode *pRead = (BinNode*)(void*)(data + sizeof(int));
    TreeNode *pNode, *pParent;
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = pRead->val;
    root->left = NULL;
    root->right = NULL;
    s = (HashNode*)malloc(sizeof(HashNode));
    s->index = 0;
    s->key = root;
    HASH_ADD_INT(user, index, s);
    for (int i = 1; i < treeSize; i++) {
        pNode = (TreeNode*)malloc(sizeof(TreeNode));
        pNode->val = pRead[i].val;
        pNode->left = NULL;
        pNode->right = NULL;
        s = (HashNode*)malloc(sizeof(HashNode));
        s->index = i;
        s->key = pNode;
        HASH_ADD_INT(user, index, s);
        HASH_FIND_INT(user, &(pRead[i].parent), s);
        pParent = (TreeNode*)s->key;
        if (pRead[i].flag == LEFT) {
            pParent->left = pNode;
        }
        else {
            pParent->right = pNode;
        }
    }
    user_del_all();
    return root;
}
int main() {
    int nums[12] = {0, 1, 2, 3, -1, -1, 4, 5};
    int returnSize = 0, numsSize = 8;
    TreeNode *root = TreeConstruct(nums, numsSize);
    char *data = serialize(root);
    TreeNode *retTree = deserialize(data);
    free(data);
    TreeDestroy(root);
    TreeDestroy(retTree);
    return 0;
}

    // printf("[");
    // for (int i = 0; i < returnSize; i++) {
    //     printf("%d%s", ret[i], i < returnSize - 1 ? ", " : "");
    // }
    // printf("]\n");
    // free(ret);