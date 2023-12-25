//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <queue>

using namespace std;

int main() {
    // ����һ�� int ���͵����ȶ��У�Ĭ���Ǵ����
    priority_queue<int> pq;

    // ����Ԫ�ص����ȶ�����
    pq.push(3);
    pq.push(1);
    pq.push(4);
    pq.push(1);  // ͬ����Ԫ�ؿ��Բ�����

    // ѭ��ȡ���Ѷ�Ԫ�ز����
    while (!pq.empty()) {
        cout << pq.top() << " ";  // ȡ���Ѷ�Ԫ�أ������ȼ���ߵ�Ԫ��
        pq.pop();                 // ɾ���Ѷ�Ԫ��
    }

    return 0;
}

// 4 3 1 1