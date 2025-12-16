#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct HashNode {
    char* key; // 키
    void* value; // 값
    struct HashNode* next; // 충돌 해결을 위한 체이닝
} HashNode;

typedef struct HashTable {
    HashNode** buckets; // 버킷 배열
    size_t size; // 현재 저장된 요소의 수
    size_t capacity; // 해시 테이블의 총 버킷 수
} HashTable;

HashTable* createHashTable(size_t capacity);
void freeHashTable(HashTable* table);

unsigned long hashFunction(const char* str, size_t capacity);


bool insert(HashTable* table, const char* key, void* value);
void* serch(HashTable* table, const char* key);
bool delete(HashTable* table, const char* key);
void printHashTable(HashTable* table, void (*printValue)(void*));


#endif