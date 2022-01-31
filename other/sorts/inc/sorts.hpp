#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>

namespace collection {

static constexpr int QS_MIN_SIZE = 0xA;

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
void _merge_sort(T data[], std::size_t size)
{
    for(std::size_t i = 1; i < size; i <<= 1)
    {
        for(std::size_t left = 0; left < size - i; left += (i << 1))
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

template<typename T>
void _shift_down(std::vector<T>& data, int64_t i, int64_t size)
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

template<typename T>
void _build_heap(std::vector<T>& data)
{
    int64_t start = (data.size() >> 1) - 1;
    while(start >= 0)
    {
        _shift_down(data, start, data.size());
        --start;
    }
}

template<typename T>
void _heap_sort(std::vector<T>& data)
{
    _build_heap(data);
    int64_t end = data.size() - 1;

    while(end > 0)
    {
        std::swap(data[end], data[0]);
        _shift_down(data, 0, end);
        --end;
    }
}

template<typename T>
int64_t _partition(std::vector<T>& data, int64_t low, int64_t high)
{
    auto pivot = data[std::floor((high + low) >> 1)]; //pivot

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

template<typename T>
void _quick_sort(std::vector<T>& data, int64_t low, int64_t high)
{
    if(high - low <= QS_MIN_SIZE)
    {
        _insertion_sort(data, false);
        return;
    }

    //TODO heuristic
    //int64_t med = median(data[low], data[(low + higha) >> 1], data[high]);
    //std::swap(data[med], data[(low + higha) >> 1]);

    auto i = _partition(data, low, high);
    _quick_sort(data, low, i);
    _quick_sort(data, i + 1, high);
}

int64_t _get_min(int64_t num)
{

}

template<typename T>
void _insertion_sort(std::vector<T>& data, bool optimise = true)
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

template<typename T>
void _tim_sort(std::vector<T>& data)
{

}

} //namespace collection

#endif //SORTS_H
