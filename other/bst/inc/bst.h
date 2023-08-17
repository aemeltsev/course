#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#define  NO             0
#define  YES            1

#define DEBUG           NO
#define USE_ITERATIVE   NO

namespace bst
{
template <typename T>
class bst
{
    struct bst_node__
    {
        T key__;
        bst_node__* parent__ {nullptr};
        bst_node__* left__ {nullptr};
        bst_node__* right__ {nullptr};

        void set_parent(const bst_node__* other){parent__ = other;}
        void set_right(const bst_node__* right){right__ = right;}
        void set_left(const bst_node__* left){right__ = left;}
        void set_key(const bst_node__& key) {key__ = key;}

        explicit bst_node__(const T &key)
            :key__(std::move(key)){}

        bst_node__(const bst_node__& other)
            :key__{other.key__}
        {
            if(other.left__ != nullptr) {
                left__ = new bst_node__{*(other.left__)};
                left__->set_parent(this);
            }
            if(other.right__ != nullptr) {
                right__ = new bst_node__{*(other.right__)};
                right__->set_parent(this);
            }
        }

        const T& get_key() const { return key__; }
        bst_node__* get_left() const { return left__; }
        bst_node__* get_right() const { return right__; }
        bst_node__* get_parent() const {return parent__; }

        bst_node__* find_min()
        {
            bst_node__ *node = this;
            while(node->left__ != nullptr) {
                node = node->left__;
            }
            return node;
        }

        bst_node__* find_max()
        {
            bst_node__ *node = this;
            while(node->_right != nullptr) {
                node = node->_right;
            }
            return node;
        }

        bst_node__* next_larger()
        {
            if(right__ != nullptr) {
                return right__->find_min();
            }

            bst_node__ *node = this;
            while ((node->parent__ != nullptr) && (node == node->parent__->right__)) {
                node = node->parent__;
            }
            return node->parent__;
        }

        bool is_root() const { return parent__ == nullptr; }
        bool has_left() const { return left__ != nullptr; }
        bool has_right() const { return right__ != nullptr; }
        bool isExternal() const { return !has_left() && !has_right(); }

        int depth() const
        {
            if (is_root()) return 0;
            else return (1 + parent__->depth());
        }

        int height() const
        {
            if (isExternal()) return 1;
            else return 1 + std::max(left__->height(), right__->height());
        }

        bool operator==(const bst_node__& other) const
        {
            auto bval = (key__ != other.key__) ? false : true;
            return bval;
        }

        bool operator<(const bst_node__& other) const
        {
            auto bval = (key__ < other.key__) ? true : false;
            return bval;
        }

        bool operator>(const bst_node__& other) const
        {
            auto bval = (key__ > other.key__) ? true : false;
            return bval;
        }

        friend std::ostream& operator<<(std::ostream& out, const bst_node__& node)
        {
            out << node.key__ <<'\n';
#if DEBUG
            out << "[this]:" << &node << '\n';
            if (node.parent__ != nullptr) out << "parent:" << *(node.parent__) << '\n';
            if (node.left__ != nullptr) out << "lchild:" << *(node.left__) << '\n';
            if (node.right__ != nullptr) out << "rchild:" << *(node.right__) << '\n';
#endif
            return out;
        }
    };

    bst_node__* root__;
    std::size_t size__;

    void insert__(const T& key, bst_node__ *node)
    {
#if USE_ITERATIVE
        auto *tmp = new bst_node__(key);
        if(root__ == nullptr) {
            root__ = tmp;
            size__++;
            return;
        }

        bst_node__ *parrent = nullptr;
        bst_node__ *current = node;

        while (current != nullptr) {
            parrent = current;
            if(current->key__ > key) {
                parrent = current;
                current = current->left__;
            } else if(current->key__ < key){
                parrent = current;
                current = current->_right;
            }
        }

        if(parrent->key__ > key) {
            parrent->left__ = tmp;
        } else {
            parrent->right__ = tmp;
        }
        size__++;
#else
        if(node == nullptr) {
            bst_node__ *newnode = new bst_node__(key);
            node = newnode;
        } else {
            if(node->key__ > key){
                insert__(key, node->left__);
            }
            else{
                insert__(key, node->right__);
            }
        }
        size__++;
        return;
#endif
    }

    inline int destroy__(bst_node__ *node) const
    {
        int removed = 0;
        if(node == nullptr) return 0;
#if USE_ITERATIVE
        std::queue<bst_node__*> nodes_q__;
        nodes_q__.push(node);

        bst_node__* front = nullptr;

        while (!nodes_q__.empty()) {
            front = nodes_q__.front();
            nodes_q__.pop();

            if(front->has_left()) {
                nodes_q__.push(front->left__);
            }

            if(front->has_right()) {
                nodes_q__.push(front->right__);
            }
#if DEBUG
            std::cout << "delete vertex: " << *front;
#endif
            delete front;
            removed++;
        }
        node = nullptr;
        return removed;
#else
        if((node->left__ == nullptr) && (node->right__ == nullptr)) {
#if DEBUG
            std::cout << "delete leaf: " << *node;
#endif
            delete node;
            removed++;
            return removed;
        } else {
            if(node->has_left()) {
                removed += destroy__(node->left__);
            }
            if(node->has_right()) {
                removed += destroy__(node->right__);
            }
#if DEBUG
            std::cout << "delete vertex: " << *node;
#endif
            delete node;
            removed++;
            return removed;
        }
#endif
    }

#if USE_ITERATIVE
    bool remove__(const T& key, bst_node__ *node) const
    {
#else
    bst_node__* remove__(const T& key, bst_node__ *node) const
    {
#endif
#if USE_ITERATIVE
        bst_node__* current = node;
        bst_node__* previev = nullptr;

        while (current != nullptr && current->key__ != key) {
            previev = current;
            if(current->key__ > key) current = current->left__;
            else current = current->right__;
        }

        if(current == nullptr) {
            return false;
        }
        // case one children
        if(!current->has_left() || !current->has_right()) {
            bst_node__* new_current;

            if(current->left__ == nullptr) new_current = current->right__;
            else new_current = current->left__;

            if(previev == nullptr) {
                return false;
            }

            if(current == previev->left__) previev->left__ = new_current;
            else previev->right__ = new_current;

            delete current;
        }
        //case two children
        else{
            bst_node__* part = nullptr;
            bst_node__* temp;

            temp = current->right__;
            while (temp->left__ != nullptr) {
                part = temp;
                temp = temp->left__;
            }

            if(part != nullptr) {
                part->left__ = temp->right__;
            }
            else {
                current->right__ = temp->right__;
            }

            current->key__ = temp->key__;
            delete temp;
        }
        this->size__--;
        return true;
#else
        if(node == nullptr) {
            return node;
        }

        if(key < node->key__) {
            node->left__ = remove__(key, node->left__);
        }
        else if(key > node->key__) {
            node->right__ = remove__(key, node->right__);
        }
        else if(node->has_left() && node->has_right()) {
            node->key__ = node->right__->find_min()->key__;
            node->right__ = remove__(node->key__, node->right__);
        }
        else {
            if(node->has_left()) {
                node = node->left__;
            }
            else if(node->has_right()) {
                node = node->right__;
            }
            else {
                node = nullptr;
            }
        }
        return node;
#endif
    }

    const bst_node__* search__(const T& key, bst_node__* node) const
    {
        if(node == nullptr || key == node->key__) return node;
        if(key < node->key__) {
            return search__(key, node->left__);
        }
        else {
            return search__(key, node->right__);
        }
    }

    const bst_node__* get_min__() const
    {
        return root__->find_min();
    }

    const bst_node__* get_max__() const
    {
        return root__->find_max();
    }

    int is_bst__(bst_node__* node)
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

    int is_bst_comm__(bst_node__* node)
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
    bst();
    bst(const T& key);
    ~bst();

    void insert(const T &key);
    void remove(const T& key);

    T min() const;
    T max() const;

    std::vector<T> get_in_order() const;
    std::vector<T> get_pre_order() const;
    std::vector<T> get_post_order() const;
    bool is_valid();
    bool is_valid_comm();
};

template <typename T>
bst<T>::bst()
    :root__(nullptr)
{}

template <typename T>
bst<T>::bst(const T& key)
{
    root__ = new bst_node__{key};
}

template <typename T>
bst<T>::~bst<T>()
{
    destroy__(root__);
}

template <typename T>
void bst<T>::insert(const T& key)
{
    if(root__ == nullptr) {
        root__ = new bst<T>{key};
    }
    else {
        this->insert__(key, this->root__);
    }
}

template <typename T>
void bst<T>::remove(const T& key)
{
#if USE_ITERATIVE
    remove__(key, this->root__);
#else
    remove__(key, this->root__);
#endif
}

template <typename T>
T bst<T>::min() const
{
    bst_node__* result = get_min__();
    return result->_key;
}

template <typename T>
T bst<T>::max() const
{
    bst_node__* result = get_max__();
    return result->_key;
}

template <typename T>
std::vector<T> bst<T>::get_in_order() const
{
    std::stack<bst_node__*> node_stack;
    std::vector<T> result;
    bst_node__ *current = root__;

    while(current != nullptr || node_stack.empty() == false) {
        while(current != nullptr) {
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
std::vector<T> bst<T>::get_pre_order() const
{
    std::stack<bst_node__*> node_stack;
    std::vector<T> result;
    bst_node__ *current = root__;

    node_stack.push(current);
    while(!node_stack.empty()) {
        current = node_stack.top();
        result.push_back(current->_key);
        node_stack.pop();

        if(current->_right != nullptr) {
            node_stack.push(current->_right);
        }
        if(current->_left != nullptr) {
            node_stack.push(current->_left);
        }
    }
    return result;
}

template <typename T>
std::vector<T> bst<T>::get_post_order() const
{
    std::stack<bst_node__*> node_stack;
    std::vector<T> result;
    bst_node__ *current = root__;
    bst_node__ *last = nullptr;

    while(!node_stack.empty() || current != nullptr) {
        if(current != nullptr) {
            node_stack.push(current);
            current = current->_left;
        }
        else {
            bst_node__ *tmp = node_stack.top();
            if(tmp->_right != nullptr && last != tmp->_right) {
                current = tmp->_right;
            }
            else {
                result.push_back(tmp->_key);
                last = node_stack.top();
                node_stack.pop();
            }
        }
    }
    return result;
}

template <typename T>
bool bst<T>::is_valid()
{
    auto result = false;
    if(is_bst(root__)) {
        result = true;
        return result;
    }
    return result;
}

template <typename T>
bool bst<T>::is_valid_comm()
{
    auto result = false;
    if(is_bst_comm(root__)) {
        result = true;
        return result;
    }
    return result;
}

}

#endif // BST_H
