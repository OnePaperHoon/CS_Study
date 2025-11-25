# 배열 기반 선형 큐 (Array-based Linear Queue)

선형 큐는 고정 크기의 배열을 사용하여 큐를 구현한 방식입니다. 이 구현 방식에서는 `front`와 `rear` 인덱스가 배열 내에서 한 방향으로만 증가합니다. 따라서 삭제(dequeue)를 반복하면 `front`가 증가하여 배열 앞부분은 비어 있게 되지만, `rear`가 배열 끝에 도달하면 더 이상 삽입(enqueue)을 할 수 없게 됩니다. 이 때문에 선형 큐는 공간을 효율적으로 재사용하지 못하는 단점이 있습니다.

이 폴더의 구현 주요 포인트

- 헤더: `ArrayBasedLinearQueue.h` — 타입과 함수 선언
- 구현: `ArrayBasedLinearQueue.c` — 초기화, 검사, enqueue/dequeue, 출력
- 예제: `main.c` — 큐 사용 예시

구조체 예시 (정의 발췌)

```c
#define MAX_QUEUE_SIZE 5

typedef int ElementType;

typedef struct {
	ElementType data[MAX_QUEUE_SIZE]; // 내부 저장 공간
	int front; // 머리 인덱스 (다음에 읽을 위치)
	int rear;  // 꼬리 인덱스 (다음에 쓸 위치)
} ArrayBasedLinearQueue;
```

기본 API (이 구현에서 제공되는 함수)

- void initQueue(ArrayBasedLinearQueue* queue);
- int isQueueFull(const ArrayBasedLinearQueue* queue);
- int isQueueEmpty(const ArrayBasedLinearQueue* queue);
- int enqueue(ArrayBasedLinearQueue* queue, ElementType item); // 0 성공, -1 실패
- int dequeue(ArrayBasedLinearQueue* queue, ElementType* item); // 0 성공, -1 실패
- void displayQueue(const ArrayBasedLinearQueue* queue);

동작 예시 (프로그램 플로우)

1. 초기화: `initQueue(&queue)` — front/rear를 0으로 설정
2. 삽입: `enqueue`는 rear 위치에 값을 쓰고 rear를 증가시킵니다. 만약 rear가 MAX_QUEUE_SIZE에 도달하면 큐는 가득 찼다고 간주합니다.
3. 삭제: `dequeue`는 front 위치의 값을 반환하고 front를 증가시킵니다.

문제점(선형 큐의 한계)

- 이 구현은 `rear`가 배열 끝에 도달하면 더 이상 삽입할 수 없습니다. 예를 들어, MAX_QUEUE_SIZE가 5이고 5번의 enqueue를 한 뒤 몇 번 dequeue를 하더라도 `rear`가 끝에 도달하면 추가 enqueue가 실패합니다. 즉 사용 가능한 빈 공간이 앞쪽에 있음에도 재활용되지 않습니다.

해결 방법(추천)

- 원형 큐(Circular queue): `front`와 `rear`를 모듈로 연산으로 처리하면 공간을 재활용할 수 있습니다. 이 저장소에는 `01.Circular Queue` 예제가 별도 폴더로 제공되어 있으니 참고하세요.

예제 코드 스냅샷 (main.c에서 발췌)

```c
ArrayBasedLinearQueue queue;
ElementType item;

initQueue(&queue);
enqueue(&queue, 10);
enqueue(&queue, 20);
enqueue(&queue, 30);
displayQueue(&queue); // 출력 예: 10 20 30
dequeue(&queue, &item); // item == 10
enqueue(&queue, 40);
enqueue(&queue, 50);
// 다음 enqueue는 실패할 수 있음(큐가 가득 찼다면 -1 반환)
```


샘플 출력 (대략)

```
Queue: 10 20 30
Dequeued: 10
Queue: 20 30
Queue: 20 30 40 50
Queue is full, cannot enqueue 60
```

왜 선형 큐에 문제가 생기나? — 원인과 직관적 이해

선형 큐에서 `front`와 `rear`는 항상 증가(단방향)합니다. `front`는 다음에 꺼낼 위치, `rear`는 다음에 쓸 위치를 가리키므로 다음 상태 불변식(invariant)을 갖습니다:

- 빈 큐: front == rear
- 요소 개수: rear - front

예를 들어, MAX_QUEUE_SIZE = 5 인 상태에서 다음 순서로 연산을 하면 어떤 일이 일어나나요?

1) enqueue 10,20,30 -> front=0, rear=3, 배열: [10,20,30,_,_]
2) dequeue -> 가져온 값 10, front=1, rear=3, 배열 앞쪽엔 빈 공간(재사용되지 않음)
3) enqueue 40,50 -> front=1, rear=5, 배열: [10,20,30,40,50]
4) 지금 rear == MAX_QUEUE_SIZE 이므로 enqueue 시도(예: enqueue 60)는 실패합니다. 하지만 실제로는 앞쪽 인덱스(front=1)에 빈 공간이 있어 총 저장 가능한 요소 수(4)가 아직 남아 있습니다.

이 문제는 왜 생기냐면 "rear가 배열 끝에 도달하면 더 이상 쓸 공간이 없다"라고 판단하기 때문입니다. 즉, 내부적으로는 배열의 앞부분(front이 지나온 공간)을 재활용하지 않기 때문에 발생합니다.

왜 원형 큐가 이 문제를 해결하나? — 핵심 아이디어

원형 큐(circular queue)는 배열 인덱스를 모듈로 연산(modulo)으로 다루어 인덱스가 배열 끝에 도달하면 다시 0으로 순환합니다. 그러면 배열 앞쪽에 비어 있는 공간이 자동으로 재활용됩니다.

핵심 차이:

- 선형 큐: rear, front는 계속 증가 — 공간 낭비 가능
- 원형 큐: rear = (rear + 1) % MAX, front = (front + 1) % MAX — 항상 배열 전체를 순환적으로 사용

원형 큐에서 빈/가득 조건 처리 방식 (종류)

1) 1칸을 비워두는 방식: rear + 1 == front 이면 가득
	- 장점: front == rear 로 빈 상태를 구분 가능
	- 단점: 실제 최대 수용량이 MAX-1 이 됨

2) 크기(count) 변수를 유지하는 방식: enqueue/dequeue 시 count를 증가/감소
	- 장점: 버퍼를 완전히 사용 가능
	- 단점: 하나의 정수 보관이 필요하지만 구현은 간단

왜 'front==rear'로 빈 상태를 판단하나?

선형 구현과 (특정) 원형 구현에서 front==rear를 빈 상태 판정으로 사용하는 관습은 간단합니다. 다만 원형 구현에서 동일한 표현을 가득(full)과 혼동하지 않으려면 위의 두 가지 해결책(1칸 비우기 또는 count 사용) 가운데 하나를 선택해야 합니다.

코드 구현 팁 / 주의사항

- 인덱스 오버플로우: 반복해서 enqueue/dequeue를 하면 front/rear 값이 계속 커집니다. 선형 큐에서는 곧 범위를 초과할 수 있으므로 실전에서는 인덱스를 리셋하거나(예: 둘 다 같은 값이면 0으로) 모듈로 연산을 사용하는 것이 안전합니다.
- 에러 처리: enqueue/dequeue는 반환값을 반드시 확인하세요. 실패(-1)를 보고 적절히 처리해야 합니다.
- 연산 복잡도: 단순 선형 큐에서 enqueue/dequeue는 O(1) 입니다. 다만, 만약 빈 공간을 채우기 위해 배열 원소들을 왼쪽으로 시프트(앞으로 이동)하는 선택을 하면 그 연산은 O(n) 이며 일반적으로 권장되지 않습니다.

요약 — 학습 포인트

- 선형 큐는 개념적으로 간단하지만, 배열의 앞부분을 재활용하지 못해 실제 공간이 비효율적으로 사용될 수 있다.
- 원형 큐는 모듈로 연산을 사용해 공간을 재활용함으로써 선형 큐의 단점을 해결한다.
- 실용적 구현에서는 빈/가득 상황을 정확히 구분하기 위해 "하나 비우기" 방식 또는 카운트 유지 방식을 선택한다.
