//
// Created by xulon on 2023/6/30.
//
#include <stdio.h>

#define maxValue 32767          // 整数最大值（在limits.h中定义）
#define Num 11                  // 渡河状态数加1
typedef struct {                // 图的结构定义
    int numVertices, numEdges;  // 图中实际顶点个数和边的条数
    char *VerticesList[Num];    // 顶点表
    int Edge[Num][Num];         // 邻接矩阵
} MGraph;

void Dijkstra1(MGraph &G, int dist[], int path[]) {
    int i, j, k, min, n = G.numVertices;  // 顶点数
    int S[Num];
    for (i = 1; i <= n; i++) {
        dist[i] = G.Edge[1][i];
        path[i] = (dist[i] > 0 && dist[i] < maxValue) ? 1 : 0;
        S[i] = 0;
    }
    S[1] = 1;                   // 源点标志为"已求得最短路径"
    for (i = 2; i <= n; i++) {  // 逐点求最短路径
        min = maxValue;
        k = 0;
        for (j = 2; j <= n; j++)
            if (!S[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        S[k] = 1;
        for (j = 2; j <= n; j++)
            if (!S[j] && G.Edge[k][j] < maxValue &&
                dist[k] + G.Edge[k][j] < dist[j]) {
                dist[j] = dist[k] + G.Edge[k][j];
                path[j] = k;
            }
    }
}

int main(void) {
    MGraph G;
    G.numVertices = Num - 1;
    G.numEdges = Num - 1;
    G.VerticesList[1] = "man, wolf, sheep, food | null";
    G.VerticesList[2] = "man, wolf, sheep | food";
    G.VerticesList[3] = "man, wolf, food | sheep";
    G.VerticesList[4] = "man, sheep, food | wolf";
    G.VerticesList[5] = "man, sheep | wolf, food";
    G.VerticesList[6] = "wolf, food | man, sheep";
    G.VerticesList[7] = "wolf | man, sheep, food";
    G.VerticesList[8] = "sheep | man, wolf, food";
    G.VerticesList[9] = "food | man, wolf, sheep";
    G.VerticesList[10] = "null | man, wolf, sheep, food";
    int i, j;
    int dist[Num], path[Num];
    for (i = 0; i <= G.numVertices; i++) {
        G.Edge[i][i] = 0;
        for (j = 0; j <= G.numVertices; j++)
            if (i != j) G.Edge[i][j] = maxValue;
    }
    G.Edge[1][6] = G.Edge[6][1] = G.Edge[2][7] = G.Edge[7][2] = G.Edge[2][8] = G.Edge[8][2] = 1;
    G.Edge[3][6] = G.Edge[6][3] = G.Edge[3][7] = G.Edge[7][3] = G.Edge[3][9] = G.Edge[9][3] = 1;
    G.Edge[4][8] = G.Edge[8][4] = G.Edge[4][9] = G.Edge[9][4] = G.Edge[5][8] = G.Edge[8][5] = 1;
    G.Edge[5][10] = G.Edge[10][5] = 1;
    Dijkstra1(G, dist, path);  // 计算最短路径
    printf("The shortest path length obtained is %d\n", dist[G.numVertices]);
    j = G.numVertices;
    i = j - 1;
    while (j) {
        dist[i--] = j;
        j = path[j];
    }  // 读出路径，存入dist
    printf("The shortest path is: \n");
    for (i = i + 1; i <= G.numVertices - 1; i++)
        printf("%d: %s\n", dist[i], G.VerticesList[dist[i]]);
}
