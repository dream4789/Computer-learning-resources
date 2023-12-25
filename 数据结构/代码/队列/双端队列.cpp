//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <deque>

using namespace std;

int main() {
    // 定义一个 int 类型的双端队列
    deque<int> dq;

    // 在队首和队尾插入元素
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(3);

    // 循环取出队列中的元素并输出
    while (!dq.empty()) {
        cout << dq.front() << " ";  // 取出队首元素
        dq.pop_front();             // 删除队首元素
    }

    return 0;
}