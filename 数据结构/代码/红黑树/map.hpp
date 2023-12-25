//
// Created by xulon on 2023/6/27.
//
#pragma once

#include"RBtree.hpp"

//红黑树里面放的键值对
namespace wbx {
    template<class K, class V>
    class map {
    public:

        typedef pair<K, V> valuetype;

        //这里是因为我们红黑树中存放的是键值对，而我们红黑树在实现的时候只有一个模板类型参数，
        //也就是我们要存放在红黑树中的节点，而我们的map是用pair（键值对来存放节点的）但是比较
        //的时候我们是通过pair中的key值来比较的，所以我们这里就要定义一个类来返回我们map中要
        //比较的类型。
        struct Keyofvalue {
            const K &operator()(const valuetype &value) {
                return value.first;
            }
        };

        typedef RBtree<valuetype, Keyofvalue> Tree;
        typedef typename Tree::RBiterator iterator;

        map()
                : _t() {}

        iterator begin() {
            return _t.Begin();
        }

        iterator end() {
            return _t.End();
        }

        size_t size() const {
            return _t.Size();
        }

        size_t empty() const {
            return _t.Empty();
        }

        //这里map的operator[]我们实现的时候直接用insert来实现，这里我们在红黑树中实现insert的时候
        //是不允许插入相同的元素的，所以这里我们operator[]如果是一个新的key值那么我们就将其直接
        //插入了如果是一个原有的key值那么红黑树中的inset插入就会将它的迭代器返回那么我们这里将
        //返回的迭代器解引用得到它的value值的引用那么我就可以对其进行修改
        V &operator[](const K &key) {
            return (*(_t.insert(make_pair(key, V())).first)).second;
        }

        pair<iterator, bool> insert(const valuetype &val) {
            return _t.insert(val);
        }

        void swap(map<K, V> &m) {
            _t.Swap(m._t);
        }

        void clear() {
            _t.Clear();
        }

        iterator find(const K &key) {
            return _t.Find(make_pair(key, V()));
        }

    private:
        Tree _t;
    };
};