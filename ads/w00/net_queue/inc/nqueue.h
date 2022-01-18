#ifndef NQUEUE_H
#define NQUEUE_H

#include <iostream>

#define NDEBUG
#include <cassert>

template<typename T>
struct Node
{
    T m_data;
    Node<T>* m_prev;
    Node<T>* m_next;

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

template<typename T>
class NQueue
{
    Node<T>* m_head = nullptr;
    Node<T>* m_tail = nullptr;
    std::size_t m_size;

public:
    class Iterator{
    public:

        Iterator(const Node<T>* pos)
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

        Node<T>* m_ptr;
    };

    NQueue()
    {
        m_head = new Node<T>();
        m_tail = new Node<T>();
        m_size = 0;
    }

    ~NQueue()
    {
        Node<T>* current = m_head->m_next;
        while(current != m_head)
        {
            Node<T>* next = current->m_next;
            delete current;
            current = next;
        }
        delete current;
    }

     std::size_t size() const {return m_size;}

     bool is_empty(){return m_size == 0;}

     Iterator begin(){return m_head->m_next;}

     const Iterator cbegin() const {return m_head->m_next;}

     Iterator end(){return m_tail->m_prev;}

     const Iterator cend() const {return m_tail->m_prev;}

     void enqueue(const T& val)
     {
         Node<T>* enq_node = new Node<T>(val);
         if(m_head->m_next == nullptr)
         {
             m_head->m_next = enq_node;
             enq_node->m_next = m_tail;
             enq_node->m_prev = m_head;
             m_tail->m_prev = enq_node;
         }
         else
         {
             auto next = m_head->m_next;
             next->m_prev = enq_node;
             m_head->m_next = enq_node;
             enq_node->m_next = next;
             enq_node->m_prev = m_head;
         }
         ++m_size;
     }

     T dequeue()
     {
         if(is_empty())
             assert("No take it, queue is empty");

         auto deq_node = m_tail->m_prev;
         T value = deq_node->m_data;
         m_tail->m_prev = deq_node->m_prev;
         delete deq_node;
         --m_size;
         return value;
     }

     T top()
     {
         return m_tail->m_prev->m_data;
     }

     T back()
     {
         return m_head->m_next->m_data;
     }
};

#endif //
