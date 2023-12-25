//
// Created by xulon on 2023/6/27.
//
#include <iostream>
#include "set.hpp"

using namespace std;
using namespace wbx;

int main() {
    set<int> s;

    // test insert
    cout << "Inserting elements into the set...\n";
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);

    cout << "Printing all the elements of the set:\n";
    for (auto iter = s.begin(); iter != s.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    // test find
    cout << "\nTesting the find function...\n";
    auto iter = s.find(3);
    if (iter != s.end()) {
        cout << "Element found: " << *iter << endl;
    } else {
        cout << "Element not found\n";
    }

    iter = s.find(6);
    if (iter != s.end()) {
        cout << "Element found: " << *iter << endl;
    } else {
        cout << "Element not found\n";
    }

    // test clear
    cout << "\nClearing the set...\n";
    s.clear();
    cout << "Set size after clearing: " << s.size() << endl;

    // test swap
    cout << "\nTesting the swap function...\n";
    set<int> s2;
    s2.insert(10);
    s2.insert(11);
    s.swap(s2);  // s2中元素移到了s中

    cout << "Printing elements of s after swap:\n";
    for (auto iter = s.begin(); iter != s.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    cout << "\nPrinting elements of s2 after swap:\n";
    for (auto iter = s2.begin(); iter != s2.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    // test end, begin, and size
    cout << "\nPrinting information about the set:\n";
    cout << "Size of the set: " << s.size() << endl;
    cout << "Iterator to the beginning of the set: " << *(s.begin()) << endl;
    --s.end();
    cout << "Iterator to the end of the set: " << *(s.end()) << endl;

    return 0;
}
