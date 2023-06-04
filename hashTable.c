#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef enum {
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;
struct __HashEntry {
    union {
        char* str_value;
        double dbl_value;
        int       int_value;
    } key;
    union {
        char* str_value;
        double dbl_value;
        int       int_value;
        long   long_value;
        void* ptr_value;
    } value;
    HashEntry* next;
};

struct __HashTable {
    HashEntry** bucket;
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

// 创建大小为hash_size的哈希表，创建成功后返回HashTable类型的指针，否则返回NULL。
HashTable* create_hash(int hash_size);
// 向哈希表中添加元素，其中键类型为char*， 元素类型为int。
HASH_RESULT hash_add_int(HashTable* table, const char* key, int value);
long hash_string(const char* str) {
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if (hash < 0)
        hash *= -1;
    return hash;
}

HashTable* create_hash(int size) {
    HashTable* res = (HashTable*)malloc(1 * sizeof(HashTable));//为哈希表分配空间
    if (res == NULL) return NULL;
    res->bucket = (HashEntry**)malloc(size * sizeof(HashEntry*));//为哈希表每个条目分配空间
    if (res->bucket == NULL) {
        free(res); return NULL;
    }
    res->size = size;
    return res;
}

HASH_RESULT hash_add_int(HashTable* table, const char* key, int value) {
    long keyTemp = hash_string(key); //先取地址
    int keyIndex = keyTemp % (long)table->size;//对size取模保证在数组范围内
    HashEntry *linkList = table->bucket[keyIndex];
    //寻找key对应value
    while (linkList != NULL) {
        if (strcmp(linkList->key.str_value, key) == 0) {//如果key有，分为value相同和不同
            if (linkList->value.int_value == value) {
                return HASH_ALREADY_ADDED;
            }
            else {
                linkList->value.int_value = value;
                return HASH_REPLACED_VALUE;//更新value值
            }
        }
        linkList = linkList->next;
    }
    HashEntry* addEntry = (HashEntry*)calloc(1,sizeof(HashEntry));
    addEntry->key.str_value = (char*)calloc(50,sizeof(char));
    addEntry->next = table->bucket[keyIndex];
    strcpy(addEntry->key.str_value, key);
    addEntry->value.int_value = value;
    table->bucket[keyIndex] = addEntry;
    return HASH_ADDED;
}

int main(int argc, char const* argv[]) {
    HashTable* ht = create_hash(9);
    hash_add_int(ht, "qrbua", 384);
    hash_add_int(ht, "eoelr", 789);
    hash_add_int(ht, "eriba", 700);
    return 0;
}
