#include <stdio.h>
#include <stdlib.h>

// 扩展性更高

#define INF 99999 // 定义一个无限大的值

void dijkstra(int n, int start, int *graph, int *dist);

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
    int *dist = (int *)malloc(n * sizeof(int));
    dijkstra(n, 0, (int *)graph, dist); // 从节点0开始
    free(dist);

    dist = (int *)malloc(n * sizeof(int));
    dijkstra(n, 0, (int *)graph1, dist); // 从节点0开始
    free(dist);

    return 0;
}

void dijkstra(int n, int start, int *graph, int *dist) {
    int visited[n]; // 标记是否已经访问过
    for(int i=0; i<n; i++) {
        dist[i] = INF; // 初始化距离值为无穷大
        visited[i] = 0;
    }
    dist[start] = 0; // 起点到自身的距离为0
    for(int i=0; i<n; i++) {
        int minDist = INF;
        int minIndex = -1;
        for(int j=0; j<n; j++) { // 找出尚未访问的距离最小的节点
            if(!visited[j] && dist[j]<minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1; // 标记为已访问节点
        for(int j=0; j<n; j++) { // 更新距离值
            if(!visited[j] && *(graph + minIndex * n + j)!=INF) {
                int newDist = dist[minIndex] + *(graph + minIndex * n + j);
                if(newDist < dist[j]) {
                    dist[j] = newDist;
                }
            }
        }
    }
    printf("The shortest distance from the starting point to each point:\n");
    for(int i=0; i<n; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");
}
