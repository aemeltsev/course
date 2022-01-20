#ifndef BHEAP_H
#define BHEAP_H

#include <cassert>
#include <cstdint>
#include <functional> //std::forvard
#include <vector>
#include <initializer_list>

template <typename T, typename Compare = std::less<T>>
class BHeap
{
    Compare _compare;
    std::vector<T> _data;
    std::vector<std::pair<std::size_t, std::size_t>> _tech_detl;

    std::size_t parent(std::size_t indx)
    {
        return (indx - 1) >> 1; //(indx-1)/2
    }

    std::size_t ch_left(std::size_t indx)
    {
        return (indx << 1) + 1; //(index*2)+1
    }

    std::size_t ch_right(std::size_t indx)
    {
        return (indx << 1) + 2; //(index*2)+2
    }

    void shift_down(std::size_t i)
    {
        std::size_t bigger;
        std::size_t max = _data.size();

        while (i<max)
        {
            bigger = i; //bigger - mean value in array
            const auto chleft = ch_left(i); //2*i + 1
            const auto chright = ch_right(i); //2*i + 2

            //left child
            if(chleft < max && _compare(_data[chleft], _data[bigger]))
            {
                bigger = chleft;
            }
            //right child
            if(chright < max && _compare(_data[chright], _data[bigger]))
            {
                bigger = chright;
            }
            if(bigger == i)
            {
                return;
            }
            std::swap(_data[i], _data[bigger]);
            _tech_detl.emplace_back(std::make_pair(i, bigger));
            i = bigger;
        }
    }

    void shift_up(std::size_t i)
    {
        while((i > 0) && _compare(_data[parent(i)], _data[i]))
        {
            const auto  p = parent(i);
            std::swap(_data[i], _data[p]);
            i=p;
        }
    }

    void build_heap()
    {
        int64_t i = (_data.size() >> 1) - 1;
        for(;i >= 0; i--)
        {
            shift_down(i);
        }
    }

    void init()
    {
        build_heap();
    }
public:
    explicit BHeap(std::initializer_list<T> list) noexcept
        :_data(list)
    {
        this->init();
    }

    explicit BHeap(const std::vector<T>& in) noexcept
        :_data(in)
    {
        this->init();
    }

    explicit BHeap(std::vector<T>&& in) noexcept
        :_data(std::move(in))
    {
        this->init();
    }

    bool is_empty() const noexcept {return _data.size() == 0;}
    std::size_t size() const noexcept {return _data.size();}

    const T& top() const
    {
        assert(_data.size() > 0);

        return _data.at(0);
    }

    template<class... Args>
    void push(Args&&... args)
    {
        const std::size_t i = _data.size();

        _data.emplace_back(std::forward<Args>(args)...);

        shift_up(i);
    }

    void pop()
    {
        assert(_data.size() > 0);

        _data.at(0) = _data.back();

        _data.pop_back();

        shift_down(0);
    }

    const std::vector<std::pair<std::size_t, std::size_t>>& get_tech_detail() const
    {
        return _tech_detl;
    }
};

#endif // BHEAP_H
