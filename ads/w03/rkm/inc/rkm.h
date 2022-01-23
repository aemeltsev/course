#ifndef RKM_H
#define RKM_H

#include <vector>
#include <string>

class RKM
{
    static const std::size_t module = 0x107ULL;
    static const std::size_t prime = 0x3B9ACA07ULL;

    std::string _pattern;
    std::size_t _pattern_size;
    std::size_t _diff_hash;

    // https://stackoverflow.com/questions/8496182/calculating-powa-b-mod-n/8498251
    template <typename T>
    T pow_mod(T base, T exp, T modulo)
    {
        base %= modulo;
        T result = 1;

        while (exp > 0)
        {
            if (exp & 1)
            {
                result = (result * base) % modulo;
            }

            base = (base * base) % modulo;
            exp >>= 1;
        }
        return result;
    }

public:
    RKM(const std::string& pattern)
        :_pattern(pattern)
        ,_pattern_size(pattern.size())
        ,_diff_hash(pow_mod<std::size_t>(module, static_cast<std::size_t>(_pattern_size - 1), prime))
    {}

    bool compare(const std::string& text, std::size_t offset)
    {
        std::size_t index;

        for(index = 0; index < _pattern_size && _pattern[index] == text[offset + index]; ++index);

        return index == _pattern_size;
    }

    std::vector<std::size_t> rkm(const std::string& text)
    {
        // 1. define matching result vector and initial text values
        std::vector<std::size_t> result;

        std::size_t text_size = text.size();
        std::size_t last_index = text_size - _pattern_size;

        std::size_t pattern_hash = 0;
        std::size_t first_win_hash = 0;
        std::size_t index = 0;

        /* 2. calculate pattern hash(as example "CCD" hash equal 4652275 in ring of the prime value
         *    and calculate first window hash with pattern size(as example "ABCCDDAEFG"
         *    first window - "ABC" and hash - 4513410
         */
        while(index < _pattern_size)
        {
            pattern_hash = (module * pattern_hash + _pattern[index]) % prime;
            first_win_hash = (module * first_win_hash + text[index]) % prime;
            ++index;
        }

        /* 3. create contain window hashes vector and push to it first window hash */
        std::vector<std::size_t> win_hashes;
        win_hashes.reserve(last_index + 1);
        win_hashes.push_back(first_win_hash);

        /* 4. matching */
        for(index = 0; index <= last_index; ++index)
        {
            /* compare pattern hash/window hash and by to character
             *  if equal push index to vector
             */
            if(pattern_hash == win_hashes[index])
            {
                if(compare(text, index))
                {
                    result.push_back(index);
                }
            }

            /* and create next window rolling hash */
            if(index < last_index)
            {
                /* https://stackoverflow.com/question/20412405/rolling-hash-in-rabin-karp
                 * (module(263) * (old_hash - to_delete_char * pow_module_pattern_length) + text_char) % prime;
                 */
                std::size_t new_win_hash = (module * (win_hashes[index] - text[index] * _diff_hash) + text[index + _pattern_size]) % prime;
                win_hashes.push_back(new_win_hash);
            }
        }
        return result;
    }
};

#endif // RKM_H
