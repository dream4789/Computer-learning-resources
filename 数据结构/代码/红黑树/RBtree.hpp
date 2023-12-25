//
// Created by xulon on 2023/6/27.
//
#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 节点的颜色
// 我们可以使用 #define 定义常量，为什么非要使用枚举？ 枚举的优点
// 1. 增加代码的可读性和可维护性
// 2. 和#define定义的标识符比较枚举有类型检查，更加严谨
// 3. 防止了命名污染（封装）
// 4. 便于调试
// 5. 使用方便，一次可以定义多个常量
// 6. 这些可能取值都是有值的，默认从0开始，一次递增1，当然在定义的时候也可以赋初值
enum Color {
    RED, BLACK
};


// 红黑树节点的定义
template<class ValueType>
struct RBTreeNode {
    RBTreeNode(const ValueType &data = ValueType(), Color color = RED)
    //这里构造节点的时候颜色默认给为红色因为如果给为黑色就有可能会破坏当前红黑树的性质，导致每条路径的黑色节点个数不同
            : _Left(nullptr), _Right(nullptr), _Parent(nullptr), _data(data), _color(color) {}

    RBTreeNode<ValueType> *_Left; // 节点的左孩子
    RBTreeNode<ValueType> *_Right; // 节点的右孩子
    RBTreeNode<ValueType> *_Parent; // 节点的双亲(红黑树需要旋转，为了实现简单给出该字段)
    ValueType _data; // 节点的值域
    Color _color; // 节点的颜色
};

//红黑树迭代器：
template<class T, class Ref, class Ptr>
struct RBTree_iterator {
    typedef RBTreeNode<T> Node;
    typedef RBTree_iterator<T, Ref, Ptr> self;

    //构造函数就将红黑树的节点指针传入进来：
    RBTree_iterator(Node *node = nullptr)
            : _pnode(node) {}

    //迭代器解引用：
    Ref operator*() {
        return _pnode->_data;
    }

    Ptr operator->() {
        return (&operator*());
    }

    //迭代器加加:前置加加
    self operator++() {
        Increament();
        return *this;
    }

    self operator++(int) {
        self temp = *this;
        Increament();
        return temp;
    }

    self operator--() {
        Decreament();
        return *this;
    }

    self operator--(int) {
        self temp = *this;
        Decreament();
        return temp;
    }

    //将当前迭代器指针的值放到后面大的值上
    void Increament() {
        //如果当前迭代器存在右子树的时候我们将_pnode更新到右子树
        if (_pnode->_Right) {
            _pnode = _pnode->_Right;
            //去右子树中找最小的节点：
            while (_pnode->_Left) {
                _pnode = _pnode->_Left;
            }
        } else {
            Node *parent = _pnode->_Parent;
            while (parent->_Right == _pnode) {
                _pnode = parent;
                parent = _pnode->_Parent;
            }
            ///-->>>>>>>>>>>一定要注意下面的情况当红黑树没有右子树，那么当前的head节点的右就指向
            //红黑树的根那么此时如果将_pnode放在parent处那么就相当于将while循环中的做了无用功。
            if (_pnode->_Right != parent) {
                _pnode = parent;
            }
        }
    }

    void Decreament() {
        if (_pnode->_Parent->_Parent == _pnode &&
            _pnode->_color == RED) {//当前节点是head节点的时候那么我们就要找到当最右边节点也就是最大节点，而判断当前节点是否是最大的节点的时候
            //不可只有一个_pnode->_Parent->_Parent因为根节点也满足这个条件，因为我们将红黑树的head节点设为红色所以我们加上_color==RED
            _pnode = _pnode->_Right;
        } else if (_pnode->_Left) {//如果当前的pnode的左子树存在那么我们就将节点放在左子树
            _pnode = _pnode->_Left;
            while (_pnode->_Right) {
                _pnode = _pnode->_Right;
            }
        } else {
            Node *parent = _pnode->_Parent;
            //这里如果_pnode到了begin的位置就不可以再减了
            while (_pnode == parent->_Left) {
                _pnode = parent;
                parent = _pnode->_Parent;
            }
            _pnode = parent;
        }
    }

    bool operator==(const self &s) const {
        return _pnode == s._pnode;
    }

    bool operator!=(const self &s) const {
        return _pnode != s._pnode;
    }

    Node *_pnode;
};

template<class T, class Keyofvalue>
class RBtree {
    typedef RBTreeNode<T> Node;
public:

    typedef RBTree_iterator<T, T &, T *> RBiterator;
public:
    RBtree()
            : _head(new Node()), _size(0) {
        _head->_Left = _head;
        _head->_Right = _head;
    }

    //插入节点
    pair<RBiterator, bool> insert(const T &val) {
        Keyofvalue key;
        //先按照二叉搜索树的方式插入
        Node *new_node = nullptr;
        Node *&_root = get_root();
        if (_root == nullptr) {  // 为空树
            _root = new Node(val, RED);
            _root->_Parent = _head;
            new_node = _root;
            //_head->_Parent = _root;
        } else {//树非空
            Node *cur = _root;
            Node *parent = _head;
            while (cur) {
                parent = cur;
                if (key(val) < key(cur->_data)) {
                    cur = cur->_Left;
                } else if (key(val) > key(cur->_data)) {
                    cur = cur->_Right;
                } else {//我们这里不允许插入相同值域的节点
                    return make_pair(RBiterator(cur), false);
                }
            }
            cur = new Node(val);
            new_node = cur;
            if (key(val) < key(parent->_data)) {
                parent->_Left = cur;
            } else {
                parent->_Right = cur;
            }
            cur->_Parent = parent;
            //插入成功之后我们调整当前红黑树的节点：
            //这里我们在插入红黑树中调整的时候只有当第一中情况才继续向上更新节点，那么我们只要考虑第一中情况的终止条件即可
            //第一中情况中如果parent为红色节点那么当前节点就需要继续向上更新，但是我们将head节点也设为红色那么当我们parent
            //节点更新到head节点那么当前也就不更新了
            while (parent != _head && parent->_color == RED) {
                //插入节点双亲为黑色：
                if (parent->_color == BLACK) {
                    break;
                } else { // 插入节点双亲为红色
                    Node *grandparent = parent->_Parent;//这里如果双亲的节点是红色那么双亲一定是有双亲节点的
                    if (parent == grandparent->_Left) {//第一大类插入节点在红黑树的左子树：
                        Node *uncle = grandparent->_Right;//当前节点的叔叔节点
                        if (uncle && uncle->_color == RED) {//第一种情况：叔叔节点存在而且为红色：
                            parent->_color = BLACK;
                            uncle->_color = BLACK;
                            grandparent->_color = RED;
                            cur = grandparent;
                            parent = cur->_Parent;
                        } else {//第二三种情况：
                            //因为我们要将第三种情况转化为第二种情况处理所以我们先写第三种情况：cur插在内侧
                            if (cur == parent->_Right) {
                                rotate_left(parent);
                                std::swap(parent, cur);
                            }
                            //第二种情况：先将parent和grandparent颜色互换然后右旋
                            parent->_color = BLACK;
                            grandparent->_color = RED;
                            rotate_right(grandparent);
                        }
                    } else {//第二大类插入节点在红黑树的右子树：
                        Node *uncle = grandparent->_Left;//当前节点的叔叔节点
                        if (uncle && uncle->_color == RED) {//第一种情况：叔叔节点存在而且为红色：
                            parent->_color = BLACK;
                            uncle->_color = BLACK;
                            grandparent->_color = RED;
                            cur = grandparent;
                            parent = cur->_Parent;
                        } else {//第二三种情况：
                            //因为我们要将第三种情况转化为第二种情况处理所以我们先写第三种情况：cur插在内侧
                            if (cur == parent->_Left) {
                                rotate_right(parent);
                                std::swap(parent, cur);
                            }
                            //第二种情况：先将parent和grandparent颜色互换然后右旋
                            parent->_color = BLACK;
                            grandparent->_color = RED;
                            rotate_left(grandparent);
                        }
                    }
                }
            }

        }
        _root->_color = BLACK;
        _head->_Left = get_mostleftnode();
        _head->_Right = get_mostrightnode();
        return make_pair(RBiterator(new_node), true);
    }

    // 这里的销毁节点一定要传&因为因为下面要修改root=nullptr的时候要将指针所指向的地址修改为nullptr不然如果后面再调用destroy的时候
    // 其实root所指向的地址并没有指向nullptr所以就有可能出错。
    void Destroy(Node *&root) {
        if (root) {
            Destroy(root->_Left);
            Destroy(root->_Right);
            delete root;
            root = nullptr;
        }

    }

    void Clear() {
        Destroy(get_root());
        _size = 0;
    }

    ~RBtree() {
        Destroy(get_root());
        delete _head;
    }

    // 查找方法
    RBiterator Find(T value) {
        Keyofvalue key;
        Node *cur = get_root();
        while (cur) {
            if (key(cur->_data) < key(value)) {
                cur = cur->_Right;
            } else if (key(cur->_data) > key(value)) {
                cur = cur->_Left;
            } else {
                return RBiterator(cur);
            }
        }
        return End();
    }

    RBiterator End() {
        return RBiterator(_head);
    }

    RBiterator Begin() {
        return RBiterator(_head->_Left);
    }

    size_t Size() const {
        return _size;
    }

    bool Empty() const {
        return _size == 0;
    }

    // 中序遍历
    void inoder() {
        cout << "中序遍历结果为：";
        Node *_root = get_root();
        mid(_root);
        cout << endl;
    }

    // 判断当前树是否是红黑树
    bool isRBtree() {
        Node *root = get_root();
        if (root == nullptr) {
            return true;
        }
        //判断根节点是否是黑色节点：
        if (root->_color == RED) {
            return false;
        }
        //判断每条路径中黑色节点个数是否相同
        size_t black_count = 0;
        Node *cur = root;
        while (cur) {
            if (cur->_color == BLACK) {
                black_count++;
            }
            cur = cur->_Left;
        }
        int k = 0;
        return _isRBtree(black_count, k, root);
    }

    //判断红黑树中是否满足性质三（两个红色节点不挨在一起）性质四（每条路径中黑色节点树相同）
    bool _isRBtree(size_t black_count, int k, Node *root) {
        if (root == nullptr) {
            if (k != black_count) {
                cout << "当前树不是红黑树，有一条路径黑色节点个数为：" << k << "少于路径节点：" << black_count << endl;
                return false;

            }
            return true;
        }
        if (root->_color == BLACK) {
            k++;
        } else {
            if (root->_Parent->_color == RED) {
                cout << "当前树不是红黑树,有两个红色节点挨在一起。" << endl;
                return false;
            }
        }
        return _isRBtree(black_count, k, root->_Left) && _isRBtree(black_count, k, root->_Right);
    }

    void Swap(RBtree<T, Keyofvalue> _t) {
        std::swap(_head, _t._head);
    }

private:
    //中序遍历：
    void mid(Node *root) {
        if (root) {
            mid(root->_Left);
            cout << root->_data << " ";
            mid(root->_Right);
        }
    }

    //这里因为我们红黑树中没有设置根节点在代码实现的时候不容易理解所以这里我们写一个私有函数返回红黑树的根节点：
    Node *&get_root() {
        return _head->_Parent;
    }

    //获取最左侧节点也就是最小节点：
    Node *get_mostleftnode() {
        Node *_root = get_root();
        if (_root) {
            while (_root->_Left) {
                _root = _root->_Left;
            }
        }
        return _root;
    }

    //获取最右侧节点也就是最大节点：
    Node *get_mostrightnode() {
        Node *_root = get_root();
        if (_root) {
            while (_root->_Right) {
                _root = _root->_Right;
            }
        }
        return _root;
    }

    //左单旋
    void rotate_left(Node *parent) {
        Node *pparent = parent->_Parent;
        Node *subR = parent->_Right;
        Node *subRL = subR->_Left;
        parent->_Right = subRL;
        //更新subRL的双亲：
        if (subRL) {
            subRL->_Parent = parent;
        }
        subR->_Left = parent;
        parent->_Parent = subR;
        subR->_Parent = pparent;
        if (pparent == _head) {//--->>>>一定要注意这里的pparent如果是头节点那么一定要将pparent的指向为subR
            _head->_Parent = subR;
        }
        if (pparent) {
            if (pparent->_Left == parent) {
                pparent->_Left = subR;
            } else {
                pparent->_Right = subR;
            }
        }
    }

    //右单旋
    void rotate_right(Node *parent) {
        Node *subL = parent->_Left;
        Node *subLR = subL->_Right;
        Node *pparent = parent->_Parent;
        parent->_Left = subLR;
        //如果subLR存在那么将其父节点更新
        if (subLR) {
            subLR->_Parent = parent;
        }
        //将parent右旋下来：
        subL->_Right = parent;
        //parent旋下来就要更新parent的父节点
        parent->_Parent = subL;
        //此时subL就要更新父节点
        subL->_Parent = pparent;
        if (pparent == _head) {
            _head->_Parent = subL;
        }
        if (pparent) {
            if (parent == pparent->_Right) {
                pparent->_Right = subL;
            } else {
                pparent->_Left = subL;
            }
        }
    }

private:
    size_t _size;
    Node *_head;
};