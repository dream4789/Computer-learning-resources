//
// Created by xulon on 2023/6/27.
//
#pragma once

#include"RBtree.hpp"

//���������ŵļ�ֵ��
namespace wbx {
    template<class K, class V>
    class map {
    public:

        typedef pair<K, V> valuetype;

        //��������Ϊ���Ǻ�����д�ŵ��Ǽ�ֵ�ԣ������Ǻ������ʵ�ֵ�ʱ��ֻ��һ��ģ�����Ͳ�����
        //Ҳ��������Ҫ����ں�����еĽڵ㣬�����ǵ�map����pair����ֵ������Žڵ�ģ����ǱȽ�
        //��ʱ��������ͨ��pair�е�keyֵ���Ƚϵģ��������������Ҫ����һ��������������map��Ҫ
        //�Ƚϵ����͡�
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

        //����map��operator[]����ʵ�ֵ�ʱ��ֱ����insert��ʵ�֣����������ں������ʵ��insert��ʱ��
        //�ǲ����������ͬ��Ԫ�صģ�������������operator[]�����һ���µ�keyֵ��ô���Ǿͽ���ֱ��
        //�����������һ��ԭ�е�keyֵ��ô������е�inset����ͻὫ���ĵ�����������ô�������ｫ
        //���صĵ����������õõ�����valueֵ��������ô�ҾͿ��Զ�������޸�
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