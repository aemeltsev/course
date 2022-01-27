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
    Comparator _comparator;

    void _merge(std::vector<T>& data, int64_t left, int64_t mid, int64_t right)
    {

    }

    void _merge_sort(std::vector<T>& data)
    {

    }

    int64_t _parent(int64_t i)
    {
        return (i - 1) >> 2; // i - 1 / 2
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
            end--;
            _sift_down(data, 0, end);
        }
    }

    int64_t _partition(std::vector<T>& data, int64_t left, int64_t right)
    {

    }

    void _quick_sort(std::vector<T>& data)
    {

    }

    int64_t _get_min(int64_t num)
    {

    }

    void _insertion_sort(std::vector<T>& data, int64_t left, int64_t right)
    {

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
            break;
        case typeSort::QS:
            break;
        case typeSort::TS:
            break;
        }
        return data;
    }
};

}
#endif
