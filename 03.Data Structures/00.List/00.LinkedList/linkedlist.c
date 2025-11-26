#include "linkedlist.h"

/**
 * 새로운 노드를 생성합니다.
 * @param data 새 노드에 저장할 데이터
 * @return 생성된 노드의 포인터 또는 NULL (메모리 할당 실패 시)
*/
Node* createNode(int data)
{
	// 메모리 할당
	Node *newNode = (Node*)malloc(sizeof(Node));

	// 할당 성공 여부 확인
	if (!newNode)
		return NULL;
	
	// 노드 최기화
	newNode->data = data;
	newNode->next = NULL;

	// 생성된 노드 반환
	return newNode;
}

/**
 * 새로운 노드를 생성하고, 리스트의 끝에 추가합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param data 새 노드에 저장할 데이터
*/
void appendNode(Node** head, int data)
{
	// 새로운 노드 생성
	Node* newNode = createNode(data);

	// 메모리 할상 성공 여부 확인
	if (!newNode)
	{
		// 에러 메시지 출력
		printf("Memory allocation failed\n");
		return;
	}

	// 리스트가 비어있는 경우
	if (*head == NULL)
	{
		// 새 노드를 헤드로 설정
		*head = newNode;
		return;
	}

	// 리스트의 끝으로 이동
	Node* temp = *head;

	// 시간 복잡도 O(n)
	while (temp->next != NULL)
		temp = temp->next;

	// 새 노드를 리스트의 끝에 추가
	temp->next = newNode;
}

/**
 * 인덱스에 해당하는 노드를 찾습니다.
 * @param head 리스트의 헤드 노드 포인터
 * @param index 찾고자 하는 노드의 인덱스 (0부터 시작)
 * @return 인덱스에 해당하는 노드의 포인터, 없으면 NULL
*/
Node* findNode(Node* head, int index)
{
	// 임시 포인터와 현재 인덱스 초기화
	Node* temp = head;
	int currentIndex = 0;

	// 리스트를 순회 하며 인덱스 찾기 시간 복잡도 O(n)
	while (temp != NULL)
	{
		// 현재 인덱스가 찾고자 하는 인덱스와 일치하는지 확인
		if (currentIndex == index)
			return temp;

		// 다음 노드로 이동 및 인덱스 증가
		temp = temp->next;
		currentIndex++;
	}

	// 인덱스에 해당하는 노드가 없으면 NULL 반환
	return NULL;
}

/**
 * 새로운 노드를 생성하고, 타겟 노드 뒤에 삽입합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param target 타겟 노드의 주소
 * @param data 새 노드에 저장할 데이터
*/
void insertNodeAtTarget(Node** head, Node* target, int data)
{
	Node* newNode = createNode(data);

	if (!newNode)
	{
		printf("Memory allocation failed\n");
		return;
	}

	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

	Node* temp = *head;

	while (temp != NULL)
	{
		if (temp == target)
		{
			newNode->next = temp->next;
			temp->next = newNode;
			return;
		}
		temp = temp->next;
	}
}

/**
 * 리스트의 모든 노드를 출력합니다.
 * @param head 리스트의 헤드 노드 포인터
*/
void printList(Node* head)
{
	Node* temp = head;
	int index = 0;

	while (temp != NULL)
	{
		printf("[%d] : %d -> ", index, temp->data);
		temp = temp->next;
		index++;
	}
	if (temp == NULL)
		printf("NULL\n");
}

/**
 * 타겟 노드를 리스트에서 제거합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param target 타겟 노드의 주소
*/
void removeNode(Node** head, Node* target)
{
	if (head == NULL || *head == NULL || target == NULL)
		return;
	
	Node* temp = *head;

	if (temp == target)
	{
		*head = temp->next;
		free(temp);
		return;
	}

	while (temp->next != NULL)
	{
		if (temp->next == target)
		{
			Node* nodeToDelete = temp->next;
			temp->next = nodeToDelete->next;
			free(nodeToDelete);
			return;
		}
		temp = temp->next;
	}
}

/**
 * 리스트의 모든 노드를 해제합니다.
 * @param head 리스트의 헤드 노드 포인터
*/
void freeList(Node* head)
{
	Node* temp = NULL;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

/**
 * 리스트를 해제하고 헤드 포인터를 NULL로 설정합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
*/
void destroyList(Node** head)
{
	if (head == NULL || *head == NULL)
		return;

	freeList(*head);
	*head = NULL;
}