#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef int bool;
typedef struct Node
{
    DataType data;
    struct Node *left;
    struct Node *right;
} BiTNode, *BiTree;
#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;
struct __Queue
{
    int i, j; // 指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue *create_queue();                   // 创建队列
bool is_empty_queue(Queue *tree);        // 队为空返回true,不为空时返回false
void *del_queue(Queue *tree);            // 结点指针出队
void add_queue(Queue *tree, void *node); // 结点指针入队
void free_queue(Queue *tree);            // 释放队列

BiTNode *transform(CSNode *root)
{
    CSNode *treenode = root;
    Queue *q = create_queue();
    Queue *bq = create_queue();                        // 二叉树也需要一个队列
    BiTree nodeRoot = (BiTree)malloc(sizeof(BiTNode)); // 创建局部根节点
    add_queue(q, treenode);                            // 普通树一层入队
    BiTree node = nodeRoot;
    node->left = NULL;
    node->right = NULL;
    add_queue(bq, node);
    while (!is_empty_queue(q) && !is_empty_queue(bq)) // 每次从普通树和二叉树中出队元素
    {
        treenode = (CSNode *)del_queue(q);
        node = (BiTree)del_queue(bq);
        int i = 0;
        node->data = treenode->data;
        // 将自己child入队，并且分配二叉树
        for (int i = 0; i < MAX_CHILDREN_NUM; i++)
        {
            if (treenode->children[i] != NULL)
            {                                                   // 说明有子
                BiTree nodeb = (BiTree)malloc(sizeof(BiTNode)); // 分配内存
                nodeb->left = NULL, nodeb->right = NULL;        // 置零
                if (i == 0)
                { // 对第一个为左儿子特判
                    node->left = nodeb;
                }
                else
                {
                    node->right = nodeb;
                }
                node = nodeb; // 向下一个节点侧移动
                add_queue(bq,node);//当前节点入队
                add_queue(q,treenode->children[i]);//当前树的子节点入队
            }
            else
            {
                break;
            }
        }
    }
    free_queue(bq);
    free_queue(q);
    return nodeRoot;
}