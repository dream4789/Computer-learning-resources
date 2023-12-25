//
// Created by xulon on 2023/6/27.
//
#include<iostream>
#include<vector>
#include<string>

using namespace std;

// �ڵ����ɫ
// ���ǿ���ʹ�� #define ���峣����Ϊʲô��Ҫʹ��ö�٣� ö�ٵ��ŵ�
// 1. ���Ӵ���Ŀɶ��ԺͿ�ά����
// 2. ��#define����ı�ʶ���Ƚ�ö�������ͼ�飬�����Ͻ�
// 3. ��ֹ��������Ⱦ����װ��
// 4. ���ڵ���
// 5. ʹ�÷��㣬һ�ο��Զ���������
// 6. ��Щ����ȡֵ������ֵ�ģ�Ĭ�ϴ�0��ʼ��һ�ε���1����Ȼ�ڶ����ʱ��Ҳ���Ը���ֵ
enum Color {
    RED, BLACK
};


// ������ڵ�Ķ���
template<class ValueType>
struct RBTreeNode {
    RBTreeNode(const ValueType &data = ValueType(), Color color = RED)
    //���ﹹ��ڵ��ʱ����ɫĬ�ϸ�Ϊ��ɫ��Ϊ�����Ϊ��ɫ���п��ܻ��ƻ���ǰ����������ʣ�����ÿ��·���ĺ�ɫ�ڵ������ͬ
            : _Left(nullptr), _Right(nullptr), _Parent(nullptr), _data(data), _color(color) {}

    RBTreeNode<ValueType> *_Left; // �ڵ������
    RBTreeNode<ValueType> *_Right; // �ڵ���Һ���
    RBTreeNode<ValueType> *_Parent; // �ڵ��˫��(�������Ҫ��ת��Ϊ��ʵ�ּ򵥸������ֶ�)
    ValueType _data; // �ڵ��ֵ��
    Color _color; // �ڵ����ɫ
};

//�������������
template<class T, class Ref, class Ptr>
struct RBTree_iterator {
    typedef RBTreeNode<T> Node;
    typedef RBTree_iterator<T, Ref, Ptr> self;

    //���캯���ͽ�������Ľڵ�ָ�봫�������
    RBTree_iterator(Node *node = nullptr)
            : _pnode(node) {}

    //�����������ã�
    Ref operator*() {
        return _pnode->_data;
    }

    Ptr operator->() {
        return (&operator*());
    }

    //�������Ӽ�:ǰ�üӼ�
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

    //����ǰ������ָ���ֵ�ŵ�������ֵ��
    void Increament() {
        //�����ǰ������������������ʱ�����ǽ�_pnode���µ�������
        if (_pnode->_Right) {
            _pnode = _pnode->_Right;
            //ȥ������������С�Ľڵ㣺
            while (_pnode->_Left) {
                _pnode = _pnode->_Left;
            }
        } else {
            Node *parent = _pnode->_Parent;
            while (parent->_Right == _pnode) {
                _pnode = parent;
                parent = _pnode->_Parent;
            }
            ///-->>>>>>>>>>>һ��Ҫע�����������������û������������ô��ǰ��head�ڵ���Ҿ�ָ��
            //������ĸ���ô��ʱ�����_pnode����parent����ô���൱�ڽ�whileѭ���е��������ù���
            if (_pnode->_Right != parent) {
                _pnode = parent;
            }
        }
    }

    void Decreament() {
        if (_pnode->_Parent->_Parent == _pnode &&
            _pnode->_color == RED) {//��ǰ�ڵ���head�ڵ��ʱ����ô���Ǿ�Ҫ�ҵ������ұ߽ڵ�Ҳ�������ڵ㣬���жϵ�ǰ�ڵ��Ƿ������Ľڵ��ʱ��
            //����ֻ��һ��_pnode->_Parent->_Parent��Ϊ���ڵ�Ҳ���������������Ϊ���ǽ��������head�ڵ���Ϊ��ɫ�������Ǽ���_color==RED
            _pnode = _pnode->_Right;
        } else if (_pnode->_Left) {//�����ǰ��pnode��������������ô���Ǿͽ��ڵ����������
            _pnode = _pnode->_Left;
            while (_pnode->_Right) {
                _pnode = _pnode->_Right;
            }
        } else {
            Node *parent = _pnode->_Parent;
            //�������_pnode����begin��λ�þͲ������ټ���
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

    //����ڵ�
    pair<RBiterator, bool> insert(const T &val) {
        Keyofvalue key;
        //�Ȱ��ն����������ķ�ʽ����
        Node *new_node = nullptr;
        Node *&_root = get_root();
        if (_root == nullptr) {  // Ϊ����
            _root = new Node(val, RED);
            _root->_Parent = _head;
            new_node = _root;
            //_head->_Parent = _root;
        } else {//���ǿ�
            Node *cur = _root;
            Node *parent = _head;
            while (cur) {
                parent = cur;
                if (key(val) < key(cur->_data)) {
                    cur = cur->_Left;
                } else if (key(val) > key(cur->_data)) {
                    cur = cur->_Right;
                } else {//�������ﲻ���������ֵͬ��Ľڵ�
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
            //����ɹ�֮�����ǵ�����ǰ������Ľڵ㣺
            //���������ڲ��������е�����ʱ��ֻ�е���һ������ż������ϸ��½ڵ㣬��ô����ֻҪ���ǵ�һ���������ֹ��������
            //��һ����������parentΪ��ɫ�ڵ���ô��ǰ�ڵ����Ҫ�������ϸ��£��������ǽ�head�ڵ�Ҳ��Ϊ��ɫ��ô������parent
            //�ڵ���µ�head�ڵ���ô��ǰҲ�Ͳ�������
            while (parent != _head && parent->_color == RED) {
                //����ڵ�˫��Ϊ��ɫ��
                if (parent->_color == BLACK) {
                    break;
                } else { // ����ڵ�˫��Ϊ��ɫ
                    Node *grandparent = parent->_Parent;//�������˫�׵Ľڵ��Ǻ�ɫ��ô˫��һ������˫�׽ڵ��
                    if (parent == grandparent->_Left) {//��һ�������ڵ��ں��������������
                        Node *uncle = grandparent->_Right;//��ǰ�ڵ������ڵ�
                        if (uncle && uncle->_color == RED) {//��һ�����������ڵ���ڶ���Ϊ��ɫ��
                            parent->_color = BLACK;
                            uncle->_color = BLACK;
                            grandparent->_color = RED;
                            cur = grandparent;
                            parent = cur->_Parent;
                        } else {//�ڶ����������
                            //��Ϊ����Ҫ�����������ת��Ϊ�ڶ��������������������д�����������cur�����ڲ�
                            if (cur == parent->_Right) {
                                rotate_left(parent);
                                std::swap(parent, cur);
                            }
                            //�ڶ���������Ƚ�parent��grandparent��ɫ����Ȼ������
                            parent->_color = BLACK;
                            grandparent->_color = RED;
                            rotate_right(grandparent);
                        }
                    } else {//�ڶ��������ڵ��ں��������������
                        Node *uncle = grandparent->_Left;//��ǰ�ڵ������ڵ�
                        if (uncle && uncle->_color == RED) {//��һ�����������ڵ���ڶ���Ϊ��ɫ��
                            parent->_color = BLACK;
                            uncle->_color = BLACK;
                            grandparent->_color = RED;
                            cur = grandparent;
                            parent = cur->_Parent;
                        } else {//�ڶ����������
                            //��Ϊ����Ҫ�����������ת��Ϊ�ڶ��������������������д�����������cur�����ڲ�
                            if (cur == parent->_Left) {
                                rotate_right(parent);
                                std::swap(parent, cur);
                            }
                            //�ڶ���������Ƚ�parent��grandparent��ɫ����Ȼ������
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

    // ��������ٽڵ�һ��Ҫ��&��Ϊ��Ϊ����Ҫ�޸�root=nullptr��ʱ��Ҫ��ָ����ָ��ĵ�ַ�޸�Ϊnullptr��Ȼ��������ٵ���destroy��ʱ��
    // ��ʵroot��ָ��ĵ�ַ��û��ָ��nullptr���Ծ��п��ܳ���
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

    // ���ҷ���
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

    // �������
    void inoder() {
        cout << "����������Ϊ��";
        Node *_root = get_root();
        mid(_root);
        cout << endl;
    }

    // �жϵ�ǰ���Ƿ��Ǻ����
    bool isRBtree() {
        Node *root = get_root();
        if (root == nullptr) {
            return true;
        }
        //�жϸ��ڵ��Ƿ��Ǻ�ɫ�ڵ㣺
        if (root->_color == RED) {
            return false;
        }
        //�ж�ÿ��·���к�ɫ�ڵ�����Ƿ���ͬ
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

    //�жϺ�������Ƿ�������������������ɫ�ڵ㲻����һ�������ģ�ÿ��·���к�ɫ�ڵ�����ͬ��
    bool _isRBtree(size_t black_count, int k, Node *root) {
        if (root == nullptr) {
            if (k != black_count) {
                cout << "��ǰ�����Ǻ��������һ��·����ɫ�ڵ����Ϊ��" << k << "����·���ڵ㣺" << black_count << endl;
                return false;

            }
            return true;
        }
        if (root->_color == BLACK) {
            k++;
        } else {
            if (root->_Parent->_color == RED) {
                cout << "��ǰ�����Ǻ����,��������ɫ�ڵ㰤��һ��" << endl;
                return false;
            }
        }
        return _isRBtree(black_count, k, root->_Left) && _isRBtree(black_count, k, root->_Right);
    }

    void Swap(RBtree<T, Keyofvalue> _t) {
        std::swap(_head, _t._head);
    }

private:
    //���������
    void mid(Node *root) {
        if (root) {
            mid(root->_Left);
            cout << root->_data << " ";
            mid(root->_Right);
        }
    }

    //������Ϊ���Ǻ������û�����ø��ڵ��ڴ���ʵ�ֵ�ʱ���������������������дһ��˽�к������غ�����ĸ��ڵ㣺
    Node *&get_root() {
        return _head->_Parent;
    }

    //��ȡ�����ڵ�Ҳ������С�ڵ㣺
    Node *get_mostleftnode() {
        Node *_root = get_root();
        if (_root) {
            while (_root->_Left) {
                _root = _root->_Left;
            }
        }
        return _root;
    }

    //��ȡ���Ҳ�ڵ�Ҳ�������ڵ㣺
    Node *get_mostrightnode() {
        Node *_root = get_root();
        if (_root) {
            while (_root->_Right) {
                _root = _root->_Right;
            }
        }
        return _root;
    }

    //����
    void rotate_left(Node *parent) {
        Node *pparent = parent->_Parent;
        Node *subR = parent->_Right;
        Node *subRL = subR->_Left;
        parent->_Right = subRL;
        //����subRL��˫�ף�
        if (subRL) {
            subRL->_Parent = parent;
        }
        subR->_Left = parent;
        parent->_Parent = subR;
        subR->_Parent = pparent;
        if (pparent == _head) {//--->>>>һ��Ҫע�������pparent�����ͷ�ڵ���ôһ��Ҫ��pparent��ָ��ΪsubR
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

    //�ҵ���
    void rotate_right(Node *parent) {
        Node *subL = parent->_Left;
        Node *subLR = subL->_Right;
        Node *pparent = parent->_Parent;
        parent->_Left = subLR;
        //���subLR������ô���丸�ڵ����
        if (subLR) {
            subLR->_Parent = parent;
        }
        //��parent����������
        subL->_Right = parent;
        //parent��������Ҫ����parent�ĸ��ڵ�
        parent->_Parent = subL;
        //��ʱsubL��Ҫ���¸��ڵ�
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