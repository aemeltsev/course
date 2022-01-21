#ifndef NHASH_H
#define NHASH_H

#include <vector>
#include <list>
#include <string>
#include <algorithm> //std::find_if

namespace {
static constexpr std::size_t data_table_size = 256;
}

class NHash
{
    struct Node
    {
        std::size_t _key;
        std::string _value;

        Node(const std::size_t key, const std::string& value)
            :_key(key)
            ,_value(value)
        {}

        Node(const Node& other)
        {
            if(this != &other)
            {
             _key = other._key;
             _value = other._value;
            }
        }

        Node& operator=(const Node& other)
        {
            if(this != &other)
            {
                _key = other._key;
                _value = other._value;
            }
            return *this;
        }
    };

    std::size_t _tab_size;
    std::vector<std::list<Node>> _tab_data;
    using iterator = typename std::list<Node>::iterator;

    //xorshift seed generator
    std::size_t splitmix64(std::size_t key)
    {
        constexpr std::size_t salt1 = 0x9E3779B97f4A7C15;
        constexpr std::size_t salt2 = 0xBF58476D1CE4E5B9;
        constexpr std::size_t salt3 = 0x94D049BB133111EB;

        std::size_t result = (key += salt1);
        result = (result ^ (result >> 30)) * salt2;
        result = (result ^ (result >> 27)) * salt3;
        return result ^ (result >> 31);
    }

public:
    NHash()
        :_tab_size(data_table_size)
        ,_tab_data{}
    {}

    explicit NHash(const std::size_t size = data_table_size)
        :_tab_size(size)
    {
        _tab_data.resize(size);
    }

    iterator find(std::size_t key)
    {
        const auto hash = splitmix64(key) % _tab_size;
        auto find_it = [&key](Node& node){
            return node._key == key;
        };

        if(!_tab_data[hash].empty())
        {
            auto result = std::find_if(_tab_data[hash].begin(),
                                        _tab_data[hash].end(),
                                        find_it);

            if(result != _tab_data[hash].end())
            {
                return result;
            }
        }
        return _tab_data.back().end();
    }

    iterator t_end(){return _tab_data.back().end();}

    void add(const std::size_t key, const std::string& value)
    {
        auto result = find(key);
        const auto hash = splitmix64(key) % _tab_size;
        if(_tab_data[hash].size() == 1
                && result->_value == " "
                && result->_key == 0)
        {

        }
        /* if in bucket exist node with current hash, rewrite him
         */
        if(result != t_end())
        {
            result->_key = key;
            result->_value = value;
        }
        else
        {

            Node node(key, value);
            _tab_data[hash].push_back(node);
        }
    }

    std::string& get(const std::size_t key)
    {
        auto result = find(key);

        if(result != t_end())
        {
            return result->_value;
        }
        else{
            const auto hash = splitmix64(key) % _tab_size;
            Node node(key, " ");
            _tab_data[hash].emplace_back(node);
            return _tab_data[hash].back()._value;
        }
    }

    void del(const std::size_t key)
    {
        const auto hash = splitmix64(key) % _tab_size;
        if(!_tab_data[hash].empty() && _tab_data[hash].size() == 1)
        {
            _tab_data[hash].front()._value = " ";
            _tab_data[hash].front()._key = 0;
        }

        auto result = find(key);
        if(result != t_end())
        {
            _tab_data[hash].erase(result);
        }
    }
};
#endif // NHASH_H
