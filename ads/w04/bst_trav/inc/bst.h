#ifndef BST_H
#define BST_H

#include <vector>
#include <stack>
#include <tuple>

namespace bst
{

template<typename T>
struct _bst_node
{
    T _key;
    _bst_node<T> *_left {nullptr};
    _bst_node<T> *_right {nullptr};

    explicit _bst_node(T key);
    _bst_node(const _bst_node<T> &other);
    _bst_node<T> &operator=(_bst_node<T> &other);
    ~_bst_node();

    const _bst_node<T> *search(const T &key) const;
    _bst_node<T> *find_min();
    _bst_node<T> *find_max();
    _bst_node<T> *next_larger();

    void delete_children();
};

template<typename T>
_bst_node<T>::_bst_node(T key)
    :_key(std::move(key))
{}

template<typename T>
_bst_node<T>::_bst_node(const _bst_node<T> &other)
    :_key{other._key}
{
    if(other._left)
    {
        _left = new _bst_node<T>{*(other._left)};
    }
    if(other._right)
    {
        _right = new _bst_node<T>{*(other._right)};
    }
}

template<typename T>
_bst_node<T> &_bst_node<T>::operator=(_bst_node<T> &other)
{
    if(this != &other)
    {
        _key = other._key;
        delete_children();

        if(other._left)
        {
            _left = new _bst_node<T>{other._right->_key};
        }
        if(other._right)
        {
            _right = new _bst_node<T>{*(other._right)};
        }
    }
    return *this;
}

template<typename T>
_bst_node<T>::~_bst_node()
{
    delete_children();
}

template<typename T>
void _bst_node<T>::delete_children()
{
    _left = nullptr;
    _right = nullptr;
}

template<typename T>
const _bst_node<T> *_bst_node<T>::search(const T &key) const
{
    if (key == this->key)
        return this;

    if (key < this->key && _left != nullptr)
    {
        return _left->getNode(key);
    }
    else
    {
        return nullptr;
    }

    if (key > this->key && _right != nullptr)
    {
        return _right->getNode(key);
    }
    else
    {
        return nullptr;
    }
}

template<typename T>
_bst_node<T> *_bst_node<T>::find_min()
{
    _bst_node<T> *node = this;
    while(node->_left != nullptr)
    {
        node = node->_left;
    }
    return node;
}

template<typename T>
_bst_node<T> *_bst_node<T>::find_max()
{
    _bst_node<T> *node = this;
    while(node->_right != nullptr)
    {
        node = node->_right;
    }
    return node;
}

template<typename T>
_bst_node<T> *_bst_node<T>::next_larger()
{
    if(_right != nullptr)
    {
        return _right->find_min();
    }

    _bst_node<T> *node = this;
    while ((node->_parent != nullptr) && (node == node->_parent->_right))
    {
        node = node->_parent;
    }
    return node->_parent;
}

template <typename T>
class BST
{
    /* using nodes as tuple {root, l.child index, r.child index}
     *  0 idx -   {4, 1, 2}
     *  1st idx - {1, 3, -1}
     *  2nd idx - {2, -1, -1}
     *  3rd idx - {3, -1, -1}
     *  it is 0 index - root,
     *  4 - root value, 1 - index left child, 2 - index right child
     * */
    using _tn = std::tuple<int, int, int>;
    using _vector_tn = std::vector<_tn>;
    _bst_node<T> *_root;

    void _insert(T& key, _bst_node<T> *node)
    {
        auto *tmp = new _bst_node<T>(key);
        _bst_node<T> *parrent = nullptr;
        _bst_node<T> *current = node;

        while (current != nullptr)
        {
            parrent = current;
            if(key < current->_key)
            {
                current = current->_left;
            }
            else
            {
                current = current->_right;
            }
        }

        if(key < parrent->_key)
        {
            parrent->_left = tmp;
        }
        else
        {
            parrent->_right = tmp;
        }
    }

    void _destroy(_bst_node<T> *node)
    {
        if(node == nullptr)
        {
            return;
        }
        _destroy(node->_left);
        _destroy(node->_right);
        delete node;
    }

    void _remove(T& key, _bst_node<T> *node)
    {
        if(node == nullptr)
        {
            return;
        }
        else if(key == node->_key)
        {
            //1. remove if the node is a leaf
            if(node->_left == nullptr && node->_right == nullptr)
            {
                node = nullptr;
            }
            //2. remove if the node has one child
            else if((node->_left != nullptr)&&(node->_right == nullptr))
            {
                node = node->_left;
            }
            else if((node->_left == nullptr)&&(node->_right != nullptr))
            {
                node = node->_right;
            }
            //3. remove if the node has two child
            else
            {
                _bst_node<T>* new_node = node->next_larger();
                std::swap(node->_key, new_node->_key);
                _remove(new_node->_key, new_node);
                return;
            }
        }
        else if(key < node->_key)
        {
            _remove(key, node->_left);
        }
        else
        {
            _remove(key, node->_right);
        }
    }

    const _bst_node<T>* _search(T key)
    {
        return _root->search(key);
    }

    _bst_node<T>* _get_min()
    {
        return _root->find_min();
    }

    _bst_node<T>* _get_max()
    {
        return  _root->find_max();
    }

    int is_bst(_bst_node<T>* node)
    {
        if(node == nullptr)
            return 1;

        if(node->_left != nullptr && node->_left->_key > node->_key)
            return 0;

        if(node->_right != nullptr && node->_right->_key < node->_key)
            return 0;

        if(!is_bst(node->_left) || !is_bst(node->_right))
            return 0;

        return 1;
    }

    int is_bst_comm(_bst_node<T>* node)
    {
        if(node == nullptr)
            return 1;

        if(node->_left != nullptr && node->_left->_key > node->_key)
            return 0;

        if(node->_right != nullptr && node->_right->_key < node->_key)
            return 0;

        if(node->_right != nullptr && node->_right->_key == node->_key)
            return 1;

        if(!is_bst(node->_left) || !is_bst(node->_right))
            return 0;

        return 1;
    }

public:
    BST();
    BST(T root_key);
    BST(_vector_tn &in); //only for tests
    BST(const BST<T>& other);
    BST<T>& operator=(const BST<T>& other);
    ~BST();

    void insert(T key);
    void remove(T key);

    T min() const;
    T max() const;

    std::vector<T> get_in_order() const;
    std::vector<T> get_pre_order() const;
    std::vector<T> get_post_order() const;
    bool is_valid();
    bool is_valid_comm();
    _bst_node<T>* build_bt(_vector_tn& vec,
                           _bst_node<T> *root,
                           std::size_t i); //only for tests
};

template <typename T>
BST<T>::BST()
    :_root(nullptr)
{}

template <typename T>
BST<T>::BST(T root_key)
{
    _root = new _bst_node<T>{root_key};
}

template <typename T>
BST<T>::BST(const BST<T>& other)
{
    _root = new _bst_node<T>{*(other._root)};
}

/* only for tests */
template <typename T>
BST<T>::BST(_vector_tn& in)
{
    _root = build_bt(in, _root, 0);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST<T>& other)
{
    if(this != &other)
    {
        _destroy(_root);
        _root = new _bst_node<T>{*(other._root)};
    }
    return *this;
}

template <typename T>
BST<T>::~BST<T>()
{
    _destroy(_root);
}

template <typename T>
void BST<T>::insert(T key)
{
    if(this->_root == nullptr)
    {
        this->_root = new _bst_node<T>{key};
    }
    else
    {
        this->_insert(key, this->_root);
    }
}

template <typename T>
void BST<T>::remove(T key)
{
    _remove(key, _root);
}

template <typename T>
T BST<T>::min() const
{
    _bst_node<T>* result = _get_min();
    return result->_key;
}

template <typename T>
T BST<T>::max() const
{
    _bst_node<T>* result = _get_max();
    return result->_key;
}

template <typename T>
std::vector<T> BST<T>::get_in_order() const
{
    std::stack<_bst_node<T>*> node_stack;
    std::vector<T> result;
    _bst_node<T> *current = _root;

    while(current != nullptr || node_stack.empty() == false)
    {
        while(current != nullptr)
        {
            node_stack.push(current);
            current = current->_left;
        }

        current = node_stack.top();
        node_stack.pop();

        result.push_back(current->_key);

        current = current->_right;
    }
    return result;
}

template <typename T>
std::vector<T> BST<T>::get_pre_order() const
{
    std::stack<_bst_node<T>*> node_stack;
    std::vector<T> result;
    _bst_node<T> *current = _root;

    node_stack.push(current);
    while(!node_stack.empty())
    {
        current = node_stack.top();
        result.push_back(current->_key);
        node_stack.pop();

        if(current->_right != nullptr)
        {
            node_stack.push(current->_right);
        }
        if(current->_left != nullptr)
        {
            node_stack.push(current->_left);
        }
    }
    return result;
}

template <typename T>
std::vector<T> BST<T>::get_post_order() const
{
    std::stack<_bst_node<T>*> node_stack;
    std::vector<T> result;
    _bst_node<T> *current = _root;
    _bst_node<T> *last = nullptr;

    while(!node_stack.empty() || current != nullptr)
    {
        if(current != nullptr)
        {
            node_stack.push(current);
            current = current->_left;
        }
        else
        {
            _bst_node<T> *tmp = node_stack.top();
            if(tmp->_right != nullptr && last != tmp->_right)
            {
                current = tmp->_right;
            }
            else
            {
                result.push_back(tmp->_key);
                last = node_stack.top();
                node_stack.pop();
            }
        }
    }
    return result;
}

template <typename T>
bool BST<T>::is_valid()
{
    auto result = false;
    if(is_bst(_root))
    {
        result = true;
        return result;
    }
    return result;
}

template <typename T>
bool BST<T>::is_valid_comm()
{
    auto result = false;
    if(is_bst_comm(_root))
    {
        result = true;
        return result;
    }
    return result;
}

/* only for tests */
template <typename T>
_bst_node<T>* BST<T>::build_bt(BST<T>::_vector_tn& vec, _bst_node<T> *root,
                      std::size_t i)
{
    _bst_node<T>* temp = new _bst_node<T>(std::get<0>(vec[i]));
    root = temp;

    if(std::get<1>(vec[i]) != -1)
    {
        root->_left = build_bt(vec, root, std::get<1>(vec[i]));
    }
    if(std::get<2>(vec[i]) != -1)
    {
        root->_right = build_bt(vec, root, std::get<2>(vec[i]));
    }
    return root;
}

} //namespace bst

#endif // BST_H
