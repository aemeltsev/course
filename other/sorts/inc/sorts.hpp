#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <cmath>
#include <functional>

namespace collection {

/*
 * Select sort by type, use O(nlogn) complexity
 */
enum class typeSort
{
    MS,
    HS,
    QS,
    TS
};

/*
 * Common sorting class
 * T - type of contain element,
 * SType - sort type,
 * Compatar - functor for comparisons
 *
 */
template< typename T,
          typeSort SType = typeSort::HS,
          typename Comparator = std::greater<T>>
class adv_sort
{
    static constexpr int QS_MIN_SIZE = 0xA;
    Comparator _comparator;

    void _merge(std::vector<T>& data, int64_t left, int64_t mid, int64_t right)
    {
        int64_t i_left = 0;
        int64_t i_right = 0;
        std::vector<int64_t> tmp(right - left);

        while(left + i_left < mid && mid + i_right < right)
        {
            if(_comparator(data[mid + i_right], data[left + i_left]))
            {
                tmp[i_left + i_right] = data[left + i_left];
                ++i_left;
            }
            else{
                tmp[i_left + i_right] = data[mid + i_right];
                ++i_right;
            }
        }
        while(left + i_left < mid) {
            tmp[i_left + i_right] = data[left + i_left];
            ++i_left;
        }
        while(mid + i_right < right) {
            tmp[i_left + i_right] = data[mid + i_right];
            ++i_right;
        }
        for(int64_t i=0; i<i_left + i_right; ++i)
        {
            data[left + i] = tmp[i];
        }
    }

    void _merge_sort(std::vector<T>& data)
    {
        int64_t size = data.size();
        for(int64_t i = 1; i < size; i <<= 1)
        {
            for(int64_t left = 0; left < size - 1; left += (i << 1))
            {
                _merge(data, left, left + i, std::min(left + (i << 1), size));
            }
        }
    }

    int64_t _parent(int64_t i)
    {
        return (i - 1) >> 1; // i - 1 / 2
    }

    int64_t _lchild(int64_t i)
    {
        return (i << 1) + 1; // 2 * i + 1
    }

    int64_t _rchild(int64_t i)
    {
        return (i << 1) + 2; // 2 * i + 2

    }

    void _sift_down(std::vector<T>& data, int64_t i, int64_t size)
    {
        int64_t big, left, right;

        while (i < size)
        {
            big = i; // big - mean value in array
            left = _lchild(i);
            right = _rchild(i);
            //left child compare
            if(left < size && _comparator(data[left], data[big]))
            {
                big = left;
            }
            //right child compare
            if(right < size && _comparator(data[right], data[big]))
            {
                big = right;
            }
            if(big == i)
            {
                return;
            }
            std::swap(data[i], data[big]);
            i = big;
        }
    }

    void _build_heap(std::vector<T>& data)
    {
        int64_t start = (data.size() >> 1) - 1;
        while(start >= 0)
        {
            _sift_down(data, start, data.size());
            --start;
        }
    }

    void _heap_sort(std::vector<T>& data)
    {
        _build_heap(data);
        int64_t end = data.size() - 1;

        while(end > 0)
        {
            std::swap(data[end], data[0]);
            _sift_down(data, 0, end);
            --end;
        }
    }

    int64_t _partition(std::vector<T>& data, int64_t low, int64_t high)
    {
        auto pivot = data[std::floor((high + low) >> 2)]; //pivot

        int64_t i = low - 1; // index left
        int64_t j = high + 1; // index right

        while(true)
        {
            do{
                ++i;
            } while (data[i] < pivot);

            do{
                --j;
            } while(data[i] > pivot);

            if(i >=j) return j;

            std::swap(data[i], data[j]);
        }
    }

    void _quick_sort(std::vector<T>& data , int64_t low, int64_t high)
    {
        if(high - low <= QS_MIN_SIZE)
        {
            _insertion_sort(data, low, high);
            return;
        }
        int64_t median = std::nth_element(data[low], data[(low + high) >> 1], data[high]);
        std::swap(data[median], data[(low + high) >> 1]);
        auto i = _partition(data, low, high);
        _quick_sort(data, low, i);
        _quick_sort(data, i + 1, high);
    }

    int64_t _get_min(int64_t num)
    {

    }

    void _insertion_sort(std::vector<T>& data, int64_t left, int64_t right, bool optimise = true)
    {
        int64_t size = data.size();

        auto bsearch = [&, data]( int64_t key, int64_t left, int64_t right) -> int64_t
        {
            while(left < right - 1) {
                int64_t med = (left + right) >> 1;

                if(data[med] < key)
                    left = med;
                else
                    right = med;
            }
            return right;
        };

        if(optimise)
        {
            for(int64_t i = 1; i < size; ++i)
            {
                int64_t j = i-1;
                auto k  = bsearch(data[i], 0, j);
                for(auto m = j; m < k; ++m)
                    std::swap(data[m], data[m + 1]);
            }
        }
        else{
            for(int64_t i = 1; i < size; ++i)
            {
                int64_t j = i-1;
                while(j >= 0 && data[j] > data[j + 1])
                {
                    std::swap(data[j], data[j + 1]);
                    --j;
                }
            }
        }
    }

    void _tim_sort(std::vector<T>& data)
    {

    }

public:
    adv_sort()
    {}

    std::vector<T> sort(std::vector<T>& data)
    {

        switch(SType)
        {
        case typeSort::HS:
            _heap_sort(data);
            break;
        case typeSort::MS:
            _merge_sort(data);
            break;
        case typeSort::QS:
            _quick_sort(data, 0, data.size()-1);
            break;
        case typeSort::TS:
            break;
        }
        return data;
    }
};

}
#endif
