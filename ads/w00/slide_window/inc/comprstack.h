#ifndef COMPRSTACK_H
#define COMPRSTACK_H
#include <stack>
#include <functional>

template<typename T, typename Compare = std::greater<T>>
class ComprStack
{
    Compare m_compare;
    std::stack<T> m_values;
    std::stack<T> m_compr;
public:
    ComprStack()
        :m_values{}
        ,m_compr{}
    {}

    void cs_push(const T& var)
    {
        m_values.push(var);

        if(!m_compr.empty())
        {
            m_compr.push(m_compare(var, m_compr.top()) ? var : m_compr.top());
        }
        else
        {
            m_compr.push(var);
        }
    }

    void cs_pop()
    {
        m_values.pop();
        m_compr.pop();
    }

    T& cs_comp(){return m_compr.top();}
    const T& cs_comp() const {return m_compr.top();}
    T& cs_top(){return m_values.top();}
    const T& cs_top() const {return m_values.top();}
    bool cs_empty(){return m_values.empty();}
    std::size_t cs_size() const {return m_values.size();}
};

#endif // COMPRSTACK_H
