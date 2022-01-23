#ifndef LLIST_H
#define LLIST_H
#include <cstdint>
#include <string>
#include <stdexcept>

namespace scl {

template<class T>
class llist
{
private:

    struct list_tnode
    {
        T m_val;
        list_tnode *m_next = nullptr;
        list_tnode *m_prev = nullptr;

        list_tnode()
        {}

        list_tnode(T& val)
            :m_val(std::move(val))
            ,m_next(nullptr)
            ,m_prev(nullptr)
        {}

        list_tnode(T& val, list_tnode* next_node)
            :m_val(val)
            ,m_next(next_node)
            ,m_prev(next_node->m_prev)
        {
            if(m_prev)
            {
                m_prev->m_next = this;
            }
            m_next->m_prev = this;

        }
    };

    list_tnode *m_head = nullptr;
    list_tnode *m_tail = nullptr;
    std::size_t m_count;

    void copy_flist(const llist<T>& other);

    // Delete all nodes
    void clear();
public:
    class iterator
    {
    public:
        friend class llist<T>;
        iterator() noexcept {}
        explicit iterator(list_tnode *node):ptr_node(node){}

        inline iterator& operator=(const iterator& other){ptr_node = other.ptr_node; return *this;}
        inline T& operator*(){return ptr_node->m_val;}
        inline T* operator->(){return &ptr_node->m_val;}
        inline iterator& operator++(){ptr_node=ptr_node->m_next; return *this;} //++i
        inline iterator& operator++(int junk){iterator ret(*this); ++*this; return ret;} //i++
        inline bool operator ==(const iterator& other) const {return ptr_node == other.ptr_node;}
        inline bool operator !=(const iterator& other) const {return ptr_node != other.ptr_node;}

    private:
        list_tnode *ptr_node;
    };

    llist() noexcept;
    ~llist();
    llist(const llist&) = delete;
    llist &operator=(const llist&) = delete;
    llist(const llist&&) = delete;
    llist &operator=(const llist&&) = delete;

    // Insert node, with value data, before pos node
    iterator insert_after(const iterator& pos, const T& data);
    iterator insert_prev(const iterator& pos, const T& data);

    // Removes the element at pos
    iterator erase_after(iterator& pos);
    iterator erase(iterator& pos);
    iterator erase_prev(iterator& pos);

    //Push, pop to head or tail
    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();

    //Capacity
    inline std::size_t size() const noexcept;
    inline bool empty() const noexcept;

    //Access
    inline iterator begin();
    inline iterator cbegin() const;
    inline iterator end();
    inline iterator cend() const;
};

/**
 * @brief Default ctor
 */
template<class T>
llist<T>::llist() noexcept
    :m_head(nullptr)
    ,m_tail(nullptr)
    ,m_count(0)
{}

/**
 * @brief Dtor
 */
template<class T>
llist<T>::~llist()
{
    list_tnode* current = m_head;
    while(current != nullptr)
    {
        auto old = current;
        current = current->m_next;
        delete old;
    }
}

/**
 * @brief
 */
template<class T>
typename llist<T>::iterator llist<T>::insert_after(const iterator& pos, const T &data)
{
    //Add temp node and this iterator position as current node
    list_tnode* result = new (std::nothrow) list_tnode(data);
    list_tnode* curr_node = pos.ptr_node;

    if(result != nullptr){

        if(curr_node->m_next == nullptr){
            // If pos - tail node, adding after him
            curr_node->m_next = result;
        }else{
            // If insert in the middle of the list
            result->m_next = curr_node->m_next;
            curr_node->m_next = result;
        }
        ++m_count;
        return iterator(result);
    }
}

template<class T>
typename llist<T>::iterator llist<T>::insert_prev(const iterator& pos, const T &data)
{
    list_tnode* curr_node = pos.ptr_node;

    if(curr_node == m_head)
    {
        push_front(data);
        return iterator(curr_node);
    }

    list_tnode* result = new (std::nothrow) list_tnode();
    list_tnode* prev_curr_node = curr_node->m_prev;

    if(result != nullptr){
        result->m_val = data;

        result->m_next = curr_node;
        prev_curr_node->m_next = result;

        ++m_count;
        return iterator(result);
    }
}

/**
 * @brief
 */
template<class T>
typename llist<T>::iterator llist<T>::erase_after(iterator& pos)
{
    list_tnode* curr_pos = pos.ptr_node;
    list_tnode* tmp = curr_pos->m_next;

    curr_pos->m_next = tmp->m_next;
    delete tmp;
    --m_count;
    return iterator(curr_pos->m_next);
}

template<class T>
typename llist<T>::iterator llist<T>::erase(iterator& pos)
{
    list_tnode* curr_pos = pos.ptr_node;
    list_tnode* prev_curr_pos = curr_pos->m_prev;

    prev_curr_pos->m_next = curr_pos->m_next;
    delete curr_pos;
    --m_count;
    return iterator(prev_curr_pos->m_next);
}

//fixing get a nullptr pointer
template<class T>
typename llist<T>::iterator llist<T>::erase_prev(iterator& pos)
{
    list_tnode* curr_pos = pos.ptr_node;
    list_tnode* prev_curr_pos = curr_pos->m_prev;
    list_tnode* prev_prev_curr_pos = prev_curr_pos->m_prev;

    prev_prev_curr_pos->m_next = curr_pos;
    delete prev_curr_pos;
    --m_count;
    return iterator(curr_pos->m_next);
}

/**
 * @brief
 */
template<class T>
void llist<T>::push_front(const T& data)
{
    list_tnode* result = new (std::nothrow) list_tnode(data, m_head);

    if(result != nullptr){
        m_head = result;
        ++m_count;
    }
}

template<class T>
void llist<T>::push_back(const T& data)
{
    list_tnode* result = new (std::nothrow) list_tnode(data, m_tail);

    if(result != nullptr){
        m_tail = result;
        ++m_count;
    }
}

/**
 * @brief
 */
template<class T>
void llist<T>::pop_front()
{
    if(empty()) throw std::runtime_error("pop_front(): List is empty.");

    list_tnode* temp_head = m_head;
    m_head = m_head->m_next;
    delete temp_head;
    --m_count;
}

template<class T>
void llist<T>::pop_back()
{
    if(empty()) throw std::runtime_error("pop_back(): List is empty.");

    if(m_tail == m_head) pop_front();

    list_tnode* temp_tail = m_tail->m_prev;
    m_tail = temp_tail->m_prev;
    delete temp_tail;
    --m_count;
}

template<class T>
inline std::size_t llist<T>::size() const noexcept
{
    return m_count;
}

template<class T>
inline bool llist<T>::empty() const noexcept
{
    return m_count == 0;
}

template<class T>
inline typename llist<T>::iterator llist<T>::begin()
{
    if(empty()){
        throw std::runtime_error("List is empty.");
    }
    return iterator(m_head->m_next);
}

template<class T>
inline typename llist<T>::iterator llist<T>::cbegin() const
{
    if(empty()){
        throw std::runtime_error("List is empty.");
    }
    return iterator(m_head->m_next);
}

template<class T>
inline typename llist<T>::iterator llist<T>::end()
{
    if(empty()){
        throw std::runtime_error("List is empty.");
    }
    return iterator(m_tail);
}

template<class T>
inline typename llist<T>::iterator llist<T>::cend() const
{
    if(empty()){
        throw std::runtime_error("List is empty.");
    }
    return iterator(m_tail);
}

/**
 * @brief Private internal method. Check the head node of validity
 *        and then sequentially adds nodes with the given value.
 * @param other const reference other flist for copy
 */
template<class T>
void llist<T>::copy_flist(const llist<T>& other)
{
    if(other.m_head != nullptr){
        list_tnode* tmp = other.m_head;
        while(tmp != nullptr){
            this->push_back(tmp->m_val);
            tmp = tmp->m_next;
        }
    }
}

} //
#endif // LLIST_H
