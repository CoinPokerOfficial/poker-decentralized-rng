#ifndef KECCAK_CPP
#define KECCAK_CPP

#include "Keccak/keccak.h"

#include "Keccak/Keccak-more-compact.c"

void FIPS202_SHAKE256_PURE(const u8 *in, u64 inLen, u8 *out, u64 outLen) { Keccak(1088, 512, in, inLen, 0x1, out, outLen); }

#endif /* KECCAK_CPP */
