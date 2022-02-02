#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <cmath>
#include <cassert>
#include <functional>
#include <algorithm>

namespace sorting {

static constexpr int QS_MIN_SIZE = 0xA;
static constexpr int TS_MIN_MERGE = 0x20;

template<typename T>
void _insertion_sort(T data[], std::size_t left, std::size_t right)
{
    for(std::size_t i = left; i <= right; ++i)
    {
        std::size_t j = i-1;
        while(j >= 0 && data[j] > data[j + 1])
        {
            std::swap(data[j], data[j + 1]);
            --j;
        }
    }
}

template<typename T>
void _merge(T data[], std::size_t left, std::size_t mid, std::size_t right)
{
    std::size_t i = 0;
    std::size_t j = 0;

    T* tmp = new T[right - left];

    while(left + i < mid && mid + j < right)
    {
        if(data[left + i] < data[mid + j])
        {
            tmp[i + j] = data[left + i];
            i++;
        }
        else{
            tmp[i + j] = data[mid + j];
            j++;
        }
    }
    while(left + i < mid)
    {
        tmp[i + j] = data[left + i];
        i++;
    }
    while(mid + j < right)
    {
        tmp[i + j] = data[mid + j];
        j++;
    }

    for(std::size_t p = 0; p < i + j; ++p)
    {
        data[left + p] = tmp[p];
    }

    delete[] tmp;
}

template<typename T>
void _merge_sort(T data[], const std::size_t& size)
{
    std::size_t arr_size = size;
    for(std::size_t i = 1; i < arr_size; i <<= 1)
    {
        for(std::size_t left = 0; left < arr_size - i; left += (i << 1))
        {
            _merge(data, left, left + i, std::min(left + (i << 1), arr_size));
        }
    }
}

std::size_t _parent(std::size_t& i)
{
    return (i - 1) >> 1; // i - 1 / 2
}

std::size_t _lchild(std::size_t& i)
{
    return (i << 1) + 1; // 2 * i + 1
}

std::size_t _rchild(std::size_t& i)
{
    return (i << 1) + 2; // 2 * i + 2

}

template<typename T>
void _shift_down(T data[], std::size_t i, const std::size_t& size)
{
    std::size_t big, left, right;

    while (i < size)
    {
        big = i; // big - mean value in array
        left = _lchild(i);
        right = _rchild(i);
        //left child compare
        if(left < size && data[left] > data[big])
        {
            big = left;
        }
        //right child compare
        if(right < size && data[right] > data[big])
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

template<typename T>
void _build_heap(T data[], const std::size_t& size)
{
    int64_t start = (size >> 1) - 1;
    while(start >= 0)
    {
        _shift_down(data, start, size);
        --start;
    }
}

template<typename T>
void _heap_sort(T data[], const std::size_t& size)
{
    _build_heap(data, size);
    int64_t end = size - 1;

    while(end > 0)
    {
        std::swap(data[end], data[0]);
        _shift_down(data, 0, end);
        --end;
    }
}

template<typename T>
std::size_t _partition(T data[], std::size_t low, std::size_t high)
{
    std::size_t pivot = data[((high + low) >> 1)]; //pivot

    std::size_t i = low; // index left
    std::size_t j = high; // index right

    while(i <= j)
    {
        while (data[i] < pivot)
            i++;

        while(data[j] > pivot)
            j--;

        if(i >=j) break;

        std::swap(data[i++], data[j--]);
    }
    return j;
}

template<typename T>
void _quick_sort(T data[], std::size_t low, std::size_t high)
{
    if(high - low <= QS_MIN_SIZE)
    {
        _insertion_sort(data, low, high);
        return;
    }

    // see: https://ru.stackoverflow.com/questions/446550/quicksort-метод-медианы-из-трех
    auto median = [&, data](std::size_t low, std::size_t mid, std::size_t high) -> std::size_t
    {
        if(data[low] > data[mid])
        {
            if(data[high] > data[low])
            {
                return low;
            }
            return (data[mid] < data[high]) ? mid : high;
        }
        if(data[high] > data[mid])
        {
            return mid;
        }
        return (data[low] < data[high]) ? mid : high;
    };

    // heuristic
    std::size_t med = median(data[low], data[(low + high) >> 1], data[high]);
    std::swap(data[med], data[(low + high) >> 1]);

    std::size_t i = _partition(data, low, high);
    _quick_sort(data, low, i);
    _quick_sort(data, i + 1, high);
}

std::size_t _get_min(std::size_t num)
{
    auto flag = 0;
    while(num >= 64)
    {
        flag |= num & 1;
        num >>= 1;
    }
    return num + flag;
}

template<typename T>
void _tim_sort(T data[], std::size_t size)
{
    std::size_t run = TS_MIN_MERGE;
    for(std::size_t i = 0; i < size; i += TS_MIN_MERGE)
    {
        _insertion_sort(data, i, std::min((i + run-1), (size - 1)));
    }

    for(std::size_t j = TS_MIN_MERGE; j < size; j <<= 1)
    {
        for(std::size_t left = 0; left < size; left += (j << 1))
        {
            std::size_t mid = left + j - 1;
            std::size_t right = std::min((left + (j << 1) - 1), (size - 1));

            if(mid < right)
            {
                _merge(data, left, mid, right);
            }
        }
    }
}

} //namespace collection

#endif //SORTS_H
