//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <queue>

using namespace std;

int main() {
    // ����һ�� int ���͵Ķ���
    queue<int> q;

    // ����Ԫ�ص���β
    q.push(1);
    q.push(2);
    q.push(3);

    // ѭ��ȡ������Ԫ�ز����
    while (!q.empty()) {
        cout << q.front() << " ";  // ȡ������Ԫ��
        q.pop();                   // ɾ������Ԫ��
    }

    return 0;
}

// 1 2 3