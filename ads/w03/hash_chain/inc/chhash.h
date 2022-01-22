#ifndef CHHASH_H
#define CHHASH_H

#include <vector>
#include <list>
#include <string>
#include <algorithm> //std::lexicographical_compare

#include <cassert>

namespace {
static constexpr std::size_t data_table_size = 256;
static constexpr std::size_t prime = 0x3B9ACA07;
static constexpr std::size_t salt  = 0x00000107;
}

class HashMeta
{
public:
    std::size_t operator()(const std::string& data) const
    {
        auto ipow = [](std::size_t base, std::size_t exp) -> std::size_t
        {
            double result = 1.;
            while(exp != 0)
            {
                if((exp & 1) != 0)
                {
                    result *= base;
                }
                base *= base;
                exp >>= 1;
            }
            return static_cast<std::size_t>(result);
        };

        auto size = data.size();
        std::size_t sum = 0;
        for(std::size_t i=0; i<size; ++i)
        {
            auto i_data = static_cast<std::size_t>(data[i]);
            auto i_salt = ipow(salt, i);
            sum = (sum + i_data * i_salt) % prime;
        }
        return static_cast<std::size_t>(sum % size);
    }
};

class HashLine
{
public:
    //https://stackoverflow.com/questions/34595/what-is-a-good-hash-function
    std::size_t operator()( const std::string& data) const
    {
        auto size = data.size();
        std::size_t h = 0xCBF29CE484222325ULL;
        constexpr std::size_t salt = 0x100000001B3ULL;
        for (std::size_t i = 0; i< size; i++ )
        {
            auto i_data = static_cast<std::size_t>(data[i]);
            h = (h ^ i_data) * salt;
        }
        return h;
    }

    /*uint32_t fnv_hash_1a_32 (const std::string& data)
    {
        auto size = data.size();
        uint32_t h = 0x811C9DC5;
        constexpr uint32_t salt = 0x01000193;
        for (std::size_t i = 0; i<size; ++i)
        {
            auto i_data = static_cast<uint32_t>(data[i]);
            h = (h ^ i_data) * salt;
        }
       return h;
    }*/
};

template <typename HMeta = HashMeta,
          typename HLine = HashLine>
class CHHash
{
    struct Node
    {
        std::size_t _hash;
        std::string _data = " ";

        Node(){}

        Node(const std::string& data)
            :_data(data)
        {}

        Node(const Node& other)
        {
            if(this != &other)
            {
                _data = other._data;
                _hash = other._hash;
            }
        }

        Node& operator=(const Node& other)
        {
            if(this != &other)
            {
                _data = other._data;
                _hash = other._hash;
            }
            return *this;
        }
    };

    HMeta _hmeta;
    HLine _hline;
    std::size_t _tab_size;
    std::vector<std::list<Node>> _chdata;
    using iterator = typename std::list<Node>::iterator;

public:
    CHHash()
        :_tab_size(data_table_size)
        ,_chdata{}
    {}

    explicit CHHash(std::size_t size = data_table_size)
    {
        _tab_size = size;
        _chdata.resize(size);
    }

    bool find(const std::string& data)
    {
        const auto hash = _hmeta(data) % _tab_size;
        bool result = false;
        bool out = false;

        if(!_chdata[hash].empty())
        {
            for(auto bitr = _chdata[hash].begin(); bitr != _chdata[hash].end(); ++bitr)
            {
               out = ((_hline(bitr->_data) % _chdata[hash].size()) == hash)
                        && std::lexicographical_compare(data.begin(), data.end(),
                                                        bitr->_data.begin(), bitr->_data.end());
            }
            if(!out) result = true;
        }
        return result;
    }

    void add(const std::string& data)
    {
        const auto hash = _hmeta(data) % _tab_size;

        if(find(data))
        {
            Node node(data);
            node._hash = _hline(data) % _chdata[hash].size();
            _chdata[hash].push_front(node);
        }
        else{
            Node node(data);
            node._hash = _hline(data) % 1;
            _chdata[hash].push_back(node);
        }
    }

    void del(std::string& data)
    {
        const auto m_hash = _hmeta(data) % _tab_size;
        bool is_exist = false;

        if(!_chdata[m_hash].empty())
        {
            for(auto itr = _chdata[m_hash].begin(); itr != _chdata[m_hash].end(); ++itr)
            {
                if(std::lexicographical_compare(data.begin(), data.end(),
                                                itr->_data.begin(), itr->_data.end()))
                {
                    // found  delete
                    is_exist = true;
                    _chdata[m_hash].erase(itr);
                }
            }
        }
        if(!is_exist)
        {
            return;
        }
    }

    std::vector<std::string> check(const std::size_t num)
    {
        assert(num >_chdata.size() && "Key number out of range");
        auto pos = _chdata[num];
        std::vector<std::string> result;

        if(!pos.empty())
        {
            result.resize(pos.size());

            for(auto itr = pos.begin(); itr != pos.end(); ++itr)
            {
                result.push_back(itr->_data);
            }
        }
        else
        {
            result.push_back(" ");
        }
        return result;
    }
};

#endif // CHHASH_H
