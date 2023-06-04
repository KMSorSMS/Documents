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
    //始终从crrent_block开始查找空闲块，循环一圈后才算结束
    BlockInfo *endState = current_block;//记下当前位置，然后向下查找大小合适的块
    do{
      int heapSize = (current_block->size_status) & 0xfffffffc,status = (current_block->size_status) & 0x00000003;//获得该空闲块大小 要减去表头尾的长度 
      if(current_block->size_status!=1){//对于非最后一块的情况
        if((status == 1 || status == 3 || num_bytes>heapSize)){//如果是已经分配的，或者是大小很小的就走,要排除最后一块情况
            current_block = (BlockInfo *)((char *)current_block + heapSize);//地址加法，走下一个
            continue;//表明是已经分配的块，走向下一个
        }
      if(num_bytes<=heapSize&&num_bytes>=heapSize-2*sizeof(BlockInfo)){//如果空闲块大小能分配size，但是不能分割也就是多加1个info后放不下size，无需分割，直接分配
        current_block->size_status += 1;//将自己标记为已分配
        BlockInfo *nextState =  (BlockInfo *)((char *)current_block + heapSize);//地址加法，走下一个
        nextState->size_status += 2;//将下一个块的status标记为上一个已分配,这里不需要处理尾部，因为尾部块不存在于分配的块，为了保险可以置为0
        return current_block;
      }else{//说明空闲块的大小比较大，要分成两个部分,这个环节需要改变status的大小值
        current_block->size_status = num_bytes + status + 1;//将自己标记为已分配,加入状态信息
        BlockInfo *nextInfo = (BlockInfo *)((char *)current_block + num_bytes);//走到分割后的空闲块
        int remainSize = heapSize-num_bytes;
        nextInfo->size_status = remainSize + 2;//总大小减去前半部分的总大小,并标记上一个块已分配
        nextInfo = (BlockInfo *)((char *)nextInfo + remainSize - sizeof(BlockInfo));
        nextInfo->size_status = remainSize;//尾部放置信息块,空闲块尾部有信息
        return current_block;
      }
        }else current_block = heap_start;//对于最后一块,绕圈
    } while (current_block != endState);//只要还没绕完一圈就继续
    return NULL;//找了一圈都没有合适的大小
}
//测试
int main(int argc, char const *argv[])
{
    // int size = sizeof(long)*1024;
    // void * heap = malloc(size);
    // heap_start = heap;
    // heap_start->size_status = size-2*sizeof(BlockInfo);
    // BlockInfo *tail = (BlockInfo *)((char *)heap_start +size - 3*sizeof(BlockInfo));
    // tail->size_status = size-2*sizeof(BlockInfo);
    // tail = (BlockInfo *)((char *)tail + sizeof(BlockInfo));
    // tail->size_status = 1;
    // current_block = heap_start;
    // mem_alloc(1320);
    // mem_alloc(8820);
    // mem_alloc(3340);
    printf("fuck you");
    return 0;
}
