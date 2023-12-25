
//
// Created by xulon on 2023/6/23.
//
#include <stdio.h>

#define INF 999999

void floyd(int n, int graph[][n], int dist[][n]) {
    // 初始化距离矩阵，即 dist[i][j] 表示从 i 到 j 的最短路径长度
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = (i == j) ? 0 : graph[i][j];
        }
    }

    // 使用 Floyd 算法计算最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int graph[5][5] = {
            {0  , 3  , INF, 7  , INF},
            {3  , 0  , 4  , 2  , INF},
            {INF, 4  , 0  , 5  , 6  },
            {7  , 2  , 5  , 0  , 4  },
            {INF, INF, 6  , 4  , 0  }
    };
    int graph1[5][5] = {
            {0  , 5  , INF, INF, 4  },
            {INF, 0  , 3  , 6  , INF},
            {5  , INF, 0  , INF, INF},
            {7  , INF, 2  , 0  , INF},
            {INF, INF, INF, 3  , 0  }
    };
    int n = 5;
    int dist[n][n];

    floyd(n, graph, dist);

    // 输出最短路径矩阵
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}
