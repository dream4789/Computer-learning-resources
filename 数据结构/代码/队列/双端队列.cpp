//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <deque>

using namespace std;

int main() {
    // ����һ�� int ���͵�˫�˶���
    deque<int> dq;

    // �ڶ��׺Ͷ�β����Ԫ��
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(3);

    // ѭ��ȡ�������е�Ԫ�ز����
    while (!dq.empty()) {
        cout << dq.front() << " ";  // ȡ������Ԫ��
        dq.pop_front();             // ɾ������Ԫ��
    }

    return 0;
}