// MIT License
//
// Copyright (c) 2019 CoinPoker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef DECENTRALIZEDRNG_UTILS_H
#define DECENTRALIZEDRNG_UTILS_H

#include <memory>
#include <vector>
#include <type_traits>
#include <limits>
#include <cassert>
#include <random>

// hash function
void FIPS202_SHAKE256_PURE(const unsigned char *in, unsigned long long int inLen, unsigned char* out, unsigned long long int outLen);

// fast random number generator
struct Sfmt {
    using result_type = std::uint32_t;

    Sfmt(const std::vector<uint8_t>&);
    Sfmt(uint32_t);
    Sfmt(const Sfmt&);
    ~Sfmt();

    static result_type min();
    static result_type max();
    result_type operator()();

    struct Impl;
    std::unique_ptr<Impl> impl;
};

// private class for uniform distribution
template <typename TValue>
class UniformIntDistribution {
public:
    static_assert(std::is_integral<TValue>::value, "");
    // range is inclusive [a..b]
    UniformIntDistribution(TValue a, TValue b = std::numeric_limits<TValue>::max())
            :_a{ a }, _b{ b }
    {
        assert(a < b);
    }

    template <typename Engine>
    TValue operator()(Engine& eng) const {

        using CommonType = typename std::common_type<TValue, typename Engine::result_type>::type;
        CommonType res;

        auto urange = _b - _a;
        auto erange = eng.max() - eng.min();
        if (erange > urange) {
            //down scale
            auto scale = erange / urange;
            do {
                res = CommonType(eng()) - eng.min();
            } while (res >= scale * urange);
            res /= scale;
        } if (erange < urange) {
            //up scale
            /*
              Note that every value in [0, urange]
              can be written uniquely as

              (erange + 1) * high + low

              where

              high in [0, urange / (erange + 1)]

              and

              low in [0, erange].
            */

            CommonType tmp; // wraparound control
            do
            {
                const CommonType uerange = erange + 1;
                const auto high = UniformIntDistribution<TValue>(0, urange / uerange)(eng);
                const auto low = CommonType(eng()) - eng.min();
                tmp = (uerange * high);
                res = tmp + low;
            }
            while (res > urange || res < tmp);
        } else {
            res = CommonType(eng()) - eng.min();
        }
        return res + _a;
    }
private:
    TValue _a;
    TValue _b;
};

// shuffle algorithm
class ShuffleKnuth {

public:

    template<class RandomIt, class URBG>
    void operator()(RandomIt first, RandomIt last, URBG&& g) const
    {
        typedef typename std::iterator_traits<RandomIt>::difference_type diff_t;
        typedef UniformIntDistribution<diff_t> distr_t;

        diff_t n = last - first;
        for (diff_t i = n - 1; i > 0; --i) {
            using std::swap;
            distr_t dist(0, i);
            swap(first[i], first[dist(g)]);
        }
    }

};


#endif //DECENTRALIZEDRNG_UTILS_H
