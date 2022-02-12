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
  };

class Rope
{
    std::string _str;
    _rope_node* _root;

    void _destroy(_rope_node *node);
    void _update(_rope_node *node);
    void _right_rotation(_rope_node *node, _rope_node *parent);
    void _left_rotation(_rope_node *node, _rope_node *parent);
    void _splay(_rope_node *node);


    //void _small_rotation(_rope_node* node);
    //void _big_rotation(_rope_node* node);
    _rope_node* _merge(_rope_node* lhs, _rope_node* rhs);
    std::pair<_rope_node*, _rope_node*> _split(_rope_node* node, std::size_t key);
    _rope_node* _find(_rope_node *&root, std::size_t key);

public:
    explicit Rope(const std::string& str);

    void remove(_rope_node*& root, std::size_t start, std::size_t len);
    void insert(_rope_node*& root, int k, _rope_node*& subString);
    char find(std::size_t index);
    std::string to_string();

};

Rope::Rope(const std::string& str)
    :_str(str)
{
    for(std::size_t i = 0; i < str.length(); ++i)
    {   _rope_node* next = new _rope_node(str[i], 1, nullptr, nullptr, nullptr);
        _root = _merge(_root, next);
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

_rope_node* Rope::_find(_rope_node*& root, std::size_t key)
{
    _rope_node* tmp = root;

    while(tmp != nullptr)
    {
        std::size_t size = (tmp->_left != nullptr) ? tmp->_left->_size : 0;
        if(key == (++size))
        {
            break;
        }
        else if(key < (++size))
        {
            tmp = tmp->_left;
        }
        else if(key > (++size))
        {
            tmp = tmp->_right;
            key = key - size - 1;
        }
    }
    splay(root, tmp);
    return tmp;
}

_rope_node* Rope::_merge(_rope_node *lhs, _rope_node *rhs)
{
    if(lhs == nullptr) return rhs;
    if(rhs == nullptr) return lhs;

    _rope_node* min_right = rhs;

    while(min_right->_left != nullptr)
    {
        min_right = min_right->_left;
    }

    splay(rhs, min_right);
    rhs->_left = lhs;
    _update(rhs);
    return rhs;
}

std::pair<_rope_node*, _rope_node*> Rope::_split(_rope_node *node, std::size_t key)
{
    _rope_node* l_node = nullptr;
    _rope_node* r_node = _find(node, key);
    splay(node, r_node);
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

void Rope::remove(_rope_node *&root, std::size_t start, std::size_t len)
{
    auto node_one = _split(root, start);
    root = node_one.first;
    _rope_node* l_node = node_one.second;

    auto node_two = _split(l_node, len-start);
    l_node = node_two.first;
    _rope_node* r_node = node_two.second;

    root = _merge(root, r_node);
    delete l_node;

}

void Rope::insert(_rope_node*& root, int k, _rope_node*& subString)
{
    auto tmp = _split(root, k);
    _rope_node* l_node = tmp.first;
    _rope_node* r_node = tmp.second;
    root = _merge(_merge(l_node, subString), r_node);


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

char Rope::find(std::size_t index)
{
    return _find(_root, index)->_key;
}

} //namespace rp

#endif //ROPE_H