#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100          //假设非零元个数的最大值为100
#define true 1;
#define false 0;
typedef int ElemType;
typedef int bool;

typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
if(pM->m==pN->m && pM->n == pN-> n){
    const TSMatrix *startPos = pM,*endPos = pN;
    if(pN->data[0].i < pM->data[0].i ||( pN->data[0].i == pM->data[0].i && pN->data[0].j < pM->data[0].j)){
        startPos = pN;
        endPos = pM;
    }
    int startcount=0,endcount=0,in=0;
    while(startcount <= startPos->len-1){
        if(startPos->data[startcount].i==endPos->data[endcount].i&&startPos->data[startcount].j==endPos->data[endcount].j){
           if(startPos->data[startcount].e + endPos->data[endcount].e){
            pQ->data[in].e = startPos->data[startcount].e + endPos->data[endcount].e;
            pQ->data[in].i = startPos->data[startcount].i;
            pQ->data[in].j = startPos->data[startcount].j;
            startcount++,endcount++,in++;
           }else{
            startcount++,endcount++;
           }
        }else{
            pQ->data[in] = startPos->data[startcount];
            startcount++,in++;
        }
        //更新startcount，endcount，startpos，endpos
        if(startPos->data[startcount].i>endPos->data[endcount].i||(startPos->data[startcount].i==endPos->data[endcount].i&&startPos->data[startcount].j>endPos->data[endcount].j)){
            int swap = startcount;
            startcount = endcount;
            endcount = swap;
            const TSMatrix *swapMatrix = startPos;
            startPos = endPos;
            endPos = swapMatrix; 
        }
    }
    //对于endpos剩下的
    while (endcount <= endPos->len-1)
    {
          pQ->data[in] = endPos->data[endcount];
            endcount++,in++;
    }
    pQ->len = in;
    return true;
}else {
    return false;
}
}