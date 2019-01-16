# Decentralized RNG utils

Various utility functions that are used to implement [AwardInterface](../award_interface/README.md) and [DeckInterface](../deck_interface/README.md)  

Algorithms used in protocol implementation :
* deck shuffling - Knuth shuffle (a.k.a. the Fisher-Yates shuffle) algorithm with seed 32-bits length.
* hashing - Keccak-256 algorithm.
* pseudo random number generator -  SIMD oriented Fast Mersenne Twister(SFMT)
