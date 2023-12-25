//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 定义一个 int 类型的队列
    queue<int> q;

    // 插入元素到队尾
    q.push(1);
    q.push(2);
    q.push(3);

    // 循环取出队首元素并输出
    while (!q.empty()) {
        cout << q.front() << " ";  // 取出队首元素
        q.pop();                   // 删除队首元素
    }

    return 0;
}

// 1 2 3