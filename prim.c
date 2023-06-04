/*通过prim算法实现最小生成树*/
#include <stdio.h>
#define MAXV 20
#define INF 200
typedef struct
{
    int no; //顶点编号
    int info; //顶点其它信息
}VertexTyte;
typedef struct
{
    int edges[MAXV][MAXV];//邻接矩阵存储
    int n, e;//顶点数，边数
    VertexTyte vexs[MAXV];//存放顶点信息
}MatGraph;//邻接矩阵存储图

void prim(MatGraph g) {
    int lowcost[MAXV];//存储其它结点到部分生成树的最短距离
    int closest[MAXV];//存储其它结点到生成树的最短距离对应的结点
    //初始化lowcost和closest
    for (int i = 0; i < g.n; i++) {
        lowcost[i] = g.edges[g.vexs[0].no][g.vexs[i].no];
        closest[i] = g.vexs[0].no;
    }
    lowcost[g.vexs[0].no] = 0;
    //标记初始结点在最小部分生成树中
    for (int j = 1; j < g.n; j++) {
        //循环遍历寻找最小结点连接，再更新
        int min = INF;
        int index;
        int k;//记录最小的结点的编号
        for (int i = 1; i < g.n; i++) {
            index = g.vexs[i].no;
            if (lowcost[index] != 0 && lowcost[index] < min) {//表明结点i没有被纳入部分生成树，并且比当前最小的还要小
                min = lowcost[index];
                k = index;
            }
        }
        if (min == INF) {
            printf("not adj");
            return;//说明不是连通图
        }
        lowcost[k] = 0;//标记加入部分最小生成树
        //出循环，找到当前prim最小点，用其更新其它结点到部分最小生成树的距离lowcost和closest
        for (int i = 1; i < g.n; i++) {
            index = g.vexs[i].no;
            if (lowcost[index] != 0 && lowcost[index] > g.edges[k][index]) {//如果其到加入了k的部分最小生成树更小，那么就更新
                lowcost[index] = g.edges[k][index];
                closest[index] = k;
            }
        }
        //完成更新后开始下一轮循环
    }
    //最后打印结果
    for (int i = 0; i < g.n; i++) {
        printf("%d ", closest[g.vexs[i].no]);
    }
    printf("\n");
    return;
}
int main(int argc, char const* argv[]) {
    //创建一个连通图
    MatGraph g;
    for (int i = 0; i < 10; i++) {
        VertexTyte v;
        v.info = i * 10;
        v.no = i;
        g.vexs[i] = v;
        for (int j = 0; j < 10; j++) {
            g.edges[i][j] = j%4+7*i%4+1;
            g.edges[j][i] = j%4+7*i%4+1;
        }
    }
    g.n = 10;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%-2d ", g.edges[i][j]);
        }
        printf("\n");
    }
    printf("-------------\n");
    prim(g);
    return 0;
}
