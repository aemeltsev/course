#ifndef SPLAYT_H
#define SPLAYT_H

#include <cstdint>
#include <vector>
#include <utility>

namespace splay
{

static constexpr int64_t limit = 0x3B9ACA01;

class SPLAYT
{
    struct _sp_node
    {
        int32_t _key;
        int64_t _sum = 0;

        _sp_node *_left{nullptr};
        _sp_node *_right{nullptr};
        _sp_node *_parent{nullptr};

        _sp_node(int32_t key, int64_t sum,
                 _sp_node *left, _sp_node *right,
                 _sp_node *parent)
            :_key{key}
            ,_sum{sum}
            ,_left{left}
            ,_right{right}
            ,_parent{parent}
        {}
    };

    _sp_node *_root;

    int64_t get_sum(_sp_node *node)
    {
        if(node == nullptr) return 0ll;
        return node->_sum;
    }

    void set_parent(_sp_node *node, _sp_node *parent)
    {
        if(node != nullptr) node->_parent = parent;
    }

    void update(_sp_node *node)
    {
        if(node == nullptr) return;

        node->_sum = node->_key
                   + (node->_left != nullptr ? node->_left->_sum : 0ll)
                   + (node->_right != nullptr ? node->_right->_sum : 0ll);

        if(node->_left)
        {
            node->_left->_parent = node;
        }

        if(node->_right)
        {
            node->_right->_parent = node;
        }
    }

    bool has_parent(_sp_node *node)
    {
        if(node == nullptr || node->_parent == nullptr)
        {
            return false;
        }
        return true;
    }

    bool has_grand_parent(_sp_node *node)
    {
        if(node == nullptr
           || node->_parent == nullptr
           || node->_parent->_parent == nullptr)
        {
            return false;
        }
        return true;
    }

    bool is_left_child(_sp_node *node)
    {
        if(!has_parent(node)) return false;
        _sp_node *tmp = node->_parent;
        return tmp->_left == node;
    }

    bool is_right_child(_sp_node *node)
    {
        if(!has_parent(node)) return false;
        _sp_node *tmp = node->_parent;
        return tmp->_right == node;
    }

    void small_rotation(_sp_node *node)
    {
        _sp_node *parent = node->_parent;
        _sp_node *gr_parent = parent->_parent;

        if(!has_parent(node))
        {
            return;
        }

        if(is_left_child(node))
        {
            _sp_node *node_right = node->_right;
            node->_right = parent;
            parent->_left = node_right;
        }
        else
        {
            _sp_node *node_left = node->_left;
            node->_left = parent;
            parent->_right = node_left;
        }

        update(parent);
        update(node);

        node->_parent = gr_parent;

        if(gr_parent)
        {
            if(gr_parent->_left == parent)
            {
                gr_parent->_left = node;
            }
            else
            {
                gr_parent->_right = node;
            }
        }

    }

    void big_rotation(_sp_node *node)
    {
        if(!has_grand_parent(node))
        {
            return;
        }

        if(is_left_child(node) && is_left_child(node->_parent))
        {
            small_rotation(node->_parent);
            small_rotation(node);
        }
        else if(is_right_child(node) && is_right_child(node->_parent))
        {
            small_rotation(node->_parent);
            small_rotation(node);
        }
        else
        {
            small_rotation(node);
            small_rotation(node);
        }
    }

    void splay(_sp_node *node)
    {
        if(node == nullptr) return;

        while(has_parent(node))
        {
            if(has_grand_parent(node))
            {
                big_rotation(node);
            }
            else
            {
                small_rotation(node);
                break;
            }
        }
        _root = node;
    }

    _sp_node *_find(int32_t key)
    {
        _sp_node *node = _root;
        _sp_node *last = _root;
        _sp_node *next = nullptr;

        while(node != nullptr)
        {
            if(node->_key >= key && (next == nullptr || node->_key < next->_key))
            {
                next = node;
            }

            last = node;

            if(node->_key == key)
            {
                break;
            }
            else if(node->_key > key)
            {
                node = node->_left;
            }
            else
            {
                node = node->_right;
            }
        }

        splay(last);
        return next;
    }

    void _split(int32_t key, _sp_node *&lhs, _sp_node *&rhs)
    {
        if(_root == nullptr)
        {
            lhs = nullptr;
            rhs = nullptr;
            return;
        }

        rhs = _find(key);
        splay(rhs);

        if(rhs == nullptr)
        {
            lhs = _root;
            return;
        }

        lhs = rhs->_left;
        rhs->_left = nullptr;
        set_parent(lhs, nullptr);

        update(lhs);
        update(rhs);
    }

    static _sp_node* merge(_sp_node* lhs, _sp_node* rhs)
    {
        if(lhs == nullptr) return rhs;
        if(rhs == nullptr) return lhs;

        SPLAYT rtree(rhs);
        _sp_node* minr = rhs;

        while(minr->_left != nullptr)
        {
            minr = minr->_left;
        }

        rtree.splay(minr);
        minr->_left = lhs;
        rtree.update(minr);

        return minr;
    }

    SPLAYT(_sp_node *node)
        :_root(node)
    {}

public:
    SPLAYT()
    {}

    void insert(int32_t key)
    {
        _sp_node *left, *right;
        _sp_node *nn = nullptr;

        _split(key, left, right);

        if(right == nullptr || right->_key != key)
        {
            nn = new _sp_node(key, static_cast<int64_t>(key), nullptr, nullptr, nullptr);
        }

        _root = SPLAYT::merge(SPLAYT::merge(left, nn), right);
    }

    bool find(int32_t key)
    {
        _sp_node *result = _find(key);
        return (result != nullptr && result->_key == key);
    }

    void erase(int32_t key)
    {
        _sp_node *node = _find(key);

        if(node != nullptr && node->_key == key)
        {
            _sp_node *next = _find(key + 1);

            if(next != nullptr)
            {
                splay(next);
                splay(node);
                _sp_node *node_left = node->_left;
                next->_left = node_left;
                set_parent(next, nullptr);
                set_parent(node_left, next);
                _root = next;
                update(_root);
            }
            else
            {
                splay((node));
                _sp_node *node_left = node->_left;
                _root = node_left;
                set_parent(node_left, nullptr);
                splay(_root);
            }
        }
    }

    int64_t sum(int32_t lhs, int32_t rhs)
    {
        if(lhs > rhs) return 0;

        int64_t result = 0;

        _sp_node *left, *middle, *right;
        _split(lhs, left, middle);

        SPLAYT mt(middle);
        mt._split(rhs+1, middle, right);

        if(middle != nullptr)
        {
            result += static_cast<int64_t>(middle->_sum);
        }

        _sp_node *node_middle = SPLAYT::merge(left, middle);
        _root = SPLAYT::merge(node_middle, right);

        return result;
    }
};

} //namespace splay

#endif // SPLAYT_H
