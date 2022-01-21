#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <map>
#include <cassert>
#include <algorithm>

template<typename T>
class DisjointSet
{
    struct Node
        {
            T m_data;
            std::size_t m_parent;
            std::size_t m_rank;
            int m_count;//only for testing

            Node(const T& data, std::size_t parent)
                :m_data(data)
                ,m_parent(parent)
                ,m_rank(0)
                ,m_count(data) //only for testing
            {}
        };

    std::map<std::size_t, Node> m_nodes;
    std::size_t m_treeSize;

public:

    DisjointSet();
    explicit DisjointSet(const std::map<std::size_t, T>& init);

    void add_node(std::size_t parent, const T& var);
    void add_nodes(const std::map<std::size_t, T>& nodes);
    std::size_t find_set(std::size_t indx) const;
    std::size_t node_count() const;
    std::size_t tree_count() const;
    std::size_t max_node_count();//only for testing
    void union_nodes(std::size_t x, std::size_t y);
    T& value_of(std::size_t indx);
    const T& value_of(std::size_t indx) const;

private:
        Node& get_node(std::size_t indx) const;
        void link(std::size_t x, std::size_t y);
};

template<typename T>
DisjointSet<T>::DisjointSet()
    :m_treeSize(0)
{}

template<typename T>
DisjointSet<T>::DisjointSet(const std::map<std::size_t, T> &init)
{
    add_nodes(init);
}

template<typename T>
void DisjointSet<T>::add_node(std::size_t parent, const T& var)
{
    m_nodes.insert(std::make_pair(parent, Node(var, parent)));
    ++m_treeSize;
}

template<typename T>
void DisjointSet<T>::add_nodes(const std::map<std::size_t, T> &nodes)
{
    typename std::map<std::size_t, T>::const_iterator it_beg = nodes.begin();

    while(it_beg != nodes.end())
    {
        auto parent = it_beg->first;
        auto data = it_beg->second;
        m_nodes.insert(std::make_pair(parent, Node(data, parent)));
        ++it_beg;
    }
    m_treeSize += nodes.size();
}

template<typename T>
std::size_t DisjointSet<T>::find_set(std::size_t indx) const
{
    auto& node = get_node(indx);
    auto& parent = node.m_parent;
    if(parent != indx)
    {
        parent = find_set(parent);
    }
    return parent;
}

template<typename T>
std::size_t DisjointSet<T>::node_count() const
{
    return m_nodes.size();
}

template<typename T>
std::size_t DisjointSet<T>::tree_count() const
{
    return m_treeSize;
}

/**
  *only for testing
  * https://stackoverflow.com/questions/9370945/finding-the-max-value-in-a-map
  */
template<typename T>
std::size_t DisjointSet<T>::max_node_count()
{
    typename std::map<std::size_t, Node>::const_iterator best = std::max_element(m_nodes.begin(),
                             m_nodes.end(),
                             [&](std::pair<std::size_t, Node> a,
                             std::pair<std::size_t, Node> b) -> bool
                             {return a.second.m_count < b.second.m_count;} );
    return best->second.m_count;
}

template<typename T>
void DisjointSet<T>::union_nodes(std::size_t x, std::size_t y)
{
    auto set_x = find_set(x);
    auto set_y = find_set(y);
    if(set_x != set_y) link(set_x, set_y);
}

template<typename T>
T& DisjointSet<T>::value_of(std::size_t indx)
{
    return get_node(indx).m_data;
}

template<typename T>
const T& DisjointSet<T>::value_of(std::size_t indx) const
{
    return get_node(indx).m_data;
}

template<typename T>
typename DisjointSet<T>::Node& DisjointSet<T>::get_node(std::size_t indx) const
{
    typename std::map<std::size_t, Node>::const_iterator itr = m_nodes.find(indx);
    if(itr != m_nodes.end())
    {
        return const_cast<Node&>(itr->second);
    }
    else
    {
        assert(indx && "No such node");
    }
}

template<typename T>
void DisjointSet<T>::link(std::size_t x, std::size_t y)
{
    auto& node_x = get_node(x);
    auto& node_y = get_node(y);
    auto& rank_x = node_x.m_rank;
    auto& rank_y = node_y.m_rank;
    if(rank_x > rank_y)
    {
        node_y.m_parent = x;
    }
    else
    {
        node_x.m_parent = y;
        if(rank_x == rank_y) ++rank_y;
    }
    node_y.m_count += node_x.m_count;
    --m_treeSize;
}

#endif // DISJOINTSET_H
