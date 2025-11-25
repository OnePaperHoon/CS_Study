#ifndef ARRAY_BASED_LINEAR_QUEUE_H
#define ARRAY_BASED_LINEAR_QUEUE_H


#define MAX_QUEUE_SIZE 5

#include <stdio.h>

typedef int ElementType;

typedef struct {
	ElementType data[MAX_QUEUE_SIZE]; // 큐의 데이터 저장을 위한 배열
	int front; // 머리 인덱스
	int rear; // 꼬리 인덱스
} ArrayBasedLinearQueue;

// 함수 선언

// 큐 초기화
void initQueue(ArrayBasedLinearQueue* queue);

// 큐가 가득 찼는지 확인
int isQueueFull(const ArrayBasedLinearQueue* queue);

// 큐가 비어있는지 확인
int isQueueEmpty(const ArrayBasedLinearQueue* queue);

// 아이템을 큐에 추가
int enqueue(ArrayBasedLinearQueue* queue, ElementType item);

// 아이템을 큐에서 제거
int dequeue(ArrayBasedLinearQueue* queue, ElementType* item);

// 큐의 현재 상태를 출력
void displayQueue(const ArrayBasedLinearQueue* queue);

#endif