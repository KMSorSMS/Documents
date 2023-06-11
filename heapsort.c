#include <stdio.h>
#include<stdlib.h>
#include <time.h>

//我这里的堆排序是最小堆

void shift(int* arr, int i, int n) {
    while (2 * i <= n) {//表明还有子结点
        int k = 2 * i;
        if (k + 1 <= n && arr[k - 1] > arr[k]) {
            k += 1;
        }
        if (arr[i - 1] > arr[k - 1]) {
            int temp = arr[i - 1];
            arr[i - 1] = arr[k - 1];
            arr[k - 1] = temp;//交换
            i = k;//走到子节点
        }
        else {
            return;//说明已经符合堆了
        }
    }
    return;
}
//这是最大堆得调换
void shiftLow2High(int* arr, int i, int n) {
    while (2 * i <= n) {//表明还有子结点
        int k = 2 * i;
        if (k + 1 <= n && arr[k - 1] < arr[k]) {//选择更大的一个子节点
            k += 1;
        }
        if (arr[i - 1] < arr[k - 1]) {//如果根结点更小，则不满足最大堆，就需要和最大的子结点交换   
            int temp = arr[i - 1];
            arr[i - 1] = arr[k - 1];
            arr[k - 1] = temp;//交换
            i = k;//走到子节点
        }
        else {
            return;//说明已经符合堆了
        }
    }
    return;
}

void heapsort(int* arr, int n) {
    //先对于传入对数组进行堆初始化
    /*思路如下：
        找到最后一个有子节点的结点（即最后一个非叶结点）也就是位置在n/2处向下取整
        然后从这个结点开始调整局部堆，需要一个工具函数shift(arr,i,n)表明从i处作为根开始，到n结束的堆进行调整
        一直到1处，编号是从1到n，n为个数
    */
    int mid = n / 2;
    for (int i = mid; i >= 1; i--) {
        //注意i-1才为在数组的编号
        shiftLow2High(arr, i, n);
    }
    //从最小堆不断取出顶部元素，移动元素，让数组变成降序排列
    for (int i = 1; i <= n; i++) {
        //将堆顶元素打印，此时为升序打印
        printf("%-2d ", arr[0]);
        //交换堆顶和堆底部
        int temp = arr[0];
        arr[0] = arr[n - i];
        arr[n - i] = temp;
        shiftLow2High(arr, 1, n - i);
    }
    printf("\n");
}
// //但是这个合并明显可以n个指针头分别进行
// void new_merge(const int *arr, int n, int k, int *output){
//     for(int i=0;i<k;i++){//遍历单个排序数组
//     int min =
//     //先找到i标记的最小的
//     for(int j=0;j<n;j++){

//     }
//     }
// }
//新增一个数组合并情况,传入的数组是升序的
void merge_arrays(const int *arr, int n, int k, int *output){
    for(int i=0;i<=n*k;i++){
        output[i] = arr[i];
    }
    heapsort(output,n*k);
}
int main(int argc, char const* argv[]) {
    srand((unsigned)time(NULL));
    int test[100], n = 20,k=5, test1[100],test2[200],output[200];
    for (int i = 0; i < n; i++) {
        test[i] = rand() % 100;
        test1[i] = rand() % 100;
    }
    for(int i=0;i < n*k;i++){
        test2[i] = rand() % 100;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", test[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", test1[i]);
    }
    for (int i = 0; i < n*k; i++) {
        printf("%d ", test2[i]);
    }
    printf("\n");
    heapsort(test, n);
    heapsort(test1,n);
    merge_arrays(test2,n,k,output);
    for (int i = 0; i < n*k; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");
    return 0;
}
