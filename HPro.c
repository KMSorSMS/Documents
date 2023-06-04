#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;

// 非零元素结点结构
typedef struct OLNode
{
    int row, col;
    ElemType value;
    struct OLNode *right, *down;
} OLNode, *OLink;

// 十字链表结构
typedef struct
{
    OLink *rowhead, *colhead;
    int rows, cols, nums;
} CrossList, *PCrossList;

int init_cross_list(PCrossList L, const ElemType *A, int m, int n)
{
    int count = 0;

    L->rowhead = (OLink *)malloc(sizeof(OLink) * (m + 1));
    L->colhead = (OLink *)malloc(sizeof(OLink) * (n + 1));
    for (int i = 0; i < m; i++)
    {
        L->rowhead[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        L->colhead[i] = NULL;
    }
    L->rows = m, L->cols = n;
    if (L->rowhead == NULL || L->colhead == NULL)
    {
        return 0;
    }
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (*(A + c + r * n) != 0)
            {
                OLink node = (OLink)malloc(sizeof(OLNode));
                if (node == NULL)
                {
                    return 0;
                }
                node->col = c + 1;
                node->row = r + 1;
                node->value = *(A + c + r * n);
                node->right = NULL;
                node->down = NULL;
                OLink rowP = *(L->rowhead + r+1), colP = *(L->colhead + c+1);
                if (rowP != NULL)
                {
                    while (rowP->right != NULL)
                    {
                        rowP = rowP->right;
                    }
                    rowP->right = node;
                }
                else
                {
                    *(L->rowhead + r+1) = node;
                }
                if (colP != NULL)
                {
                    while (colP->down != NULL)
                    {
                        colP = colP->down;
                    }
                    colP->down = node;
                }
                else
                {
                    *(L->colhead + c+1) = node;
                }
                count++;
            }
        }
    }
    L->nums = count;
    return count;
}

int del_cross_list(PCrossList L, ElemType k)
{
    int count = 0;
    for (int i = 1; i <= L->rows; i++)
    {
        if (*(L->rowhead + i) == NULL)
        {
            continue;
        }
        OLink rowP = *(L->rowhead + i);
        OLink rowPre = rowP;
        if (rowP->value == k)
        {
            *(L->rowhead + i) = rowP->right;
            count++;
        }
        rowP = rowP->right;
        while (rowP != NULL)
        {
            if (rowP->value == k)
            {
                rowPre->right = rowP->right;
                count++;
                rowP = rowPre->right;
                continue;
            }
            rowP = rowP->right;
        }
    }
    for (int j = 1; j <= L->cols; j++)
    {
        if (*(L->colhead + j) == NULL)
        {
            continue;
        }
        OLink colP = *(L->colhead + j);
        OLink colPre = colP;
        if (colP->value == k)
        {
            *(L->colhead + j) = colP->down;
            free(colP);
        }
        colP = colP->down;
        while (colP != NULL)
        {
            if (colP->value == k)
            {
                colPre->down = colP->down;
                free(colP);
                colP = colPre->down;
                continue;
            }
            colP = colP->down;
        }
    }
    return count;
}

int main(int argc, char const *argv[])
{
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    PCrossList L = (PCrossList)malloc(sizeof(CrossList));
    init_cross_list(L, A, 2, 5);
    del_cross_list(L,3);
    return 0;
}
