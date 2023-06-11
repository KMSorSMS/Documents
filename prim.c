/*通过prim算法实现最小生成树*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 20
#define INF 200
typedef struct
{
    int no; //顶点编号
    int info; //顶点其它信息
}VertexTyte;
//MatGraph具有edges边数组、n顶点数量、e边数量、以及vexs顶点数组
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
    printf("\n prim 结束\n");
    return;
}

//floyd算法寻找全图最短路径
void ShortestPath_Floyd(MatGraph g, int** path, int** dis) {
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            dis[i][j] = g.edges[i][j];//初始化i到j的距离
            if (dis[i][j] < INF) {
                path[i][j] = -1;//标记i到j的当前最短路径上，中间结点编号为-1，即不存在
            }
        }
    }
    //三重循环遍历整个图进行松弛
    for (int i = 0; i < g.n; i++) {//中间结点
        for (int j = 0; j < g.n; j++) {//起点
            for (int k = 0; k < g.n; k++) {//终点
                if (dis[j][k] > dis[j][i] + dis[i][k]) {//如果j到k的距离大于j到i再到k的距离，那么就更新
                    dis[j][k] = dis[j][i] + dis[i][k];//更新j到k的最短距离
                    path[j][k] = i;//更新j到k的最短路径上的中间结点为i
                }
            }
        }
    }
}

//打印floyd算法的结果
void PrintPath_Floyd(MatGraph g, int** path, int** dis, int i, int j) {//指定起点i和终点j
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            printf("%-2d ", dis[i][j]);
        }
        printf("\n");
    }
    printf("\n-------floyd-------------\n");
    /*打印从i到j的最短路径 ，因为path里面存储的是中间结点的编号，所以需要使用栈打印
        这里我使用一个比较简单的栈，不去完整实现函数，int top是栈顶指针，stack数组是
        栈，栈的大小是g.n，每次打印都是前半部分一直入栈，到达path为-1的地方出栈，打印序列，
        然后对后半部分同样由中间结点分为两部分，直到后半部分为空
    */
   printf("%d ", i);//打印起点
    while (path[i][j] != -1) {//对于有中间结点的情况
        int stack[MAXV];
        int top = -1;
        int k = path[i][j];
        while (k != -1) {
            stack[++top] = k;//入栈
            k = path[i][k];//更新k
        }
        while (top != -1) {//打印前半部分
            printf("%d ", stack[top--]);//出栈
        }
        i = path[i][j];//更新i,对后半部分重复上述操作
    }
    printf("%d ", j);//打印终点
    printf("\n-------floyd---------------\n");
    return;
}

int main(int argc, char const* argv[]) {
    srand((unsigned)time(NULL));

    //创建一个连通图
    MatGraph g;
    for (int i = 0; i < 10; i++) {
        VertexTyte v;
        v.info = i * 10;
        v.no = i;
        g.vexs[i] = v;
        for (int j = 0; j < 10; j++) {
            g.edges[i][j] = rand() % 100 + 1;
            g.edges[j][i] = rand() % 100 + 1;
        }
    }
    g.n = 10;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%-2d ", g.edges[i][j]);
        }
        printf("\n");
    }
    printf("\n-------初始化完成-------------\n");
    prim(g);
    //测试floyd算法
    int** path = (int**)malloc(sizeof(int*) * g.n);
    int** dis = (int**)malloc(sizeof(int*) * g.n);
    for (int i = 0; i < g.n; i++) {
        path[i] = (int*)malloc(sizeof(int) * g.n);
        dis[i] = (int*)malloc(sizeof(int) * g.n);
    }
    ShortestPath_Floyd(g, path, dis);
    PrintPath_Floyd(g, path, dis, 0, 9);
    return 0;
}
