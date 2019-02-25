# Decentralized RNG libraries for [CoinPoker](https://coinpoker.com) client

This project consist of multiple projects that are used to implement decentralized card shuffle/verification for hand and award structure selection.

The purpose of this project is that any client, with some knowledge of c++, can verify and test decentralized rng protocol themselves.  

* [AwardInterface](award_interface/README.md) - defines decentralized rng interface for award selection.
* [DeckInterface](deck_interface/README.md) - defines decentralized rng interface for poker hand shuffling and verification.
* [Utils](utils/README.md) - various utily functions that is used in implementing decentralized rng protocols.
* [AwardRNG](award_rng/README.md) - shared library that implements [AwardInterface](award_interface/README.md).
* [DeckRNG](deck_rng/README.md) - shared library that implements [ShuffleInterface](deck_interface/README.md).

### Building instructions

Project uses `CMake` as build generator. In order to test/modify [AwardRNG](award_rng/README.md) or [DeckRNG](deck_rng/README.md) yourself, generate project to that builds shared libs.
Enter following commands from project root.
```shell
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
```
After project is built, rename shared libraries `DeckRNG`, `AwardRNG` to `DeckRNG_custom`, `AwardRNG_custom` and copy to poker client root directory.
