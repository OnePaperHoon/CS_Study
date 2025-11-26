#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data);
void appendNode(Node** head, int data);
Node *findNode(Node* head, int index);
void insertNodeAtTarget(Node** head, Node* target, int data);
void printList(Node* head);
void removeNode(Node** head, Node* target);
void freeList(Node* head);
void destroyList(Node** head);

#endif