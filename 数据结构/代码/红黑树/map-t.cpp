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
    // 插入一些键值对
    cout << "Inserting elements into the map...\n";
    m.insert(make_pair(1, "one"));
    m.insert(make_pair(2, "two"));
    m.insert(make_pair(3, "three"));
    m.insert(make_pair(4, "four"));
    m.insert(make_pair(5, "five"));

    // 输出插入结果和 map 中所有的键值对
    cout << "Printing all the elements of the map:\n";
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        cout << iter->first << ": " << iter->second << endl;
    }

    // test operator[]
    // 读取一个已经存在和不存在的 key 对应的 value 值
    cout << "\nTesting the [] operator...\n";
    cout << "m[1] = " << m[1] << endl;
    cout << "m[6] = " << m[6] << endl;

    // test find
    // 分别查找一个已经存在和不存在的 key
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
    // 清空 map 中的所有元素，并输出清空后 map 中的元素个数
    cout << "\nClearing the map...\n";
    m.clear();
    cout << "Map size after clearing: " << m.size() << endl;

    // test swap
    // 创建两个 map 对象，分别插入不同的键值对，然后交换它们的内容，并输出交换后两个 map 中的元素
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
    // 测试 end、begin 和 size 函数，输出 end 迭代器、begin 迭代器和 map 的大小
    cout << "\nPrinting information about the map:\n";
    cout << "Size of the map: " << m.size() << endl;
    cout << "Iterator to the beginning of the map: " << m.begin()->first << "->" << m.begin()->second << endl;
    --m.end();
    cout << "Iterator to the end of the map: " << m.end()->first << "->" << m.end()->second << endl;

    return 0;
}