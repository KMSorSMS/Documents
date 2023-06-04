#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef int bool;
#define Stack_Size 50
typedef BiTNode *ElemType;
typedef struct
{
    ElemType elem[Stack_Size];
    int top;
} Stack;

void init_stack(Stack *S);        // 初始化栈
bool push(Stack *S, ElemType x);  // x 入栈
bool pop(Stack *S, ElemType *px); // 出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool top(Stack *S, ElemType *px); // 获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool is_empty(Stack *S);          // 栈为空时返回 true，否则返回 false
void visit_node(BiTNode *node);
typedef struct Node
{
    DataType data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;

void pre_order(BiTree root)
{
    Stack stack;
    BiTree node = root;
    init_stack(&stack);
    while (!is_empty(&stack) || node)
    {
        while (node)
        {
            visit_node(node);
            push(&stack, node);
            node = node->left;
        }
        pop(&stack,&node);
        node = node->right;
    }
}

int main(int argc, char const *argv[])
{
    int n, *l, *r;
    scanf("%d", &n);
    l = (int *)malloc(sizeof(int) * n);
    r = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", l + i, r + i);
    }
    printf("%d %d", 1, 2 * n - 1);
    return 0;
}
