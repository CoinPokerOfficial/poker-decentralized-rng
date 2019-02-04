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

#ifndef DECENTRALIZEDRNG_DECK_INTERFACE_H
#define DECENTRALIZEDRNG_DECK_INTERFACE_H

#include <array>

#ifdef WIN32

    #ifdef DECKRNGLIB_SHARED_EXPORTS
        #define DECKRNGLIB_API __declspec(dllexport)
    #elif defined DECKRNGLIB_SHARED_IMPORTS
        #define DECKRNGLIB_API __declspec(dllimport)
    #else
        #define DECKRNGLIB_API
    #endif

    #define CALL __stdcall
#else
    #define DECKRNGLIB_API
    #define CALL
#endif


namespace DecentralizedRNGDeck
{
    using HandId = unsigned long long;

    using Seed256 = std::array<unsigned char, 32>;
    using Hash256 = std::array<unsigned char, 32>;

    using CardSalt = std::array<unsigned char, 32>;
    using CardHash = std::array<unsigned char, 32>;


    struct HashInfo
    {
        int playerSeatIndex;
        Hash256 hash;
    };

    struct SeedInfo
    {
        int playerSeatIndex;
        Seed256 seed;
    };

    struct NicknameInfo
    {
        int playerSeatIndex;
        char nickname[32];
    };

    struct SaltedCard {
        CardSalt salt;
        char card;
    };

    struct CardVerifyInfo
    {
        int cardIndex;
        SaltedCard card;
    };


    struct BeginHandParams
    {
        HandId                      handId;              // unique hand id
        int                         playerSeatIndex;     // unique per table player seat index
        const CardHash*             initialCardList;     // list of initially shuffled poker card hashes
        int                         initialCardListSize; // list size
        const NicknameInfo*         nicknameList;        // list of players on table
        int                         nicknameListSize;    // list size
        const Seed256::value_type*  inputSeed;           // seed supplied by user from game client (table RNG tab; optional)
        int                         inputSeedSize;       // input seed size (optional)
    };

    struct VerifyHandParams
    {
        HandId                      handId;                // hand id
        const SeedInfo*             seedInfoList;          // list of users secrets
        int                         seedInfoListSize;      // list size
        const CardVerifyInfo*       cardsToVerifyList;     // list of cards seed my the user
        int                         cardsToVerifyListSize; // list size
    };

    struct Result
    {
        enum Enum
        {
            FAILED = 0,
            SUCCEED,
        };
    };


    class IDeckRNG
    {
    public:
        virtual const Hash256* CALL BeginHand(const BeginHandParams& params) = 0;
        virtual const Seed256* CALL GetSeed(const HandId& handId, const HashInfo* hashInfoList, int hashInfoListSize) = 0;
        virtual void CALL AbortHand(const HandId& handId) = 0;
        virtual Result::Enum CALL VerifyHand(const VerifyHandParams& params) = 0;

    public:
        virtual ~IDeckRNG() {}
    };

}//RNG

extern "C"
{
    DECKRNGLIB_API DecentralizedRNGDeck::IDeckRNG* CreateDeckRNG();
    DECKRNGLIB_API void DestroyDeckRNG(DecentralizedRNGDeck::IDeckRNG* rng);
}

#endif //DECENTRALIZEDRNG_DECK_INTERFACE_H
