# Double Linked List

## 개념

이중 연결 리스트(Double Linked List)는 각 노드가 **다음 노드(next)**와 **이전 노드(prev)** 두 개의 포인터를 가지는 선형 자료구조입니다.

### 노드 구조
```c
typedef struct Node {
    int data;           // 데이터
    struct Node* prev;  // 이전 노드를 가리키는 포인터
    struct Node* next;  // 다음 노드를 가리키는 포인터
} Node;
```

## 특징

### 장점
1. **양방향 순회 가능**: 앞에서 뒤로, 뒤에서 앞으로 모두 순회 가능
2. **삭제 연산 효율적**: 삭제할 노드만 알면 이전 노드를 찾기 위한 순회 불필요
3. **역방향 탐색**: tail에서 head 방향으로 탐색 가능

### 단점
1. **메모리 오버헤드**: 각 노드마다 포인터가 2개 필요 (단일 연결 리스트는 1개)
2. **구현 복잡도**: 단일 연결 리스트보다 구현이 복잡
3. **포인터 관리**: prev와 next 두 개의 포인터를 모두 관리해야 함

## 시간 복잡도

| 연산 | 시간 복잡도 | 설명 |
|------|------------|------|
| 탐색 (Search) | O(n) | 처음부터 순차 탐색 필요 |
| 삽입 (Insert) | O(1) | 위치를 알고 있을 때 |
| 삭제 (Delete) | O(1) | 삭제할 노드를 알고 있을 때 |
| 맨 앞 삽입/삭제 | O(1) | head 포인터 접근 |
| 맨 뒤 삽입/삭제 | O(n) 또는 O(1) | tail 포인터 유지 시 O(1) |

## 주요 연산

### 1. 노드 생성 (Create)
```c
Node* createNode(int data);
```
- 새로운 노드를 동적 할당하고 데이터를 초기화
- prev와 next는 NULL로 초기화

### 2. 삽입 (Insert)
```c
int addNode(Node** head, int data);        // 맨 뒤 삽입
int insertNode(Node** head, size_t index, int data);  // 특정 위치 삽입
```

**삽입 과정** (중간 노드 삽입 시):
```
[A] <-> [B] <-> [C]
         ↓ B 뒤에 X 삽입
[A] <-> [B] <-> [X] <-> [C]

1. newNode 생성
2. B->next = newNode
3. newNode->prev = B
4. C->prev = newNode
5. newNode->next = C
```

### 3. 삭제 (Remove)
```c
int removeNode(Node** head, size_t index);
int removeNodeByData(Node** head, int data);
```

**삭제 시 4가지 케이스**:

#### 케이스 1: 단일 노드 삭제
```
[A] → NULL
```
- `*head = NULL`

#### 케이스 2: 머리 노드 삭제
```
NULL <- [A] <-> [B] <-> [C]
         ↓ A 삭제
NULL <- [B] <-> [C]
```
- `*head = nextNode`
- `nextNode->prev = NULL`

#### 케이스 3: 꼬리 노드 삭제
```
[A] <-> [B] <-> [C] -> NULL
                 ↓ C 삭제
[A] <-> [B] -> NULL
```
- `prevNode->next = NULL`

#### 케이스 4: 중간 노드 삭제
```
[A] <-> [B] <-> [C] <-> [D]
         ↓ B 삭제
[A] <-> [C] <-> [D]
```
- `prevNode->next = nextNode`
- `nextNode->prev = prevNode`

### 4. 탐색 (Search)
```c
Node* findNodeByIndex(Node** head, size_t index);
Node* findNodeByData(Node** head, int data);
```
- head부터 순차적으로 탐색

### 5. 출력 (Print)
```c
void printList(Node** head);          // 순방향 출력
void printListRevers(Node** head);    // 역방향 출력
```

## 단일 연결 리스트와의 비교

| 특성 | 단일 연결 리스트 | 이중 연결 리스트 |
|------|----------------|----------------|
| 포인터 수 | 1개 (next) | 2개 (prev, next) |
| 순회 방향 | 한 방향 | 양방향 |
| 노드 삭제 | O(n) - 이전 노드 찾기 필요 | O(1) - 이전 노드 접근 가능 |
| 메모리 사용량 | 적음 | 많음 (포인터 1개 추가) |
| 구현 복잡도 | 낮음 | 높음 |

## 활용 사례

1. **브라우저의 앞/뒤로 가기**: 방문 기록을 양방향으로 탐색
2. **음악 플레이어**: 이전/다음 곡 재생
3. **텍스트 에디터의 Undo/Redo**: 작업 기록을 양방향으로 관리
4. **LRU Cache**: 최근 사용 항목을 양방향으로 관리
5. **운영체제의 프로세스 스케줄링**: 프로세스 리스트 관리

## 구현 시 주의사항

1. **메모리 누수 방지**: 삭제 시 반드시 `free()` 호출
2. **NULL 체크**: 모든 포인터 접근 전 NULL 체크
3. **경계 조건 처리**:
   - 빈 리스트
   - 단일 노드
   - 머리/꼬리 노드 처리
4. **포인터 업데이트 순서**: 기존 연결을 끊기 전에 새 연결 먼저 설정
5. **메모리 해제**: `destroyList()`로 프로그램 종료 전 전체 리스트 해제

## 코드 예제

### 리스트 생성 및 사용
```c
Node* head = NULL;

// 리스트 초기화
initHead(&head, 10);

// 노드 추가
addNode(&head, 20);
addNode(&head, 30);

// 출력: 10 <-> 20 <-> 30
printList(&head);

// 역방향 출력: 30 <-> 20 <-> 10
printListRevers(&head);

// 인덱스 1 뒤에 25 삽입
insertNode(&head, 1, 25);  // 10 <-> 20 <-> 25 <-> 30

// 데이터 20 삭제
removeNodeByData(&head, 20);  // 10 <-> 25 <-> 30

// 리스트 크기
size_t size = getListSize(&head);  // 3

// 메모리 해제
destroyList(&head);
```

## 마무리

이중 연결 리스트는 양방향 탐색이 필요한 경우에 매우 유용한 자료구조입니다. 추가 메모리를 사용하는 대신 삭제와 역방향 탐색에서 효율성을 얻을 수 있습니다.
