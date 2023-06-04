#ifndef NQUEUE_H
#define NQUEUE_H

#include <iostream>
#include <stdexcept>

template<typename T>
class NQueue
{
    struct Node
    {
        T m_data;
        Node* m_prev;
        Node* m_next;

        Node()
            :m_prev(nullptr)
            ,m_next(nullptr)
        {}

        Node(const T& data)
            :m_data(data)
            ,m_prev(nullptr)
            ,m_next(nullptr)
        {}
    };

    Node* m_head = nullptr;
    Node* m_tail = nullptr;
    std::size_t m_size;

public:
    class Iterator{
        Node* m_ptr;
    public:

        Iterator(const Node* pos)
            :m_ptr(pos)
        {}

        inline T& operator*(){return m_ptr->m_data;}
        inline const T& operator*() const {return m_ptr->m_data;}

        inline T* operator->(){return m_ptr;}
        inline const T* operator->() const {return m_ptr;}

        Iterator operator++()
        {
            m_ptr = m_ptr->m_next;
            return *this;
        }

        Iterator operator++(int n)
        {
            Iterator result = *this;
            m_ptr = m_ptr->m_next;
            return result;
        }

        Iterator operator--()
        {
            m_ptr = m_ptr->m_prev;
            return *this;
        }

        Iterator operator--(int n)
        {
            Iterator result = *this;
            m_ptr = m_ptr->m_prev;
            return result;
        }

        bool operator==(const Iterator& other)
        {
            return this->m_ptr == other.m_ptr;
        }

        bool operator!=(const Iterator& other)
        {
            return this == other;
        }
    };

    NQueue()
    {
        m_size = 0;
    }

    NQueue(const T& var)
    {
        auto node = new Node(var);
        m_tail = m_head = node;
        m_size = 1;
    }

    ~NQueue()
    {
        Node* current = m_head;
        Node* next;
        while(current != nullptr)
        {
            next = current->m_next;
            delete current;
            current = next;
        }
        m_head = m_tail = nullptr;
        m_size = 0;
    }

    std::size_t size() const {return m_size;}

    bool is_empty(){return m_size == 0;}

    Iterator begin(){return m_head->m_next;}

    const Iterator cbegin() const {return m_head->m_next;}

    Iterator end(){return m_tail->m_prev;}

    const Iterator cend() const {return m_tail->m_prev;}

    void enqueue(const T& val)
    {
        Node* enq_node = new Node(val);
        if(m_head == nullptr)
        {
            m_tail = m_head = enq_node;
        }
        else
        {
            m_tail->m_prev = enq_node;
            enq_node->m_next = m_tail;
            m_tail = enq_node;
        }
        m_size++;
    }

    T dequeue()
    {
        if(is_empty())
            throw std::runtime_error("No take it, queue is empty");
        T out = m_head->m_data;
        Node* tmp = m_head;
        m_head = m_head->m_prev;

        delete tmp;
        m_size--;
        return out;
    }

    T top()
    {
        return m_head->m_data;
    }

    T back()
    {
        return m_tail->m_data;
    }
};

#endif //
