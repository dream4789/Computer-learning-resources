#include <stdio.h>

#define INF 999999

void floyd(int n, int *graph, int *dist) {
    // 初始化距离矩阵，即 dist[i][j] 表示从 i 到 j 的最短路径长度
    for (int i = 0; i < n * n; i++) {
        dist[i] = graph[i];
    }

    // 使用 Floyd 算法计算最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (*(dist + i * n + k) + *(dist + k * n + j) < *(dist + i * n + j)) {
                    *(dist + i * n + j) = *(dist + i * n + k) + *(dist + k * n + j);
                }
            }
        }
    }
}

int main() {
    int n = 5;
    int dist[n][n];

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

    floyd(n, (int *)graph, (int *)dist);
    // 输出最短路径矩阵
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }

    floyd(n, (int *)graph1, (int *)dist);
    // 输出最短路径矩阵
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }

    int graph2[4][4] = {
            {0  , INF, 3  , INF},
            {2  , 0  , INF, INF},
            {INF, 7  , 0  , 1  },
            {6  , INF, INF, 0  }
    };

    n = 4;
    int dist1[4][4];
    floyd(n, (int *)graph2, (int *)dist1);
    // 输出最短路径矩阵
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", dist1[i][j]);
        }
        printf("\n");
    }

    return 0;
}
/*

Shortest path matrix:
  0   3   7   5   9
  3   0   4   2   6
  7   4   0   5   6
  5   2   5   0   4
  9   6   6   4   0
Shortest path matrix:
  0   5   8   7   4
  8   0   3   6  12
  5  10   0  12   9
  7  12   2   0  11
 10  15   5   3   0

 */