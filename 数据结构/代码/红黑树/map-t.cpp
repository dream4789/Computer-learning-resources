//
// Created by xulon on 2023/6/27.
//
#include <iostream>
#include "map.hpp"

using namespace std;
using namespace wbx;

int main() {
    map<int, string> m;

    // test insert
    // ����һЩ��ֵ��
    cout << "Inserting elements into the map...\n";
    m.insert(make_pair(1, "one"));
    m.insert(make_pair(2, "two"));
    m.insert(make_pair(3, "three"));
    m.insert(make_pair(4, "four"));
    m.insert(make_pair(5, "five"));

    // ����������� map �����еļ�ֵ��
    cout << "Printing all the elements of the map:\n";
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        cout << iter->first << ": " << iter->second << endl;
    }

    // test operator[]
    // ��ȡһ���Ѿ����ںͲ����ڵ� key ��Ӧ�� value ֵ
    cout << "\nTesting the [] operator...\n";
    cout << "m[1] = " << m[1] << endl;
    cout << "m[6] = " << m[6] << endl;

    // test find
    // �ֱ����һ���Ѿ����ںͲ����ڵ� key
    cout << "\nTesting the find function...\n";
    auto iter = m.find(3);
    if (iter != m.end()) {
        cout << "Element found: " << iter->first << "->" << iter->second << endl;
    } else {
        cout << "Element not found\n";
    }

    iter = m.find(6);
    if (iter != m.end()) {
        cout << "Element found: " << iter->first << "->" << iter->second << endl;
    } else {
        cout << "Element not found\n";
    }

    // test clear
    // ��� map �е�����Ԫ�أ��������պ� map �е�Ԫ�ظ���
    cout << "\nClearing the map...\n";
    m.clear();
    cout << "Map size after clearing: " << m.size() << endl;

    // test swap
    // �������� map ���󣬷ֱ���벻ͬ�ļ�ֵ�ԣ�Ȼ�󽻻����ǵ����ݣ���������������� map �е�Ԫ��
    cout << "\nTesting the swap function...\n";
    map<int, string> m2;
    m2.insert(make_pair(10, "ten"));
    m2.insert(make_pair(11, "eleven"));
    m.swap(m2);

    cout << "Printing elements of m after swap:\n";
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        cout << iter->first << ": " << iter->second << endl;
    }

    cout << "\nPrinting elements of m2 after swap:\n";
    for (auto iter = m2.begin(); iter != m2.end(); ++iter) {
        cout << iter->first << ": " << iter->second << endl;
    }

    // test end, begin, and size
    // ���� end��begin �� size ��������� end ��������begin �������� map �Ĵ�С
    cout << "\nPrinting information about the map:\n";
    cout << "Size of the map: " << m.size() << endl;
    cout << "Iterator to the beginning of the map: " << m.begin()->first << "->" << m.begin()->second << endl;
    --m.end();
    cout << "Iterator to the end of the map: " << m.end()->first << "->" << m.end()->second << endl;

    return 0;
}