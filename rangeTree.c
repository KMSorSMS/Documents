/*
这里是树的前序中序以及后序遍历，非递归版本
*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
    int data;
    struct Node* LChild;
    struct Node* RChild;
}BiTNode, * BiTree;

typedef BiTree StackElem;

//栈的数据结构,顺序栈

typedef struct
{
    StackElem elem[50];//设置栈最大容量为50
    int top;//-1表示空栈,top指向当前栈顶位置
    int size;//标注栈的大小
}SeqStack;

void InitStack(SeqStack* S) {
    S->top = -1;//标注栈为空即可
    S->size = 50;//设置栈的大小为50；
}

int push(SeqStack* s, StackElem x) {
    if (s->top >= s->size - 1) return 0;//表明无法入栈
    s->top++;
    s->elem[s->top] = x;//入栈应该是栈顶指针加一，然后元素入栈
    return 1;
}

int pop(SeqStack* s, StackElem* x) {
    if (s->top <= -1) return 0;//栈为空
    *x = s->elem[s->top];//出栈
    s->top--;//堆顶下降
    return 1;//出栈成功
}
//查看栈顶不出栈
int top(SeqStack* s, StackElem* x) {
    if (s->top <= -1) return 0;
    *x = s->elem[s->top];
    return 1;
}
int isEmpty(SeqStack* s) {
    if (s->top <= -1) return 1;
    return 0;
}
int isFull(SeqStack* s) {
    if (s->top >= s->size - 1) return 1;
    return 0;
}

void visitNode(BiTree subT) {
    printf("%d ", subT->data);
}

void rangeHead1(BiTree tree) {
    //初始化一个数组用于栈；
    SeqStack stackIni;
    SeqStack* stack = &stackIni;
    InitStack(stack);
    push(stack, tree);//将根节点入栈
    while (!isEmpty(stack)) {
        BiTree subT;
        pop(stack, &subT);
        visitNode(subT);
        if (subT->RChild != NULL) push(stack, subT->RChild);
        if (subT->LChild != NULL) push(stack, subT->LChild);//分别将左右子树入栈，记住是左子树后入栈，这样才能先遍历
    }
    printf("\n--------------\n");
}
void rangeHeadClass(BiTree tree) {
    //这里的思路是访问根节点，入栈，再继续访问左子树，子树同样访问根节点，入栈，然后再访问左子树，结束后，出栈，访问出栈元素的右子树
    //初始化一个数组用于栈；
    SeqStack stackIni;
    SeqStack* stack = &stackIni;
    InitStack(stack);
    BiTree root = tree;
    while (root != NULL || !isEmpty(stack)) {
        if (root != NULL) {//如果是根节点不为空的情况，则访问根节点，入栈，访问左子树
            visitNode(root);
            push(stack, root);
            root = root->LChild;//访问左子树
        }
        else {
            pop(stack, &root);
            root = root->RChild;//访问右子树
        }
    }
    printf("\n--------------\n");
}
//中序遍历，非递归
/*
思路就是对根结点入栈，访问左子树，直到左子树为空时，从栈中弹出最近的根结点
然后访问该结点，再访问右子树，对于右子树，也是对根结点入栈，访问左子树，如果
左子树为空，同样从栈中弹出最近的根结点，然后访问该节点，再访问右子树，如果右子树为空，
一样的从栈中继续弹出根结点，如此操作直到栈为空
*/
void rangeMid1(BiTree tree) {
    //初始化栈
    SeqStack stackIni;
    SeqStack* stack = &stackIni;
    InitStack(stack);
    BiTree root = tree;
    while (root != NULL || !isEmpty(stack)) {
        if (root != NULL){
            push(stack,root);//将当前根结点入栈
            root = root->LChild;//走向左子树
        }else {//说明没有左子树，应该访问根节点然后访问右子树
            pop(stack,&root);
            visitNode(root);
            root = root->RChild;
        }
    }
    printf("\n--------------\n");
}
//后序遍历，非递归

//初始化满二叉树，数据随机生成
void initTree(BiTree tree, int layer, int max) {
    if (layer >= max) {
        tree->data = rand() % 99;
        tree->LChild = NULL;
        tree->RChild = NULL;
        return;
    }
    tree->data = rand() % 99;
    tree->LChild = (BiTree)calloc(1, sizeof(BiTNode));
    tree->RChild = (BiTree)calloc(1, sizeof(BiTNode));
    layer++;
    //递归调用生成左右子树
    initTree(tree->LChild, layer, max), initTree(tree->RChild, layer, max);
}

int main(int argc, char const* argv[]) {
    srand((unsigned)time(NULL));
    // for (int i = 0; i < 20; i++) {
    //     printf("%d ", rand() % 99);
    // }
    // printf("\n---------------\n");
    BiTNode treeNode;
    BiTree tree = &treeNode;
    initTree(tree, 1, 3);
    rangeHead1(tree);
    rangeHeadClass(tree);
    rangeMid1(tree);
    return 0;
}
