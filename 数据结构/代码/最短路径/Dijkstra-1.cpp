// The shortest distance from the starting point to each point:
// 0 3 7 5 9

#include <stdio.h>
#define INF 99999 // 定义一个无限大的值

void dijkstra(int graph[5][5], int start);

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
    dijkstra(graph, 0); // 从节点0开始
    dijkstra(graph1, 0); // 从节点0开始
    return 0;
}

void dijkstra(int graph[5][5], int start) {
    int dist[5]; // 存储起点到各个点的最短距离
    int visited[5] = {0}; // 标记是否已经访问过
    for(int i=0; i<5; i++) {
        dist[i] = INF; // 初始化距离值为无穷大
    }
    dist[start] = 0; // 起点到自身的距离为0
    for(int i=0; i<5; i++) {
        int minDist = INF;
        int minIndex = -1;
        for(int j=0; j<5; j++) { // 找出尚未访问的距离最小的节点
            if(!visited[j] && dist[j]<minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1; // 标记为已访问节点
        for(int j=0; j<5; j++) { // 更新距离值
            if(!visited[j] && graph[minIndex][j]!=INF) {
                int newDist = dist[minIndex] + graph[minIndex][j];
                if(newDist < dist[j]) {
                    dist[j] = newDist;
                }
            }
        }
    }
    printf("The shortest distance from the starting point to each point:\n");
    for(int i=0; i<5; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");
}