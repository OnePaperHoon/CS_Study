#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct BSTNode {
    int key;
    void* value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BST {
    BSTNode* root;
} BST;

BST* createBST();
BSTNode* createBSTNode(int key, void* value);

// 재귀 삽입
BSTNode* insertBST(BST* tree, BSTNode* node);

// 검색
void* searchBST(BST* tree, int key);

// 삭제
void freeBSTNode(BSTNode* root);


#endif // BST_H