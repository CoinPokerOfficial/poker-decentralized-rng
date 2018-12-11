#pragma once

#include <type_traits>

namespace RNG
{


    template <typename TValue>
    class UniformIntDistribution {
    public:
        static_assert(std::is_integral<TValue>::value, "");
        UniformIntDistribution(TValue a, TValue b = std::numeric_limits<TValue>::max())
            :_a{ a }, _b{ b }
        {
            assert(a < b);
        }

        template <typename Engine>
        TValue operator()(Engine& eng) {
            auto urange = _b - _a;
            auto erange = eng.max() - eng.min();
            assert((unsigned)erange >(unsigned)urange);
            auto scale = erange / urange;
            while (true) {
                auto res = eng() - eng.min();
                if (res >= scale * urange)
                    continue;
                return res / scale + _a;
            }
        }
    private:
        TValue _a;
        TValue _b;
    };



    template<class RandomIt, class URBG>
    void shuffle_knuth(RandomIt first, RandomIt last, URBG&& g)
    {
        typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
        typedef UniformIntDistribution<diff_t> distr_t;

        diff_t n = last - first;
        for (diff_t i = n - 1; i > 0; --i) {
            using std::swap;
            distr_t D(0, i);
            swap(first[i], first[D(g)]);
        }
    }

}//RNG