#include<stdio.h>
#define MAX_VERTEX_NUM 10
typedef int bool;
typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct{
    VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
int matrix_locate_vertex(MatrixGraph *MG, VertexType vex){
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        if(MG->vertex[i] == vex){
            return i;
        }
    }
    return -1;
}
bool matrix_insert_vertex(MatrixGraph *G, VertexType v){
     for(int i=0;i<MAX_VERTEX_NUM;i++){
         if(G->vertex[i] == v){
            return 0;
        }else if(G->vertex[i] <= 0){
            G->vexnum++;
            G->vertex[i] = v;
            for(int j=0;j<MAX_VERTEX_NUM;j++){
                G->arcs[i][j] = 0;
                G->arcs[j][i] = 0;
            }
            return 1;
        }
    }
    return 0;
}
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w){
    int indexv,indexw;
    if((indexv = matrix_locate_vertex(G,v))==-1 || (indexw = matrix_locate_vertex(G,w))==-1){
        return 0;
    }else{
        G->arcnum++;
         if( G->arcs[indexv][indexw]!=-1){
            return 0;
        }
        G->arcs[indexv][indexw] = 1;
        if(G->type == UDG){
            G->arcs[indexw][indexv] = 1;
        }
        return 1;
    }

}

