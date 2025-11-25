#include "ArrayBasedLinearQueue.h"

// 큐 초기화
void initQueue(ArrayBasedLinearQueue* queue) {
	queue->front = 0;
	queue->rear = 0;
}

// 큐가 가득 찼는지 확인
/**
 * @param queue 큐에 대한 포인터
 * @return 가득 찼으면 1, 아니면 0 반환
*/
int isQueueFull(const ArrayBasedLinearQueue* queue) {
	return queue->rear == MAX_QUEUE_SIZE;
}

// 큐가 비었는지 확인
/**
 * @param queue 큐에 대한 포인터
 * @return 비어있으면 1, 아니면 0 반환
*/
int isQueueEmpty(const ArrayBasedLinearQueue* queue) {
	return queue->front == queue->rear;
}

// 아이템을 큐에 추가
int enqueue(ArrayBasedLinearQueue* queue, ElementType item) {
	
	// 1. 큐가 가득 찼는지 확인
	if (isQueueFull(queue)) {
		// 2. 가득 찼다면, 에러 코드 반환
		return -1;
	}
	// 3. reqr 위치에 아이템 추가
	queue->data[queue->rear] = item;
	// 4. reqr 인덱스 증가
	queue->rear++;
	// 5. 성공 코드 반환
	return 0;
}

// 아이템을 큐에서 제거
/**
 * @param queue 큐에 대한 포인터
 * @param item 제거된 아이템을 저장할 포인터
 * @return 성공 시 0, 실패 시 -1 반환
*/
int dequeue(ArrayBasedLinearQueue* queue, ElementType* item) {
	// 1. 큐가 비어있는지 확인
	if (isQueueEmpty(queue)) {
		// 2. 비어있다면 에러 코드 반환
		return -1;
	}
	// 3. front 위치의 아이템을 item에 복사
	*item = queue->data[queue->front];
	// 4. front 인덱스 증가
	queue->front++;
	// 5. 성공 코드 반환
	return 0;
}

// 큐의 현재 상태를 출력
void displayQueue(const ArrayBasedLinearQueue* queue) {
	printf("Queue: ");
	for (int i = queue->front; i < queue->rear; i++) {
		printf("%d ", queue->data[i]);
	}
}