//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 定义一个 int 类型的优先队列，默认是大根堆
    priority_queue<int> pq;

    // 插入元素到优先队列中
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);  // 同样的元素可以插入多次

    // 循环取出堆顶元素并输出
    while (!pq.empty()) {
        cout << pq.top() << " ";  // 取出堆顶元素，即优先级最高的元素
        pq.pop();                 // 删除堆顶元素
    }

    return 0;
}

// 4 3 1 1