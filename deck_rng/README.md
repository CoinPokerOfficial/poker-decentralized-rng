# DeckRNG shared library

Implementation of [DeckInterface](../deck_interface/README.md) for [CoinPoker](https://coinpoker.com) client.
It creates single shared library, -`DeckRNG`.
 
## How to test

At first CoinPoker client will try to load `PokerRNG_custom` library, if it's not found - original `PokerRNG` library will be loaded.

So in order to test it you need to rename shared library to `PokerRNG_custom` and place it in CoinPoker client installation directory.
