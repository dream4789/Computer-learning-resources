//
// Created by xulon on 2023/6/27.
//
#pragma once

#include"RBtree.hpp"

//红黑树里面放的键值对
namespace wbx {
    template<class K>
    class set {
    public:

        typedef K valuetype;

        struct Keyofvalue {
            const K &operator()(const valuetype &value) {
                return value;
            }
        };

        typedef RBtree<valuetype, Keyofvalue> Tree;
        typedef typename Tree::RBiterator iterator;

        set()
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

        pair<iterator, bool> insert(const valuetype &val) {
            return _t.insert(val);
        }

        void swap(set<K> &s) {
            _t.Swap(s._t);
        }

        void clear() {
            _t.Clear();
        }

        iterator find(const valuetype &key) {
            return _t.Find(key);
        }

    private:
        Tree _t;
    };
};