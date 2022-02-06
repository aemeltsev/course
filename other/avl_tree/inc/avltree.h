#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>

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

    T get_data(){return _data;}
    int get_height(){return _height;}

    int update_height();
    int get_balance();

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
        return this->get_left_child()->get_height() - this->getRightChild()->get_height();
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
    if(new_left != nullptr) new_left->parent = this;

    _left_child = new_left;
    update_height();
    return _left_child;
}

template<typename T>
_tnode<T>* _tnode<T>::set_right_child(_tnode<T>* new_right)
{
    if(new_right != 0) new_right->parent = this;
    _right_child = new_right;
    update_height();
    return _right_child;
}

template<typename T>
class AVLTree
{
private:
    _tnode<T>* _root;
    std::size_t _size;

    void _set_root(_tnode<T>* node);
    void _rotate_left(_tnode<T>* node);
    void _rotate_right(_tnode<T>* node);
    void balance_node(_tnode<T>* node);

public:

    template<typename Y>
    class Iterator
    {
        _tnode<Y>* _itnode;
        const AVLTree<Y>* _avlt;
    public:

        Iterator(_tnode<Y>* node, const AVLTree<Y>& avl)
            :_itnode(node)
            ,_avlt(&avl)
        {}

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

    }

    const AVLTree& operator=(const AVLTree& other)
    {

    }

    ~AVLTree()
    {

    }

    void clear();
    void insert(const T& key);
    void remove(const T& key);
    _tnode<T>* find(const T& val);
    std::size_t size() const {return _size;}
    bool empty() const {return _size == 0;}
    std::size_t height(){return (_root ? _root->get_height() : 0);}
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

    // Now attach the subtree to the parent (or root)
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

    // Now attach the subtree to the parent (or root)
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
void AVLTree<T>::balance_node(_tnode<T>* node)
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

#endif // AVLTREE_H
