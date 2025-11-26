#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE -1

typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data);
int appendNode(Node** head, int data);
Node *findNode(Node* head, size_t index);
int insertNodeAtTarget(Node** head, Node* target, int data);
void printList(Node* head);
int removeNode(Node** head, Node* target);
void freeList(Node* head);
void destroyList(Node** head);

#endif