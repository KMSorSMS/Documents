#include <stdio.h>
#include <stdlib.h>

/*
用邻接表法存储图
由递归的方式实现深度优先搜索
*/
#define MaxVertexNum 100 // 最大结点个数
int visited[100]; // static保证每次的dfs递归函数修改是对全局同一个visted数组修改
// 这里是邻接链表的结点定义
typedef struct node {
  int adjvex;           // 邻接点域 其实也就是弧头元素
  struct node* nextarc; // 链表的下一个结点指针
  int info;             // 用于存放结点内的数据
} EdgeNode;
// 这里是顶点
typedef struct vnode {
  int vexdata;       // 顶点域，其实也就是弧尾元素
  EdgeNode* firstarc; // 作为邻接链表的头指针
} VertexNode;
typedef VertexNode AdjList[MaxVertexNum]; // 形成顶点数组类型
int vertextNum, edgeNum;
//初始化图，邻接表法
void CreateAdjList(AdjList g) {
  //读入顶点数和边数
  printf("input vertexNum edgeNum\n");
  scanf("%d %d", &vertextNum, &edgeNum);
  for (int i = 1; i <= vertextNum; i++) {//遍历顶点填入信息
    // g[i].vexdata = getchar();//读入顶点信息
    g[i].firstarc = NULL; //设置边表为空，初始化操作
  }
  for (int i = 1; i <= edgeNum; i++) {
    int from, end;
    scanf("%d %d", &from, &end);//弧尾弧头
    EdgeNode* s;
    s = (EdgeNode*)calloc(1, sizeof(EdgeNode));
    s->adjvex = end;//邻接点的序号为弧头，即入度结点
    s->nextarc = g[from].firstarc;//头插法入链表
    g[from].firstarc = s;//头插法入链表
    //因为是无向图，所以反面也要来一遍
    s = (EdgeNode*)calloc(1, sizeof(EdgeNode));
    s->adjvex = from;//邻接点的序号为弧头，即入度结点
    s->nextarc = g[end].firstarc;//头插法入链表
    g[end].firstarc = s;//头插法入链表
  }
}

// 对单个连通图进行深度优先遍历
void dfs(AdjList g, int v) {
  EdgeNode* w; // 用于遍历结点v对应的整个邻接表
  int i;
  printf("%d", v);        // 遍历当前结点
  visited[v] = 1;         // 标记当前结点已经遍历
  w = g[v].firstarc;      // 初始化为邻接链表头
  while (w != NULL) {     // 只要链表中还有结点
    i = w->adjvex;        // 走到邻接结点往下
    if (visited[i] == 0) {
      dfs(g, i);
    }// 说明是可行的，未被访问过 // 向下深度优先访问
    w = w->nextarc;// 这里是上一个深度优先返回后或者结点是已访问过的后，平行去访问剩下的邻接结点
  }
}

void traverse(AdjList g, int n) {
  
  for (int i = 1; i <= n; i++)
    visited[i] = 0;
  for (int i = 1; i <= n; i++) {
    if (visited[i] == 0)
      dfs(g, i);
  }
}
int main(int argc, char const* argv[]) {
  AdjList g;
  CreateAdjList(g);
  traverse(g, vertextNum);
  printf("\n");
  return 0;
}
