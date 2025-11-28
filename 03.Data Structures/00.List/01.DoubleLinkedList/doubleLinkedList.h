#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#define SUCCESS 1
#define FAILURE -1

#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;  // 구조체 내부에서는 struct Node* 사용
    struct Node* next;  // 구조체 내부에서는 struct Node* 사용
} Node;

// CREATE
Node*   createNode(int data);

// INIT
int     initHead(Node** head, int data);

// FIND
Node*   findNodeByIndex(Node** head, size_t index);
Node*   findNodeByData(Node** head, int data);

// ADD
int     addNode(Node** head, int data);

// INSERT
int     insertNode(Node** head, size_t index, int data);

// REMOVE
int     removeNode(Node** head, size_t index);
int     removeNodeByData(Node** head, int data);

// PRINT
void    printList(Node** head);
void    printListRevers(Node** head);

// SIZE
size_t  getListSize(Node** head);

// DESTROY
int     destroyList(Node** head);

// EMPTY
int     isEmpty(Node** head);

// UTILS
Node*   getTail(Node** head);

#endif