#include <stdio.h>
#define Stack_Size 50
#define true 1
#define false 0
typedef int bool;
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
bool path(BiTNode *root, BiTNode *node, Stack *s);
typedef int DataType;

typedef struct Node
{
    DataType data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;
bool path(BiTNode *root, BiTNode *node, Stack *s)
{
    if (node == NULL)
        return false;
    BiTree nodeR = root, pre = NULL;
    while (!is_empty(s) || nodeR)
    {
        while (nodeR)
        {
            push(s, nodeR);
            if (nodeR == node)
            {
                return true;
            }
            nodeR = nodeR->left;
        }
        top(s, &nodeR);
        if (nodeR->right == NULL || nodeR->right == pre)
        {
            pre = nodeR;
            pop(s, &nodeR);
            nodeR = NULL;
        }
        else
        {
            nodeR = nodeR->right;
        }
    }
    return false;
}