#include <stdio.h>
#include <stdlib.h>
typedef int VertexType;
#define MAX_VERTEX_NUM 10
typedef int bool;
typedef enum { DG, UDG } GraphType;

typedef struct ArcNode {
  int adjvex;
  struct ArcNode *nextarc;

} ArcNode;

typedef struct VNode {
  VertexType data;
  ArcNode *firstarc;
} VNode;
typedef struct {
  VNode vertex[MAX_VERTEX_NUM];
  int vexnum, arcnum;
  GraphType type;
} ListGraph;

int locate_vertex(
    ListGraph *G,
    VertexType v); // 返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v);
bool insert_arc(ListGraph *G, VertexType v, VertexType w);
bool del_vertex(ListGraph *G, VertexType v); // 删除顶点 v
int locate_vertex(ListGraph *G, VertexType v) {
  for (int i = 0; i < MAX_VERTEX_NUM; i++) {
    if (G->vertex[i].data == v) {
      return i;
    }
  }
  return -1;
}
bool insert_vertex(ListGraph *G, VertexType v) {
  int index = locate_vertex(G, v);
  if (index == -1) {
    G->vertex[G->vexnum].data = v;
    G->vexnum++;
    return 1;
  }
  return 0;
}
bool insert_arc(ListGraph *G, VertexType v, VertexType w) {
  int indexv, indexw;
  if ((indexv = locate_vertex(G, v)) == -1 ||
      (indexw = locate_vertex(G, w)) == -1) {
    return 0;
  } else {
    ArcNode *vnc = G->vertex[indexv].firstarc,
            *wnc = G->vertex[indexw].firstarc, *prev = NULL, *prew = NULL;
    while (vnc != NULL) {
      if (vnc->adjvex == indexw) {
        return 0;
      }
      prev = vnc;
      vnc = vnc->nextarc;
    }
    vnc = (ArcNode *)calloc(1, sizeof(ArcNode));
    vnc->adjvex = indexw;
    vnc->nextarc = NULL;
    if (prev == NULL) {
      G->vertex[indexv].firstarc = vnc;
    } else {
      prev->nextarc = vnc;
    }
    if (G->type == UDG) {
      while (wnc != NULL) {
        if (wnc->adjvex == indexv) {
          return 0;
        }
        prew = wnc;
        wnc = wnc->nextarc;
      }
      wnc = (ArcNode *)calloc(1, sizeof(ArcNode));
      wnc->adjvex = indexv;
      wnc->nextarc = NULL;
      if (prew == NULL) {
        G->vertex[indexw].firstarc = wnc;
      } else {
        prew->nextarc = wnc;
      }
    }
    G->arcnum++;
    return 1;
  }
}
bool del_vertex(ListGraph *G, VertexType v) { // 删除顶点 v
  int indexv = locate_vertex(G, v);
  if (indexv == -1)
    return 0;
  for (int i = 0; i < G->vexnum; i++) {
    ArcNode *pre = NULL, *arc = G->vertex[i].firstarc;
    if (i == indexv) {
      while (arc != NULL) {
        pre = arc;
        arc = arc->nextarc;
        free(pre);
        G->arcnum--;
      }
      G->vertex[i].firstarc = NULL;
      G->vertex[i].data = 0;
      G->vexnum--;
    } else {
      if (arc == NULL)
        continue;
      if (arc->adjvex == indexv) {
        G->vertex[i].firstarc = arc->nextarc;
        free(arc);
        G->arcnum--;
        continue;
      }
      while (arc != NULL) {
        if (arc->adjvex == indexv) {
          pre->nextarc = arc->nextarc;
          free(arc);
          arc = pre;
          G->arcnum--;
        }
        pre = arc;
        arc = arc->nextarc;
      }
    }
  }
  return 1;
}