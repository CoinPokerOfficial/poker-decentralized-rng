# DeckRNG shared library

Implementation of [DeckInterface](../deck_interface/README.md) for [CoinPoker](https://coinpoker.com) client.
It creates single shared library, -`DeckRNG`.
 
## How to test

At first CoinPoker client will try to load `DeckRNG_custom` library, if it's not found - original `DeckRNG` library will be loaded.

So in order to test it you need to rename shared library to `DeckRNG_custom` and place it in CoinPoker client installation directory.
