#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef enum
{
	HASH_PTR,
	HASH_NUMERIC,
	HASH_STRING,
} HASH_VAL_TAG;

typedef struct __HashEntry HashEntry;
struct __HashEntry{
    union{
        char  *str_value;
        double dbl_value;
        int    int_value;
    } key;
    HASH_VAL_TAG val_tag;
    union{
        char  *str_value;
        double dbl_value;
        int    int_value;
        long   long_value;
        void  *ptr_value;
    } value;
    HashEntry *next;
};

struct __HashTable{
    HashEntry **bucket;        
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

long hash_string(const char *str){
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if(hash < 0)
        hash *= -1;
    return hash;
}

// 向哈希表中添加元素，其中键类型为char*， 元素类型为char*。
HASH_RESULT hash_add_str(HashTable* table, const char *key, char *value );
// 从哈希表中删除元素，其中键类型为char*。
HASH_RESULT hash_del_str(HashTable *table, char *key );

HASH_RESULT hash_add_str(HashTable* table, const char *key, char *value ){
    //先遍历一次确定key是否存在
    long temp = hash_string(key);//根据hash函数确定在数组中的位置
    int hash_index = temp % table->size;//将产生的极大数字与表的大小取模
    HashEntry *bucket = table->bucket[hash_index];//获得hash桶对应处的链表指针,这里没有头节点
    while(bucket != NULL){//定位到对应key处
        if(strcmp(bucket->key.str_value,key)==0){//key相同
            if(strcmp(bucket->value.str_value,value)==0){//如果value也相同，表明已经加入
                return HASH_ALREADY_ADDED;
            }else{//说明value不同，更新value
                strcpy(bucket->value.str_value,value);//将内容拷贝
                return HASH_REPLACED_VALUE;
            }
        }
        bucket = bucket->next;//走向下一个节点
    }
    //如果能出循环，说明了key不在此链表中，需要头插法加入entry
    HashEntry *bucketadd = (HashEntry *)calloc(1,sizeof(HashEntry));//为新的节点分配空间
    bucketadd->key.str_value = (char *)calloc(strlen(key)+1,sizeof(char)),bucketadd->value.str_value = (char *)calloc(strlen(value)+1,sizeof(char));//初始化分配大小
    strcpy(bucketadd->key.str_value,key),strcpy(bucketadd->value.str_value,value),bucketadd->val_tag = HASH_STRING;
    //插入到链表中，头插法
    bucketadd->next = table->bucket[hash_index];
    table->bucket[hash_index] = bucketadd;
    return HASH_OK;
}

HASH_RESULT hash_del_str(HashTable *table, char *key ){//切记free
    //遍历查找key是否存在
    long temp = hash_string(key);//根据hash函数确定在数组中的位置
    int hash_index = temp % table->size;//将产生的极大数字与表的大小取模
    HashEntry *bucket = table->bucket[hash_index];//获得hash桶对应处的链表指针,这里没有头节点
    HashEntry *formerBucket = bucket;//记录删去节点的上一个指针
    //对第一个节点特判
    if(strcmp(bucket->key.str_value,key)==0){//如果第一个元素就是要删除的
        table->bucket[hash_index] = bucket->next;//头指针指向下一个节点
        free(bucket);//释放第一个节点
        return HASH_DELETED;
    }
    bucket = bucket->next;//寻找节点走向下一个
    while(bucket!=NULL){
        if(strcmp(bucket->key.str_value,key)==0){//找到删除节点
            formerBucket->next = bucket->next;
            free(bucket);//释放节点
            return HASH_DELETED;
        }
        formerBucket = bucket;
        bucket = bucket->next;//走向下一个节点，并用former保存上一个节点
    }
    return HASH_NOT_FOUND;//走出来了都没有找到，说明是没有
}
//测试
int main(int argc, char const *argv[])
{
    HashTable *table = (HashTable *)calloc(1,sizeof(HashTable));
    table->size = 9;
    table->bucket = (HashEntry **)calloc(table->size,sizeof(HashEntry *));//分配数组空间
    char key[20],value[20];
    while (1){
        // char *key,*value;
        // key = (char *)calloc(20,sizeof(char)),value = (char *)calloc(20,sizeof(char));
        scanf("%s %s",key,value);
        hash_add_str(table,key,value);

    }
    return 0;
}
