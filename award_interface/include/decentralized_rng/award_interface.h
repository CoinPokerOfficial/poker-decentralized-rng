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

#ifndef DECENTRALIZEDRNG_AWARD_INTERFACE_H
#define DECENTRALIZEDRNG_AWARD_INTERFACE_H

#include <cstdint>
#include <array>

#ifdef WIN32

    #ifdef AWARDRNGLIB_SHARED_EXPORTS
        #define AWARDRNGLIB_API __declspec(dllexport)
    #elif defined AWARDRNGLIB_SHARED_IMPORTS
        #define AWARDRNGLIB_API __declspec(dllimport)
    #else
        #define AWARDRNGLIB_API
    #endif

    #define CALL __stdcall
#else
    #define AWARDRNGLIB_API
    #define CALL
#endif

namespace DecentralizedRNGAward
{
    typedef std::array<uint8_t, 32> Seed256;

    enum Result
    {
        Failure,
        Success,
        Error
    };

    class IAwardRNG
    {
    public:

        virtual Result CALL Clear() = 0;
        virtual Result CALL Begin(uint32_t game_id) = 0;
        virtual Result CALL Seed(const char* name, uint32_t table_id, uint32_t seat_index, const Seed256& seed) = 0;

        virtual Result CALL Hash() = 0;

        virtual uint32_t CALL GetRange() const = 0;
        virtual uint32_t CALL GetAwardNumber() const = 0;

        virtual Result CALL Destroy() = 0;

        virtual const char* CALL GetOutput() const = 0;

    protected:

        virtual ~IAwardRNG() {};
    };
}

extern "C"
{
    AWARDRNGLIB_API DecentralizedRNGAward::IAwardRNG* CreateAwardRNG();
    AWARDRNGLIB_API void DestroyAwardRNG(DecentralizedRNGAward::IAwardRNG* rng);
}

#endif // DECENTRALIZEDRNG_AWARD_INTERFACE_H
