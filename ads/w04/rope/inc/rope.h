#ifndef ROPE_H
#define ROPE_H

#include <iostream>
#include <string>
#include <stack>
#include <list>

namespace tree
{
struct _rope_node
{
    char _key;
    std::size_t _size;
    _rope_node* _left = nullptr;
    _rope_node* _right = nullptr;
    _rope_node* _parent = nullptr;

    _rope_node()
        :_key(0)
        ,_size(0)
    {}

    _rope_node(char key,
               std::size_t size,
               _rope_node* left,
               _rope_node* right,
               _rope_node* parent)
        :_key(key)
        ,_size(size)
        ,_left(left)
        ,_right(right)
        ,_parent(parent)
    {}

    ~_rope_node()
    {
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
    }

    char& get_data() {return _key;}
    _rope_node* get_left_child() {return this->_left;}
    _rope_node* get_right_child() {return this->_right;}

  };

class Rope
{
    _rope_node* _root = nullptr;
    std::size_t _rsize = 0;

    void _destroy(_rope_node* node);
    void _update(_rope_node* node);
    void _right_rotation(_rope_node* node, _rope_node* parent);
    void _left_rotation(_rope_node* node, _rope_node* parent);
    void _splay(_rope_node* node);

    _rope_node* _merge(_rope_node* lhs, _rope_node* rhs);
    std::pair<_rope_node*, _rope_node*> _split(_rope_node* node, std::size_t key);
    _rope_node* _find(_rope_node* node, std::size_t key);
    void _push_back(char ch, _rope_node* node);
    void _insert(char ch, std::size_t pos, _rope_node* node);
    void _remove(_rope_node* node);
    _rope_node* _max_node(_rope_node* node);

public:
    Rope();
    explicit Rope(const std::string& str);
    ~Rope();

    void remove(std::size_t pos);
    void insert(char ch, std::size_t pos);
    void push_back(char ch);
    char find(std::size_t index);
    std::string to_string();
    std::size_t size() {return _rsize;}
    bool empty() {return _rsize == 0;}
};

Rope::Rope()
{}

Rope::Rope(const std::string& str)
{
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        _push_back(str[i], _root);
    }
}

Rope::~Rope()
{
    _destroy(_root);
}

void Rope::_destroy(_rope_node* node)
{
    if(node)
    {
        _destroy(node->get_left_child());
        _destroy(node->get_right_child());
        delete node;
    }
}

void Rope::_update(_rope_node *node)
{
    node->_size = 1 + (node->_left != nullptr ? node->_left->_size : 0)
                    + (node->_right != nullptr ? node->_right->_size : 0);
}

// zig(right rotation)
void Rope::_right_rotation(_rope_node *node, _rope_node *parent)
{
    parent->_left = node->_right;
    if(parent->_left)
    {
        parent->_left->_parent = parent;
    }

    node->_right = parent;
    node->_parent = parent->_parent;
    parent->_parent = node;

    if(node->_parent)
    {
        if(node->_parent->_left == parent)
            node->_parent->_left = node;
        else
            node->_parent->_right = node;
    }

    _update(parent);
    _update(node);
}

// zag(left rotation)
void Rope::_left_rotation(_rope_node *node, _rope_node *parent)
{
    parent->_right = node->_left;
    if(parent->_right)
    {
        parent->_right->_parent = parent;
    }

    node->_left = parent;
    node->_parent = parent->_parent;
    parent->_parent = node;

    if(node->_parent)
    {
        if(node->_parent->_left == parent)
            node->_parent->_left = node;
        else
            node->_parent->_right = node;
    }

    _update(parent);
    _update(node);
}

void Rope::_splay(_rope_node* node)
{
    if(node == nullptr) return;

    if(node->_parent != nullptr)
    {
        _rope_node* parent = node->_parent;
        if(parent->_parent == nullptr)
        {
            //zig/zag
            if(parent->_left == node)
                _right_rotation(node, parent);
            else
                _left_rotation(node, parent);
        }
        else
        {
            _rope_node* grandparent = parent->_parent;
            if(grandparent->_left == parent && parent->_left == node)
            {
                // zig-zag
                _right_rotation(parent, grandparent);
                _right_rotation(node, parent);
            }
            else if(grandparent->_right == parent && parent->_right == node)
            {
                // zag-zag
                _left_rotation(parent, grandparent);
                _left_rotation(node, parent);
            }
            else
            {
                if(parent->_left == node)
                {
                    // zig-zag
                    _right_rotation(node, parent);
                    grandparent->_right = node;
                    _left_rotation(node, grandparent);
                }
                else
                {
                    // zag-zig
                    _left_rotation(node, parent);
                    grandparent->_left = node;
                    _right_rotation(node, grandparent);
                }
            }
        }
        _splay(node);
    }
    else
    {
        _root = node;
    }
}

void Rope::_push_back(char ch, _rope_node *node)
{
    if(!node)
    {
        _root = new _rope_node(ch, 1, nullptr, nullptr, node);
    }
    else
    {
        if(node->_right == nullptr)
        {
            node->_right = new _rope_node(ch, 1, nullptr, nullptr, node);
            _splay(node->_right);
        }
        else
        {
            _push_back(ch, node->_right);
        }
    }
}

void Rope::push_back(char ch)
{
    _push_back(ch, _root);
    ++_rsize;
}

char Rope::find(std::size_t index)
{
    return _find(_root, index)->_key;
}

_rope_node* Rope::_find(_rope_node* node, std::size_t key)
{
    _rope_node* tmp = node;

    while(tmp != nullptr)
    {
        std::size_t size = (tmp->_left != nullptr) ? tmp->_left->_size : 0;
        if(key == size)
        {
            break;
        }
        else if(key < size)
        {
            tmp = tmp->_left;
        }
        else if(key > size)
        {
            tmp = tmp->_right;
            key = key - size - 1;
        }
        ++size;
    }
    _splay(tmp);
    return tmp;
}

_rope_node* Rope::_max_node(_rope_node *node)
{
    if(node == nullptr)
        return node;

    _rope_node* tmp = node;

    while(tmp != nullptr)
    {
        tmp = tmp->_right;
    }

    return tmp;
}

_rope_node* Rope::_merge(_rope_node *lhs, _rope_node *rhs)
{

    if(lhs == nullptr && rhs == nullptr)
    {
        return nullptr;
    }
    else if(lhs == nullptr)
    {
        rhs->_parent = nullptr;
        return rhs;
    }
    else if(rhs == nullptr)
    {
        lhs->_parent = nullptr;
        return lhs;
    }
    else
    {
        _rope_node* merged = _max_node(lhs);
        _splay(merged);
        merged->_right = rhs;
        rhs->_parent = merged;
        _update(merged);
        return merged;
    }
}

std::pair<_rope_node*, _rope_node*> Rope::_split(_rope_node *node, std::size_t key)
{
    _rope_node* l_node = nullptr;
    _rope_node* r_node = _find(node, key);

    _splay(r_node);

    if(r_node == nullptr)
    {
        l_node = node;
        return {l_node, r_node};
    }

    l_node = r_node->_left;
    r_node->_left = nullptr;

    if(l_node != nullptr)
    {
        l_node->_parent = nullptr;
    }

    _update(l_node);
    _update(r_node);
    return {l_node, r_node};
}

void Rope::_remove(_rope_node *node)
{
    if(!node) return;

    if(!node->_left && !node->_right)
    {
        delete node;
        _root = nullptr;
    }
    else
    {
        _splay(node);
        _root = _merge(node->_left, node->_right);
    }
}

void Rope::remove(std::size_t pos)
{
    ++pos;
    _remove(_find(_root, pos));
    --_rsize;
}

void Rope::_insert(char ch, std::size_t pos, _rope_node *node)
{
    if(!node)
    {
        _root = new _rope_node(ch, 1, nullptr, nullptr, node);
    }
    else
    {
        auto node_index = node->_size;
        if(node->_right != nullptr)
            node_index -= node->_right->_size;

        if(pos < node_index)
        {
            if(node->_left == nullptr)
            {
                node->_left = new _rope_node(ch, 1, nullptr, nullptr, node);
                _splay(node->_left);
            }
            else
            {
                _insert(ch, pos, node->_left);
            }
        }
        else
        {
            if(node->_right == nullptr)
            {
                node->_right = new _rope_node(ch, 1, nullptr, nullptr, node);
                _splay(node->_right);
            }
            else
            {
                _insert(ch, pos - node_index, node->_right);
            }
        }
    }
}

void Rope::insert(char ch, std::size_t pos)
{
    _insert(ch, pos, _root);
    ++_rsize;
}

std::string Rope::to_string()
{
    std::string result = "";

    if(_root == nullptr) return result;

    std::stack<_rope_node*> st;
    _rope_node* parent = _root;

    while(parent != nullptr)
    {
        st.push(parent);
        parent = parent->_left;
    }

    while(!st.empty())
    {
        parent = st.top();
        result.push_back(parent->_key);
        st.pop();
        parent = parent->_right;

        while(parent != nullptr)
        {
            st.push(parent);
            parent = parent->_left;
        }
    }
    return result;
}

} //namespace rp

#endif //ROPE_H
