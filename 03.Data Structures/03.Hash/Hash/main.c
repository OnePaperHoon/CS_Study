#include "Hash.h"
#include <stdio.h>

int main()
{
    // 해시 테이블 생성
    HashTable* table = createHashTable(10);

    // 값 삽입
    int* value1 = (int*)malloc(sizeof(int));
    *value1 = 42;
    insert(table, "key1", value1);
    int* value2 = (int*)malloc(sizeof(int));
    *value2 = 84;
    insert(table, "key2", value2);

    // 값 검색
    int* retrieved1 = (int*)serch(table, "key1");
    if (retrieved1)
        printf("Key: key1, Value: %d\n", *retrieved1);
    int* retrieved2 = (int*)serch(table, "key2");
    if (retrieved2)
        printf("Key: key2, Value: %d\n", *retrieved2);
    // 해시 테이블 해제
    freeHashTable(table);
    free(value1);
    free(value2);
    free(table->buckets);
    free(table);
    return 0;
}