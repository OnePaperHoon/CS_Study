#include "BST.h"

BST* createBST()
{
    BST* tree = (BST*)malloc(sizeof(BST));
    if (!tree)
        return NULL;
    tree->root = NULL;
    return tree;
}

BSTNode* createBSTNode(int key, void* value)
{
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    if (!newNode)
        return NULL;
    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 재귀 삽입 보조 함수
BSTNode* insertNodeRecursive(BSTNode* currentNode, BSTNode* newNode)
{
    // Base case: 빈 위치를 찾으면 새 노드 삽입
    if (currentNode == NULL)
        return newNode;

    // Recursive case: 키 값 비교
    if (newNode->key < currentNode->key)
    {
        // 왼쪽 서브트리로 재귀
        currentNode->left = insertNodeRecursive(currentNode->left, newNode);
    }
    else if (newNode->key > currentNode->key)
    {
        // 오른쪽 서브트리로 재귀
        currentNode->right = insertNodeRecursive(currentNode->right, newNode);
    }
    // 같은 키가 이미 존재하면 삽입하지 않음 (중복 방지)

    return currentNode;
}

// 재귀 삽입 함수
BSTNode* insertBST(BST* tree, BSTNode* node)
{
    if (!tree || !node)
        return NULL;

    // 트리가 비어있으면 루트로 설정
    if (tree->root == NULL)
    {
        tree->root = node;
        return node;
    }

    // 재귀 함수 호출
    insertNodeRecursive(tree->root, node);
    return node;
}