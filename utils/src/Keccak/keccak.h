#ifndef KECCAK_H
#define KECCAK_H

// took Keccak-more-compact.c from https://github.com/gvanas/KeccakCodePackage (Standalone/CompactFIPS202/C/Keccak-more-compact.c)
// pure implementation (aka ethereum / shake-256 with 0x1 as delimited suffix)

void FIPS202_SHAKE256_PURE(const unsigned char *in, unsigned long long int inLen, unsigned char* out, unsigned long long int outLen);

#endif /* KECCAK_H */
