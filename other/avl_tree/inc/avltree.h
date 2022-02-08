#ifndef AVLTREE_H
#define AVLTREE_H

#include <cstdint>
#include <iterator>

namespace tree {

template<typename T>
class _tnode
{
private:
    T _data;
    int _height;
    _tnode* _parent = nullptr;
    _tnode* _left_child = nullptr;
    _tnode* _right_child = nullptr;

public:
    _tnode()
        :_data(0)
        ,_height(0)
    {}

    explicit _tnode(T& val)
        :_data(val)
        ,_height(0)

    {}

    explicit _tnode(const T& val)
        :_data(val)
        ,_height(0)

    {}

    _tnode(T& key, int height, _tnode* parent, _tnode* left_child, _tnode* _right_child)
        :_data(key)
        ,_height(height)
        ,_parent(parent)
        ,_left_child(left_child)
        ,_right_child(_right_child)
    {}

    T get_data(){return _data;}
    int get_height(){return _height;}

    int update_height();
    int get_balance();
    bool is_leaf();

    _tnode* get_parent(){return this->_parent;}
    _tnode* get_left_child(){return this->_left_child;}
    _tnode* get_right_child(){return _right_child;}
    _tnode<T>* set_left_child(_tnode* new_left);
    _tnode* set_right_child(_tnode* new_right);

    void remove_parent(){this->_parent = nullptr;}
    void remove_left_child(){this->_left_child = nullptr;}
    void remove_right_child(){this->_right_child = nullptr;}
};

template<typename T>
int _tnode<T>::update_height()
{
    if(_left_child != nullptr && _right_child != nullptr)
    {
        if(_left_child->get_height() > _right_child->get_height())
        {
            _height = _left_child->get_height() + 1;
        }
        else
        {
            _height = _right_child->get_height() + 1;
        }
    }
    else if(_left_child != nullptr)
    {
        _height = _left_child->get_height() + 1;
    }
    else if(_right_child != nullptr)
    {
        _height = _right_child->get_height() + 1;
    }
    else{
        _height = 0;
    }
    return _height;
}

template<typename T>
int _tnode<T>::get_balance()
{
    if(this->get_left_child() != nullptr && this->get_right_child() != nullptr)
    {
        return this->get_left_child()->get_height() - this->get_right_child()->get_height();
    }
    else if(this->get_left_child() != nullptr)
    {
        return this->get_left_child()->get_height() + 1;
    }
    else if(this->get_right_child() != nullptr)
    {
        return (-1) * (this->get_right_child()->get_height() + 1);
    }
    else{
        return 0;
    }
}

template<typename T>
_tnode<T>* _tnode<T>::set_left_child(_tnode<T>* new_left)
{
    if(new_left != nullptr) new_left->_parent = this;

    _left_child = new_left;
    update_height();
    return _left_child;
}

template<typename T>
_tnode<T>* _tnode<T>::set_right_child(_tnode<T>* new_right)
{
    if(new_right != 0) new_right->_parent = this;
    _right_child = new_right;
    update_height();
    return _right_child;
}

template<typename T>
bool _tnode<T>::is_leaf()
{
    return this->get_left_child() == nullptr && this->get_right_child() == nullptr;
}

template<typename T>
class AVLTree
{
private:
    _tnode<T>* _root;
    std::size_t _size{0};
    static _tnode<T>* _copy_nodes(_tnode<T>* node)
    {
        if(node != nullptr)
        {
            _tnode<T>* parent = _copy_nodes(node->get_parent());
            _tnode<T>* left = _copy_nodes(node->get_left_child());
            _tnode<T>* right = _copy_nodes(node->get_right_child());
            return new _tnode<T>(node->get_data(), node->get_height(), parent, left, right);
        }
        else
        {
            return nullptr;
        }
    }

    void _set_root(_tnode<T>* node);
    void _rotate_left(_tnode<T>* node);
    void _rotate_right(_tnode<T>* node);
    void _balance_node(_tnode<T>* node);
    void _delete_tree(_tnode<T>* node);

public:

    class Iterator
            :public std::iterator<std::bidirectional_iterator_tag, T>
    {
        friend class AVLTree<T>;
        _tnode<T>* _itnode;
        const AVLTree<T>* _tree;

        Iterator up() {_itnode = _itnode->get_parent(); return *this;}
        Iterator left() {_itnode = _itnode->get_left_child(); return *this;}
        Iterator right() {_itnode = _itnode->get_right_child(); return *this;}

    public:

        Iterator(_tnode<T>* node, const AVLTree<T>* tree)
            :_itnode(node)
            ,_tree(tree)
        {}

        const T& operator*() const {return _itnode->get_data();}
        const T& operator->()const {return _itnode->get_data();}

        Iterator& operator++()
        {
            _tnode<T>* tmp;

            if(_itnode == nullptr)
            {
                _itnode = _tree->_root;
                if(_itnode == nullptr)
                {
                    throw "Out of range";
                }

                while(_itnode->get_left_child() != nullptr)
                {
                    _itnode = _itnode->get_left_child();
                }
            }
            else
            {
                if(_itnode->get_right_child() != nullptr)
                {
                    _itnode = _itnode->get_right_child();

                    while(_itnode->get_left_child() != nullptr)
                    {
                        _itnode = _itnode->get_left_child();
                    }
                }
                else
                {
                    tmp = _itnode->get_parent();

                    while(tmp != nullptr && _itnode == tmp->get_right_child())
                    {
                        _itnode = tmp;
                        tmp = tmp->get_parent();
                    }

                    _itnode = tmp;
                }
            }
            return *this;
        }

        Iterator& operator--()
        {
            _tnode<T>* tmp;

            if(_itnode == nullptr)
            {
                _itnode = _tree->_root;
                if(_itnode == nullptr)
                {
                    throw "Out of range";
                }

                while(_itnode->get_right_child() != nullptr)
                {
                    _itnode = _itnode->get_right_child();
                }
            }
            else
            {
                if(_itnode->get_left_child() != nullptr)
                {
                    _itnode = _itnode->get_left_child();

                    while(_itnode->get_right_child() != nullptr)
                    {
                        _itnode = _itnode->get_right_child();
                    }
                }
                else
                {
                    tmp = _itnode->get_parent();

                    while(tmp != nullptr && _itnode == tmp->get_left_child())
                    {
                        _itnode = tmp;
                        tmp = tmp->get_parent();
                    }

                    _itnode = tmp;
                }
            }
            return *this;
        }

        Iterator operator++(int);
        Iterator operator--(int);
        Iterator& operator+=(int i);
        Iterator& operator-=(int i);

        operator bool() {return _itnode != nullptr;}

        bool operator==(const Iterator& itr)
        {
            return _itnode == itr._itnode && _tree == itr._tree;
        }

        bool operator!=(const Iterator& itr)
        {
            return _itnode != itr._itnode || _tree != itr._tree;
        }

    };

    AVLTree()
        :_root(nullptr)
    {}

    AVLTree(T& val)
    {
        _root = new _tnode<T>(val);
    }

    AVLTree(const AVLTree& other)
    {
        if(this != &other)
        {
            _root = _copy_nodes(other._root);
        }
    }
    /*
    const AVLTree& operator=(const AVLTree& other)
    {

    }*/

    ~AVLTree()
    {
        _delete_tree(_root);
        delete _root;
    }

    void clear();
    void insert(const T& key);
    void remove(T& key);
    _tnode<T>* find(const T& val);
    bool empty() const {return _size == 0;}
    std::size_t size()const {return _size;}
};

template<typename T>
void AVLTree<T>::_set_root(_tnode<T>* node)
{
    _root = node;
    if(_root != nullptr) _root->remove_parent();
}

template<typename T>
void AVLTree<T>::_rotate_left(_tnode<T>* node)
{
    _tnode<T>* parent = node->get_parent();
    bool left{false};
    bool right{false};

    if(parent)
    {
        if(parent->get_left_child() == node)
            left = true;
        else
            right = true;
    }

    _tnode<T>* temp = node->get_right_child();
    node->set_right_child(temp->get_left_child());
    temp->set_left_child(node);

    if(parent)
    {
        if(left)
            parent->set_left_child(temp);
        if(right)
            parent->set_right_child(temp);
    }
    else
    {
        _set_root(temp);
    }
}

template<typename T>
void AVLTree<T>::_rotate_right(_tnode<T>* node)
{
    _tnode<T>* parent = node->get_parent();
    bool left{false};
    bool right{false};

    if(parent)
    {
        if(parent->get_left_child() == node)
            left = true;
        else
            right = true;
    }

    _tnode<T>* temp = node->get_left_child();
    node->set_left_child(temp->get_right_child());
    temp->set_right_child(node);

    if(parent)
    {
        if(left)
            parent->set_left_child(temp);
        if(right)
            parent->set_right_child(temp);
    }
    else
    {
        _set_root(temp);
    }
}

template<typename T>
void AVLTree<T>::_balance_node(_tnode<T>* node)
{
    auto balance = node->get_balance();

    if(balance > 1)
    {
        if(node->get_left_child()->get_balance() < 0)
            _rotate_left(node->get_left_child());
        _rotate_right(node);
    }
    else if(balance < -1)
    {
        if(node->get_right_child()->get_balance() > 0)
            _rotate_right(node->get_right_child());
        _rotate_left(node);
    }
}

template<typename T>
void AVLTree<T>::_delete_tree(_tnode<T>* node)
{
    if(node)
    {
        _delete_tree(node->get_left_child());
        _delete_tree(node->get_right_child());
        delete node;
    }
}

template<typename T>
void AVLTree<T>::clear()
{
    _delete_tree(_root);
}

template<typename T>
void AVLTree<T>::insert(const T& key)
{
    _tnode<T>* add_node;
    // basic case: if empty tree - insert in to _root node
    if(!_root)
    {
        _root = new _tnode<T>(key);
        _size++;
    }
    else
    {
        auto tmp = _root;
        // iterative descend and search parrent node
        while(true)
        {
            // insert to left sub-tree
            if(key < tmp->get_data())
            {
                if(tmp->get_left_child() == nullptr)
                {
                    add_node = tmp->set_left_child(new _tnode<T>(key));
                    break;
                }
                else
                {
                    tmp = tmp->get_left_child();
                }
            }
            // insert to right sub-tree
            else if(key > tmp->get_data())
            {
                if(tmp->get_right_child() == nullptr)
                {
                    add_node = tmp->set_right_child(new _tnode<T>(key));
                    break;
                }
                else
                {
                    tmp = tmp->get_right_child();
                }
            }
            else
            {
                return;
            }
        }
        tmp = add_node;
        _size++;
        // iterative ascend - update height and rebalance
        while(tmp != nullptr)
        {
            tmp->update_height();
            _balance_node(tmp);
            tmp = tmp->get_parent();
        }
    }
}

template<typename T>
void AVLTree<T>::remove(T &key)
{
    // empty tree
    if(_root == nullptr) return;
    // find node to be deleted
    _tnode<T>* rem_node = find(key);
    if(rem_node == nullptr) return;

    _tnode<T> *replace, *replace_parent, *tmp;
    // get parent of a node to be removed
    _tnode<T>* rem_node_parent = rem_node->get_parent();
    bool left_side = false;
    bool right_side = false;

    if(rem_node_parent != nullptr)
    {
        (rem_node_parent->get_left_child() == rem_node) ? left_side = true
                                                        : right_side = true;
    }

    int balance = rem_node->get_balance();

    // no child case - node is leaf
    if(rem_node->is_leaf())
    {
        // if parent exist
        if(rem_node_parent != nullptr)
        {
            if(left_side)
                rem_node_parent->set_left_child(nullptr);
            else
                rem_node_parent->set_right_child(nullptr);

            delete rem_node;
            rem_node_parent->update_height();
            _balance_node(rem_node_parent);
        }
        else
        {
            // rem_node - root
            _set_root(nullptr);
            delete rem_node;
        }
    }
    else if(rem_node->get_right_child() == nullptr)
    {
        // if exist one left child
        // if parent exist
        if(rem_node_parent != nullptr)
        {
            if(left_side)
                rem_node_parent->set_left_child(rem_node->get_left_child());
            else
                rem_node_parent->set_right_child(rem_node->get_left_child());

            delete rem_node;
            rem_node_parent->update_height();
            _balance_node(rem_node_parent);
        }
        else
        {
            _set_root(rem_node->get_left_child());
            delete rem_node;
        }
    }
    else if(rem_node->get_left_child() == nullptr)
    {
        // if exist one right child
        // if parent exist
        if(rem_node_parent != nullptr)
        {
            if(left_side)
                rem_node_parent->set_left_child(rem_node->get_right_child());
            else
                rem_node_parent->set_right_child(rem_node->get_right_child());

            delete rem_node;
            rem_node_parent->update_height();
            _balance_node(rem_node_parent);
        }
        else
        {
            _set_root(rem_node->get_right_child());
            delete rem_node;
        }
    }
    else
    {
        if(balance > 0)
        {
            if(rem_node->get_left_child()->get_right_child() == nullptr)
            {
                replace = rem_node->get_left_child();
                replace->set_right_child(rem_node->get_right_child());

                tmp = replace;
            }
            else
            {
                replace = rem_node->get_left_child()->get_right_child();
                while(replace->get_right_child() != nullptr)
                {
                    replace = replace->get_right_child();
                }
                replace_parent = replace->get_parent();
                replace_parent->set_right_child(replace->get_left_child());

                tmp = replace_parent;

                replace->set_left_child(rem_node->get_left_child());
                replace->set_right_child(rem_node->get_right_child());
            }
        }
        else
        {
            if(rem_node->get_right_child()->get_left_child() == nullptr)
            {
                replace = rem_node->get_right_child();
                replace->set_left_child(rem_node->get_left_child());

                tmp = replace;
            }
            else
            {
                replace = rem_node->get_right_child()->get_left_child();
                while(replace->get_left_child() != nullptr)
                {
                    replace = replace->get_left_child();
                }
                replace_parent = replace->get_parent();
                replace_parent->set_left_child(replace->get_right_child());

                tmp = replace_parent;

                replace->set_left_child(rem_node->get_left_child());
                replace->set_right_child(rem_node->get_right_child());
            }
        }

        if(rem_node_parent != nullptr)
        {
            if(left_side)
                rem_node_parent->set_left_child(replace);
            else
                rem_node_parent->set_right_child(replace);

            delete rem_node;
        }
        else
        {
            _set_root(replace);
            delete rem_node;
        }
        _balance_node(tmp);
    }
}

template<typename T>
_tnode<T>* AVLTree<T>::find(const T& val)
{
    _tnode<T>* temp = _root;
    while(temp)
    {
        if(val == temp->get_data())
            return temp;
        else if(val < temp->get_data())
            temp = temp->get_left_child();
        else
            temp = temp->get_right_child();
    }
    return nullptr;
}

} //namespace tree

#endif // AVLTREE_H
