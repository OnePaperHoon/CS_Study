#include "Hash.h"

HashTable* createHashTable(size_t capacity)
{
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->capacity = capacity;
    table->size = 0;
    table->buckets = (HashNode**)calloc(capacity, sizeof(HashNode*));
    
    return table;
}

void freeHashTable(HashTable* table)
{
    for (size_t i = 0; i < table->capacity; i++)
    {
        HashNode* node = table->buckets[i];
        while (node)
        {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
}

unsigned long hashFunction(const char* str, size_t capacity)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % capacity;
}

bool insert(HashTable* table, const char* key, void* value)
{
    unsigned long index = hashFunction(key, table->capacity);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    table->size++;

    return TRUE;
}

void* serch(HashTable* table, const char* key)
{
    unsigned long index = hashFunction(key, table->capacity);
    HashNode* node = table->buckets[index];

    while(node)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }

    return NULL;
}

bool delete(HashTable* table, const char* key)
{
    unsigned long index = hashFunction(key, table->capacity);
    HashNode* node = table->buckets[index];
    HashNode* prev = NULL;

    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            if (prev)
                prev->next = node->next;
            else
                table->buckets[index] = node->next;

            free(node->key);
            free(node);
            table->size--;

            return TRUE;
        }
    }
    return FALSE;
}

void printHashTable(HashTable* table, void (*printValue)(void*))
{
    for (size_t i = 0; i < table->capacity; i++)
    {
        HashNode* node = table->buckets[i];
        if (node)
        {
            printf("Bucket %zu:\n", i);
            while (node)
            {
                printf("  Key: %s, Value: ", node->key);
                printValue(node->value);
                printf("\n");
                node = node->next;
            }
        }
    }
}