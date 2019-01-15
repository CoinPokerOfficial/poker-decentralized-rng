# Decentralized RNG libraries for [CoinPoker](https://coinpoker.com) client

This project consist of multiple projects that are used to implement decentralized card shuffle/verification for hand and award structure selection.

The purpose of this project is that any client, with some knowledge of c++, can verify and test decentralized rng protocol themselves.  

* [DecentralizedRNGAwardInterface](decentralized_rng_award_interface/README.md) - defines decentralized rng interface for award selection.
* [DecentralizedRNGHandInterface](decentralized_rng_hand_interface/README.md) - defines decentralized rng interface for poker hand shuffling and verification.
* [DecentralizedRNGUtils](decentralized_rng_utils/README.md) - various utily functions that is used in implementing decentralized rng protocols.
* [PokerAwardRNG](poker_award_rng/README.md) - shared library that implements [DecentralizedRNGAwardInterface](decentralized_rng_award_interface/README.md).
* [PokerHandRNG](poker_hand_rng/README.md) - shared library that implements [DecentralizedRNGHandInterface](decentralized_rng_hand_interface/README.md).
