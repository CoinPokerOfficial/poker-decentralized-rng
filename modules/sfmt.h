#ifndef SFMT_H
#define SFMT_H

#include <memory>
#include <vector>

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

#endif /* SFMT_H */
