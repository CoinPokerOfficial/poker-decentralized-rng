### Decentralized RNG library for [CoinPoker](https://coinpoker.com) client

#### Implementation details:

Validating poker hands is done in four steps:

1. ##### Receiving hand to be player information and returning the hash of a user generated secret (aka seed)

    ```
    const Hash256* BeginHand(const BeginHandParams& params);

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
    ```

    At this step the implementer should generate a random secret and pass its hash to the caller. If inputSeed is supplied one could use it as input.  
    Implementer should store the card hash information mapped to the hand id for later verification.  
    If valid resulting hash is not returned in time server will generate one.
    
    Keccak 256 is used as a hashing function (pure, ethereum / shake-256 with 0x1 as delimited suffix)

2. ##### Receiving the hashes of other players and the operator generated secrets and returning your own secret

    ```
    const Seed256* GetSeed(const HandId& handId, const HashInfo* hashInfoList, int hashInfoListSize);
    ```

    If a valid seed is not returned the server will abort the hand. Doing this more then once will suspend the user from participating in the shuffle.

3. ##### Receiving this callback if hand is aborted

    ```
    void AbortHand(const HandId& handId);
    ```

4. ##### Receiving user seeds and initial card values and returning verification result

    ```
    Result::Enum VerifyHand(const VerifyHandParams& params);

    struct VerifyHandParams
    {
        HandId                      handId;                // hand id
        const SeedInfo*             seedInfoList;          // list of users secrets
        int                         seedInfoListSize;      // list size
        const CardVerifyInfo*       cardsToVerifyList;     // list of cards seed my the user
        int                         cardsToVerifyListSize; // list size
    };
    ```

    seedInfoList can be used here to verify hashInfoList received from the GetSeed call.  
    To verify cardsToVerifyList you should concat card salt, /0 and plain card value before applying hash:

    `HASH = SALT\0card`

#### Build instructions:

* ##### Windows Mingw (7.1):
    >g++ -DSFMT_MEXP=19937 decentralized_rng_dll.cpp modules/sfmt.cpp modules/keccak.cpp -shared -fPIC -o PokerRNG.dll


* ##### Mac OS X clang:

    >g++ -std=c++1z -DSFMT_MEXP=19937 decentralized_rng_dll.cpp modules/sfmt.cpp modules/keccak.cpp -shared -fPIC -o PokerRNG.dylib

Deck Shuffling - Knuth shuffle (a.k.a. the Fisher-Yates shuffle) algorithm with seed 32-bits length.  
Hashing - Keccak-256 algorithm.

Detailed description of CoinPoker decentralized RNG protocol can be found [here](https://coinpoker.com/downloads/CoinPoker_RNG.pdf).

