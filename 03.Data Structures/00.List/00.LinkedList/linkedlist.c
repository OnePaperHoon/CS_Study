#include "linkedlist.h"

/***
 * 리뷰(시니어 관점): 파일 전체 코멘트
 * - 잘된 점: 함수들이 작고 역할이 분리되어 있으며, freeList/destroyList에서 메모리를 해제하고 있어 메모리 관리가 비교적 잘 되어 있음.
 * - 개선 권장 사항:
 *   1) 인덱스/크기 값에는 일관된 타입을 사용하세요. 가능한 경우 size_t를 사용해 범위와 의미를 명확히 하십시오.
 *   2) append/insert/remove 같은 변경(mutating) 함수는 호출자가 실패를 처리할 수 있도록 상태 코드(int)를 반환하도록 설계하는 것이 좋습니다.
 *   3) C에서 malloc의 반환값을 캐스팅하지 마세요. (stdlib.h가 포함되어 있다면 캐스트 불필요) 캐스팅은 오래된 컴파일러에서 프로토타입 누락을 숨길 수 있습니다.
 *   4) 입력 검증(assert)와 소유권(누가 Node*를 해제하는지) 문서를 보강하세요.
 *   5) append 성능을 O(1)로 만들기 위해 tail 포인터(또는 리스트 래퍼 구조체)를 유지하는 것을 고려하거나, 현재 구현이 O(n)임을 문서화하세요.
 */

/**
 * 새로운 노드를 생성합니다.
 * @param data 새 노드에 저장할 데이터
 * @return 생성된 노드의 포인터 또는 NULL (메모리 할당 실패 시)
*/
Node* createNode(int data)
{
	// 메모리 할당
	Node *newNode = calloc(1, sizeof(Node));
	// 할당 성공 여부 확인
	if (!newNode)
		return NULL;
	
	// 노드 초기화
	newNode->data = data;
	newNode->next = NULL;

	// 생성된 노드 반환
	return newNode;
}

/**
 * 새로운 노드를 생성하고, 리스트의 끝에 추가합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param data 새 노드에 저장할 데이터
 * @return SUCCESS(1) 또는 FAILURE(-1)
*/
int appendNode(Node** head, int data)
{
	// 새로운 노드 생성
	Node* newNode = createNode(data);

	// 메모리 할당 성공 여부 확인
	if (!newNode)
		return FAILURE;

	// 리스트가 비어있는 경우
	if (*head == NULL)
	{
		// 새 노드를 헤드로 설정
		*head = newNode;
		return SUCCESS;
	}

	// 리스트의 끝으로 이동
	Node* temp = *head;

	// 시간 복잡도 O(n)
	while (temp->next != NULL)
		temp = temp->next;

	// 새 노드를 리스트의 끝에 추가
	temp->next = newNode;


	return SUCCESS;
}

/**
 * 인덱스에 해당하는 노드를 찾습니다.
 * @param head 리스트의 헤드 노드 포인터
 * @param index 찾고자 하는 노드의 인덱스 (0부터 시작)
 * @return 인덱스에 해당하는 노드의 포인터, 없으면 NULL
*/
Node* findNode(Node* head, size_t index)
{
	// 임시 포인터와 현재 인덱스 초기화
	Node* temp = head;
	size_t currentIndex = 0;

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

	return NULL;
}

/**
 * 새로운 노드를 생성하고, 타겟 노드 뒤에 삽입합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param target 타겟 노드의 주소
 * @param data 새 노드에 저장할 데이터
 * @return SUCCESS(1) 또는 FAILURE(-1)
*/
int insertNodeAtTarget(Node** head, Node* target, int data)
{
	// 유효성 검사
	if (head == NULL)
		return FAILURE;

	// 새로운 노드 생성
	Node* newNode = createNode(data);

	// 메모리 할당 성공 여부 확인
	if (!newNode)
		return FAILURE;

	if (*head == NULL)
	{
		// 리스트가 비어있고 target이 NULL일 때만 허용: 빈 리스트에 삽입
		if (target == NULL)
		{
			*head = newNode;
			return SUCCESS;
		}
		// target이 NULL이 아니면 (비어있는 리스트에서) 삽입 불가
		free(newNode);
		return FAILURE;
	}
	// 타겟 노드를 찾아서 그 뒤에 새 노드 삽입
	Node* temp = *head;

	// 시간 복잡도 O(n)
	while (temp != NULL)
	{
		// 타겟 노드 발견 시 삽입
		if (temp == target)
		{
			newNode->next = temp->next; // 새 노드의 next를 타겟의 next로 설정
			temp->next = newNode; // 타겟의 next를 새 노드로 설정
			return SUCCESS; 
		}
		temp = temp->next;
	}
	
	// 타겟 노드를 찾지 못함
	return FAILURE;
}

/**
 * 리스트의 모든 노드를 출력합니다.
 * @param head 리스트의 헤드 노드 포인터
*/
void printList(Node* head)
{
	Node* temp = head;
	int index = 0;

	// 리스트를 순회하며 각 노드의 데이터 출력
	// 시간 복잡도 O(n)
	while (temp != NULL)
	{
		printf("[%d] : %d -> ", index, temp->data);
		temp = temp->next;
		index++;
	}
	printf("NULL\n");
}

/**
 * 타겟 노드를 리스트에서 제거합니다.
 * @param head 리스트의 헤드 노드에 대한 이중 포인터
 * @param target 타겟 노드의 주소
 * @return SUCCESS(1) 또는 FAILURE(-1)
*/
int removeNode(Node** head, Node* target)
{
	if (head == NULL || *head == NULL || target == NULL)
		return FAILURE;
	
	Node* temp = *head;

	if (temp == target)
	{
		*head = temp->next;
		free(temp);
		return SUCCESS;
	}

	while (temp->next != NULL)
	{
		if (temp->next == target)
		{
			Node* nodeToDelete = temp->next;
			temp->next = nodeToDelete->next;
			nodeToDelete->next = NULL;
			free(nodeToDelete);
			return SUCCESS;
		}
		temp = temp->next;
	}
	// 타겟 노드를 찾지 못한 경우
	return FAILURE;
}

/**
 * 리스트의 모든 노드를 해제합니다.
 * @param head 리스트의 헤드 노드 포인터
*/
void freeList(Node* head)
{
	// 리스트가 비어있는 경우
	if (head == NULL)
		return;
	
	Node* temp = NULL;

	// 리스트를 순회 하며 각 노드 해제
	// 시간 복잡도 O(n)
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