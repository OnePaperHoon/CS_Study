#include "doubleLinkedList.h"
#include <stdio.h>


/**
 * @param int 노드 내부 데이터 필드를 초기화할 데이터
 * @return Node* 또는 NULL(에러)
 */
Node* createNode(int data)
{
    // 새로운 노드 생성
    Node* newNode = (Node*)calloc(1, sizeof(Node));

    // 메모리 할당 성공 여부 확인
    if (!newNode)
        return NULL; // 실패시 NULL 리턴

    // 필드 초기화
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    // 새로운 노드 리턴
    return newNode;
}

/**
 * @param Node** 헤더
 * @param int 내부적으로 새로 생성할 노드의 데이터
 * @return SUCCESS or FAILURE
 */
int initHead(Node** head, int data)
{
    // 1. data를 기반으로 새로운 노드를 생성
    Node* newNode = createNode(data);
    
    // 2. 유효성 검사
    if (newNode == NULL)
    {
        // 2-1. FAILURE 리턴 
        return FAILURE;
    }

    // 3. head가 비어있는지 확인
    if (*head != NULL)
        return FAILURE;
    // 4. 새로운 노드를 header Node로 설정
    *head = newNode;
    
    // 5. SUCCESS 리턴
    return SUCCESS;
}

/**
 * @param Node** header
 * @param size_t 찾으려 하는 노드의 인덱스
 * @return Node* or NULL(error)
 */
Node* findNodeByIndex(Node** head, size_t index)
{
    // 1. 유효성 검사
    if (*head == NULL)
        return NULL;

    // 2. 변수 선언 currentIndex, Node* temp;
    size_t currentIndex = 0;
    Node* temp = *head;

    // 3. while문으로 index까지의 노드 탐색
    // 시간 복잡도 O(n)
    while (temp != NULL)
    {
        if (currentIndex == index)
            return temp;
        currentIndex++;
        temp = temp->next;
    }

    // 4. 인덱스 범위를 찾지 못함 NULL 반환
    return NULL;
}

/**
 * @param Node** head
 * @param int 찾으려 노드의 데이터
 * @return Node* or NULL(Error)
 */
Node*   findNodeByData(Node** head, int data)
{
    // 1. 유효성 검사
    if (*head == NULL)
        return NULL;

    // 2. temp 변수 선언
    Node* temp = *head;

    // 3. 전체 순회하며 조회
    while (temp)
    {
        // 4. 찾으려하는 값과 같은 노드를 찾으면 반환 
        if (temp->data == data)
            return temp;
        temp = temp->next;
    }

    // 4. 노드를 찾지 못했을때 NULL 반환
    return NULL;
}

/**
 * @param Node** 헤더
 * @param int 내부적으로 새로 생성할 노드의 데이터
 * @return SUCCESS or FAILURE
 */
int addNode(Node** head, int data)
{
    // 1. 새로운 노드를 생성
    Node* newNode = createNode(data);

    // 2. 생성된 노드의 유효성을 검사
    if (newNode == NULL)
        return FAILURE;
    
    // 2-1. 헤드가 빈 리스트이면 새 노드를 헤드로 설정
    if (*head == NULL) {
        *head = newNode;
        return SUCCESS;
    }

    // 3. Node* temp 생성
    Node* temp = *head;

    // 4. 리스트의 끝으로 이동
    while(temp->next != NULL)
        temp = temp->next;

    // 5. 가장 끝에 새로운 노드를 연결
    temp->next = newNode;
    newNode->prev = temp;

    // 6. 성공 여부를 리턴
    return SUCCESS;
}

/**
 * @param Node** 헤드
 * @param size_t 삽입할 노드의 위치
 * @param int 내부적으로 새로 생성할 노드의 데이터
 * @return SUCCESS or FAILURE
 * @attention 인덱스로 찾은 노드의 뒤에 삽입합니다.
 */
int insertNode(Node** head, size_t index, int data)
{
    // 1. 유효성 검사
    if (*head == NULL)
        return FAILURE;

    // 2. 새로운 노드 생성
    Node* newNode = createNode(data);

    // 3. 새로운 노드 유효성 검사
    if (newNode == NULL)
        return FAILURE;

    // 4. 타겟 노드 변수 및 next Node 변수 선언
    Node* target = findNodeByIndex(head, index);
    Node* nextNode = NULL;

    // 5. 타겟 노드 유효성 검사
    if (target == NULL)
        return FAILURE;

    nextNode = target->next;

    // 6. target<->nextNode 사이 삽입
    // target -> newNode 연결
    target->next = newNode;
    newNode->prev = target;

    // nextNode가 NULL이면 target이 마지막 노드
    if (nextNode)
    {
        // newNode -> nextNode 연결
        nextNode->prev = newNode;
        newNode->next = nextNode;
    }
    // 7. 성공 여부 리턴
    return SUCCESS;
}

/**
 * @param Node** haed
 * @param size_t 삭제할 노드의 인덱스
 */
int removeNode(Node** head, size_t index)
{
    // 1. 유효성 검사 - 리스트가 비어있는지 확인
    if (*head == NULL)
        return FAILURE;

    // 2. prevNode, currentNode, nextNode 변수 생성
    // NULL로 초기화하는 것이 안전합니다
    Node* prevNode = NULL;
    Node* currentNode = NULL;
    Node* nextNode = NULL;

    // 3. 삭제할 노드를 인덱스로 찾기
    currentNode = findNodeByIndex(head, index);

    // 4. 찾은 노드의 유효성 검사 - 인덱스가 범위를 벗어났는지 확인
    if (currentNode == NULL)
        return FAILURE;

    // 5. 삭제할 노드의 이전 노드와 다음 노드 저장
    // currentNode->prev가 NULL이 아닐 때만 prevNode에 저장
    // (머리 노드가 아닌 경우)
    if (currentNode->prev)
        prevNode = currentNode->prev;

    // currentNode->next가 NULL이 아닐 때만 nextNode에 저장
    // (꼬리 노드가 아닌 경우)
    if (currentNode->next)
        nextNode = currentNode->next;

    // 6. 케이스별 처리 (if-else if 구조로 상호 배타적으로 처리)

    // [케이스 1] 리스트에 노드가 하나만 있는 경우 (머리이자 꼬리)
    //   - prevNode == NULL && nextNode == NULL
    //   - *head를 NULL로 설정
    if (prevNode == NULL && nextNode == NULL)
    {
        *head = NULL;
    }
    // [케이스 2] 머리 노드를 삭제하는 경우 (prevNode == NULL, nextNode 존재)
    //   - *head를 nextNode로 변경
    //   - nextNode->prev를 NULL로 설정
    else if (prevNode == NULL)
    {
        *head = nextNode;
        nextNode->prev = NULL;
    }
    // [케이스 3] 꼬리 노드를 삭제하는 경우 (nextNode == NULL, prevNode 존재)
    //   - prevNode->next를 NULL로 설정
    else if (nextNode == NULL)
    {
        prevNode->next = NULL;
    }
    // [케이스 4] 중간 노드를 삭제하는 경우 (prevNode와 nextNode 모두 존재)
    //   - prevNode->next = nextNode
    //   - nextNode->prev = prevNode
    else
    {
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // 7. 모든 케이스에서 currentNode는 free()로 메모리 해제
    //    free(currentNode)는 currentNode가 가리키는 메모리만 해제하므로
    //    prev나 next가 NULL이어도 문제없습니다
    free(currentNode);
    // 8. SUCCESS 리턴
    return SUCCESS;
}

/**
 * @param Node** 헤드
 * @param int 삭제할 노드의 데이터
 * @return SUCCESS or FAILURE
 */
int removeNodeByData(Node** head, int data)
{
    // 1. 유효성 검사 - 리스트가 비어있는지 확인
    if (*head == NULL)
        return FAILURE;

    // 2. prevNode, currentNode, nextNode 변수 생성
    // NULL로 초기화하는 것이 안전합니다
    Node* prevNode = NULL;
    Node* currentNode = NULL;
    Node* nextNode = NULL;

    // 3. 삭제할 노드를 데이터로 찾기
    currentNode = findNodeByData(head, data);

    // 4. 찾은 노드의 유효성 검사 - 데이터를 가진 노드가 없는지 확인
    if (currentNode == NULL)
        return FAILURE;

    // 5. 삭제할 노드의 이전 노드와 다음 노드 저장
    // currentNode->prev가 NULL이 아닐 때만 prevNode에 저장
    // (머리 노드가 아닌 경우)
    if (currentNode->prev)
        prevNode = currentNode->prev;

    // currentNode->next가 NULL이 아닐 때만 nextNode에 저장
    // (꼬리 노드가 아닌 경우)
    if (currentNode->next)
        nextNode = currentNode->next;

    // 6. 케이스별 처리 (if-else if 구조로 상호 배타적으로 처리)

    // [케이스 1] 리스트에 노드가 하나만 있는 경우 (머리이자 꼬리)
    //   - prevNode == NULL && nextNode == NULL
    //   - *head를 NULL로 설정
    if (prevNode == NULL && nextNode == NULL)
    {
        *head = NULL;
    }
    // [케이스 2] 머리 노드를 삭제하는 경우 (prevNode == NULL, nextNode 존재)
    //   - *head를 nextNode로 변경
    //   - nextNode->prev를 NULL로 설정
    else if (prevNode == NULL)
    {
        *head = nextNode;
        nextNode->prev = NULL;
    }
    // [케이스 3] 꼬리 노드를 삭제하는 경우 (nextNode == NULL, prevNode 존재)
    //   - prevNode->next를 NULL로 설정
    else if (nextNode == NULL)
    {
        prevNode->next = NULL;
    }
    // [케이스 4] 중간 노드를 삭제하는 경우 (prevNode와 nextNode 모두 존재)
    //   - prevNode->next = nextNode
    //   - nextNode->prev = prevNode
    else
    {
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // 7. 모든 케이스에서 currentNode는 free()로 메모리 해제
    //    free(currentNode)는 currentNode가 가리키는 메모리만 해제하므로
    //    prev나 next가 NULL이어도 문제없습니다
    free(currentNode);

    // 8. SUCCESS 리턴
    return SUCCESS;
}

/**
 * @param Node** 헤드
 */
void printList(Node** head)
{
    // 1. 유효성 검사 - 리스트가 비어있는지 확인
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // 2. temp 변수 생성
    Node* temp = *head;

    // 3. 리스트 순회하며 출력
    printf("List: ");
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->next != NULL)
            printf(" <-> ");
        temp = temp->next;
    }
    printf("\n");
}

/**
 * @param Node** 헤드
 */
void printListRevers(Node** head)
{
    // 1. 유효성 검사 - 리스트가 비어있는지 확인
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    // 2. 마지막 노드(tail)를 찾기
    Node* tail = getTail(head);

    // 3. tail부터 역방향으로 순회하며 출력
    printf("List (Reverse): ");
    while (tail != NULL)
    {
        printf("%d", tail->data);
        if (tail->prev != NULL)
            printf(" <-> ");
        tail = tail->prev;
    }
    printf("\n");
}

/**
 * @param Node** 헤드
 * @return size_t 리스트의 크기
 */
size_t getListSize(Node** head)
{
    // 1. 유효성 검사 - 리스트가 비어있으면 0 반환
    if (*head == NULL)
        return 0;

    // 2. 카운트 변수와 temp 변수 생성
    size_t count = 0;
    Node* temp = *head;

    // 3. 리스트 순회하며 카운트
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // 4. 카운트 반환
    return count;
}

/**
 * @param Node** 헤드
 * @return SUCCESS or FAILURE
 */
int destroyList(Node** head)
{
    // 1. 유효성 검사 - 리스트가 비어있으면 FAILURE 반환
    if (*head == NULL)
        return FAILURE;

    // 2. temp 변수와 nextNode 변수 생성
    Node* temp = *head;
    Node* nextNode = NULL;

    // 3. 리스트 순회하며 모든 노드 메모리 해제
    while (temp != NULL)
    {
        // 다음 노드를 저장
        nextNode = temp->next;

        // 현재 노드 메모리 해제
        free(temp);

        // 다음 노드로 이동
        temp = nextNode;
    }

    // 4. head를 NULL로 설정
    *head = NULL;

    // 5. SUCCESS 반환
    return SUCCESS;
}

/**
 * @param Node** 헤드
 * @return 1(비어있음) or 0(비어있지 않음)
 */
int isEmpty(Node** head)
{
    // head가 NULL이면 1(true), 아니면 0(false) 반환
    return (*head == NULL) ? 1 : 0;
}

/**
 * @param Node** 헤드
 * @return Node* 마지막 노드 또는 NULL(에러)
 */
Node* getTail(Node** head)
{
    // 1. 유효성 검사 - 리스트가 비어있으면 NULL 반환
    if (*head == NULL)
        return NULL;

    // 2. temp 변수 생성
    Node* temp = *head;

    // 3. 마지막 노드까지 이동
    while (temp->next != NULL)
        temp = temp->next;

    // 4. 마지막 노드 반환
    return temp;
}