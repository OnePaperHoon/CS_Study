# Dynamic Array (동적 배열)

이 폴더는 C로 구현한 간단한 동적 배열(dynamic array, 가변 배열) 예제를 포함합니다. 구현 파일: `darray.c`, `darray.h`와 테스트용 `main.c`가 있습니다.

기능 요약

- 동적 크기 조절: 요소가 가득 차면 내부 버퍼를 증가시켜 저장 공간을 확장합니다.
- 기본 연산: 초기화, 삽입(push), 삭제(pop), 접근(get), 크기 조회(size), 해제(free)

빌드 및 실행

Windows (PowerShell)에서 다음 명령을 사용하세요:

```powershell
cd "Data Structures\dynamic_array"
make
.\darray
```

파일 설명

- `darray.h` : API 선언
- `darray.c` : 동적 배열 구현
- `main.c` : 사용 예제 및 간단한 테스트

확장 아이디어

- 에러 코드 표준화 (반환값 또는 errno)
- 삽입 시 복사 대신 이동(semi-shallow) 구현
- 스레드-안전성 추가 (mutex)

