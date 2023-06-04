#include <stdio.h>
#include <stdlib.h>

typedef struct _blockInfo {
	int size_status;
} BlockInfo;
BlockInfo *heap_start;
BlockInfo *current_block;
void* mem_alloc(int size);
int mem_free(void *ptr);

void* mem_alloc(int num_bytes){//实现内存分配
    num_bytes = ((num_bytes+7)/8)*8;//将size向上取至8的倍数
    BlockInfo *endState = current_block;//记下当前位置，然后向下查找大小合适的块
    //这次我先实验只分配一次
    int size = current_block->size_status & 0xfffffffc;//得到大小
    int status = current_block->size_status & 0x00000003;//得到状态
    BlockInfo * tail = (BlockInfo *)((char *)current_block + size -sizeof(BlockInfo));
    current_block->size_status = num_bytes+1;//记录大小和状态
    BlockInfo *nextBlock = (BlockInfo *)((char *)current_block + num_bytes+sizeof(BlockInfo));//到下一个块
    nextBlock->size_status = size-sizeof(BlockInfo)-num_bytes+2;
    nextBlock = (BlockInfo *)((char *)nextBlock + size-2*sizeof(BlockInfo)-num_bytes);
    nextBlock->size_status = tail->size_status;

    return current_block;

    return NULL;
}
int main(int argc, char const *argv[])
{
    int size = sizeof(long)*1024;
    void * heap = malloc(size);
    heap_start = heap;
    heap_start->size_status = size;
    BlockInfo *tail = (BlockInfo *)((char *)heap_start +size - sizeof(BlockInfo));
    tail->size_status = 1;
    current_block = heap_start;
    mem_alloc(1320);
    mem_alloc(8820);
    mem_alloc(3340);
    return 0;
    return 0;
}
