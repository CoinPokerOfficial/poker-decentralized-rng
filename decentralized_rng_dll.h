#pragma once

#include <array>

#ifdef WIN32
    #ifdef RNGLIBRARY_EXPORTS  
        #define RNGLIBRARY_API __declspec(dllexport)   
    #else  
        #define RNGLIBRARY_API __declspec(dllimport)   
    #endif  
    
    #define CALL __stdcall
#else
    #define RNGLIBRARY_API
    #define CALL
#endif


namespace RNG
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


    class IDecentralizedRandomNumberGenerator
    {
    public:
        virtual const Hash256* CALL BeginHand(const BeginHandParams& params) = 0;
        virtual const Seed256* CALL GetSeed(const HandId& handId, const HashInfo* hashInfoList, int hashInfoListSize) = 0;
        virtual void CALL AbortHand(const HandId& handId) = 0;
        virtual Result::Enum CALL VerifyHand(const VerifyHandParams& params) = 0;

    public:
        virtual ~IDecentralizedRandomNumberGenerator() {}
    };
    
}//RNG

extern "C"
{
    RNGLIBRARY_API RNG::IDecentralizedRandomNumberGenerator* CreateRNG();
    RNGLIBRARY_API void DestroyRNG(RNG::IDecentralizedRandomNumberGenerator* rng);
}
