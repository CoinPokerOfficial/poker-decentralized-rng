#include "sfmt.h"

#include <limits>

#include "SFMT-1.5.1/SFMT.c"

struct Sfmt::Impl {
    sfmt_t sfmt = {};
};

// SFMT from http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/SFMT-src-1.5.1.zip
Sfmt::Sfmt(const std::vector<uint8_t>& seed)
    : impl(new Impl)
{
    assert(!(seed.size() % sizeof(uint32_t)));

    sfmt_init_by_array(&impl->sfmt, reinterpret_cast<const uint32_t*>(seed.data()), seed.size()/4);
}

Sfmt::Sfmt(uint32_t seed)
    : impl(new Impl)
{
    sfmt_init_gen_rand(&impl->sfmt, seed);
}

Sfmt::Sfmt(const Sfmt& rhs)
    : impl(new Impl(*rhs.impl))
{
}

Sfmt::~Sfmt() {
}

Sfmt::result_type Sfmt::min() {
    return std::numeric_limits<result_type>::min();
}

Sfmt::result_type Sfmt::max() {
    return std::numeric_limits<result_type>::max();
}

Sfmt::result_type Sfmt::operator()() {
    return sfmt_genrand_uint32(&impl->sfmt);
}
