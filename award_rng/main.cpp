#include <random>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include <decentralized_rng/utils.h>
#include <decentralized_rng/award_interface.h>

#define VERSION "1.0.0"

namespace DecentralizedRNGAward
{
    typedef Seed256 Hash256;

    enum Origin
    {
        None,
        Player,
        System,
        Unknown = 255
    };

    struct InfoSeed
    {
        Seed256 seed{};

        uint32_t table_id{ 0 };
        uint32_t seat_index{ 0 };

        Origin origin{ None };

        std::string name{};
    };

    struct InfoHash : public InfoSeed
    {
        InfoHash(const InfoSeed& value) : InfoSeed(value) {}

        Hash256 hash;
    };

    struct Game
    {
        uint32_t game_id{ 0 };

        Hash256 combined{};

        std::vector<InfoSeed> received;
        std::vector<InfoHash> committed;
    };

    class AwardRNG : public IAwardRNG
    {
    public:
        virtual Hash256 GetHash(const Seed256& seed) const;
        virtual Hash256 GetHash(const std::vector<Hash256>& input) const;

        virtual Seed256 GetSeed(const std::string& input) const;

        virtual Seed256 GetRandomSeed() const;
        virtual bool    Seeded(const Seed256& seed) const;

        virtual Result CALL Clear();
        virtual Result CALL Begin(uint32_t game_id);
        virtual Result CALL Seed(const char* name, uint32_t table_id, uint32_t seat_index, const Seed256& seed);

        virtual Result CALL Hash();

        virtual uint32_t CALL GetRange() const;
        virtual uint32_t CALL GetAwardNumber() const;

        virtual const char* CALL GetOutput() const;

        virtual Result CALL Destroy();

    protected:

        Game m_game;

        mutable std::string m_output;
    };

    template<typename T>
    std::string GetHex(const T &container)
    {
        std::string result = "0x";
        std::ostringstream oss;
        oss << std::setfill('0');

        for (auto i = container.begin(); i != container.end(); i++)
        {
            oss << std::setw(2) << std::hex << static_cast<int>((*i));
        }

        return result += oss.str();
    }

    template<typename T>
    std::string GetAscii(const T &container)
    {
        std::ostringstream oss;

        for (auto i = container.begin(); i != container.end(); i++)
        {
            if (std::isgraph(static_cast<uint8_t>(*i)) != 0)
            {
                oss << static_cast<char>(*i);
            }
            else
            {
                oss << ".";
            }
        }

        return oss.str();
    }

    template<typename T>
    void SortInfo(T &container)
    {
        std::sort(container.begin(), container.end(), [](const InfoHash& a, const InfoHash& b)
        {
            if (a.table_id < b.table_id)
                return true;

            if (a.seat_index < b.seat_index)
                return true;

            return false;
        });
    }

    std::string GetSeparator()
    {
        std::ostringstream oss;
        oss << std::setfill('-') << std::setw(72) << "-";
        return oss.str();
    }

    std::string GetOrigin(Origin origin)
    {
        switch (origin)
        {
            case Origin::None:
                return "None";

            case Origin::Player:
                return "Player";

            case Origin::System:
                return "System";

            default:
                break;
        }

        return "Unknown";
    }

    template<typename T>
    std::string GetOutputSeed(const T &container, const std::string &prefix)
    {
        std::stringstream result;

        result << prefix << "Origin: " << GetOrigin(container.origin) << std::endl;

        if (container.table_id != 0)
        {
            result << prefix << "Table: " << container.table_id << std::endl;
            result << prefix << "Seat: " << container.seat_index << std::endl;
        }

        result << prefix << "Name: " << container.name << std::endl;
        result << prefix << "Seed: " << GetAscii(container.seed) << std::endl;
        result << prefix << "Seed: " << GetHex(container.seed) << std::endl;

        return result.str();
    }

    template<typename T>
    std::string GetOutputHash(const T &container, const std::string &prefix)
    {
        std::stringstream result;

        result << prefix << "Hash: " << GetHex(container.hash) << std::endl;

        return result.str();
    }

    Hash256 AwardRNG::GetHash(const Seed256& seed) const
    {
        Hash256 result;

        FIPS202_SHAKE256_PURE(seed.data(), seed.size(), result.data(), result.size());

        return result;
    }

    Hash256 AwardRNG::GetHash(const std::vector<Hash256>& input) const
    {
        Hash256 result{};

        FIPS202_SHAKE256_PURE((const unsigned char*)&input[0], sizeof(Seed256)*input.size(), (unsigned char*)&result, sizeof(result));

        return result;
    }

    Seed256 AwardRNG::GetSeed(const std::string& input) const
    {
        Seed256 result;

        for (size_t i = 0; i < std::min(result.size(), input.size()); i++)
        {
            result[i] = static_cast<Seed256::value_type>(input.at(i));
        }

        return result;
    }

    Seed256 AwardRNG::GetRandomSeed() const
    {
        Seed256 result{};

        std::random_device rd{};
        Sfmt gen{rd()};

        const std::string symbols = "!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        if (!symbols.empty())
        {
            UniformIntDistribution<size_t> dist(0, static_cast<size_t>(symbols.size() - 1));
            std::for_each(result.begin(), result.end(), [&dist, &gen, &symbols](Seed256::value_type& value)
            {
                value = symbols.at(dist(gen));
            });
        }

        return result;
    }

    bool AwardRNG::Seeded(const Seed256& seed) const
    {
        return !std::all_of(seed.begin(), seed.end(), [](Seed256::value_type value) { return value == 0; });
    }

    Result CALL AwardRNG::Clear()
    {
        m_game = Game();

        return Result::Success;
    }

    Result CALL AwardRNG::Begin(uint32_t game_id)
    {
        try
        {
            Clear();

            m_game.game_id = game_id;

            return Result::Success;
        }
        catch (const std::exception&)
        {
            return Result::Error;
        }
    }

    Result CALL AwardRNG::Seed(const char* name, uint32_t table_id, uint32_t seat_index, const Seed256& seed)
    {
        try
        {
            InfoSeed info;

            info.name = std::string(name ? name : "");
            info.table_id = table_id;
            info.seat_index = seat_index;
            info.seed = seed;

            m_game.received.push_back(std::move(info));

            return Result::Success;
        }
        catch (const std::exception&)
        {
            return Result::Error;
        }
    }

    uint32_t CALL AwardRNG::GetAwardNumber() const
    {
        try
        {
            auto range = GetRange();

            assert(range > 0);

            // create seed by copying from array
            std::vector<uint8_t> seed{};
            seed.reserve(m_game.combined.size());
            std::copy(m_game.combined.begin(), m_game.combined.end(), std::back_inserter(seed));
            // create random number generator
            Sfmt gen(seed);
            UniformIntDistribution<uint32_t> dist(0u, range - 1);
            return dist(gen);
        }
        catch (const std::exception&)
        {
            return 0;
        }
    }

    Result CALL AwardRNG::Hash()
    {
        try
        {
            if (m_game.received.empty())
            {
                return Result::Failure;
            }

            m_game.committed.clear();

            for (auto& i : m_game.received)
            {
                if (!Seeded(i.seed))
                {
                    i.origin = Origin::System;
                    i.seed = GetRandomSeed();
                }
            }

            SortInfo(m_game.received);

            for (auto& i : m_game.received)
            {
                InfoHash commit(i);

                commit.hash = GetHash(i.seed);

                m_game.committed.push_back(commit);
            }

            std::vector<Hash256> hashes;

            for (auto i : m_game.committed)
            {
                hashes.push_back(i.hash);
            }

            m_game.combined = GetHash(hashes);

            if (!Seeded(m_game.combined))
            {
                return Result::Failure;
            }

            return Result::Success;
        }
        catch (const std::exception&)
        {
            return Result::Error;
        }
    }

    uint32_t CALL AwardRNG::GetRange() const
    {
        return 1000000;
    }

    const char* CALL AwardRNG::GetOutput() const
    {
        try
        {
            std::stringstream result;

            if (m_game.game_id <= 0 || m_game.committed.empty())
            {
                m_output = result.str();

                return m_output.c_str();
            }

            result << GetSeparator() << std::endl;
            result << "Version: " << VERSION << std::endl;
            result << "Game Id: " << m_game.game_id << std::endl;
            result << GetSeparator() << std::endl;
            result << "Data: " << std::endl;

            for (size_t i = 0; i < m_game.committed.size(); i++)
            {
                result << GetSeparator() << std::endl;

                result << GetOutputSeed(m_game.received[i], "");
                result << GetOutputHash(m_game.committed[i], "");
            }

            result << GetSeparator() << std::endl;
            result << "Combined Hash: " << GetHex(m_game.combined) << std::endl;
            result << "Random Number: " << GetAwardNumber() << std::endl;

            m_output = result.str();

            return m_output.c_str();
        }
        catch (const std::exception&)
        {
            return nullptr;
        }
    }

    Result CALL AwardRNG::Destroy()
    {
        try
        {
            delete this;

            return Result::Success;
        }
        catch (const std::exception&)
        {
            return Result::Error;
        }
    }
}//RNG

#if defined WIN32
#define EXPORT
#else
#define EXPORT __attribute__((visibility("default")))
#endif

EXPORT DecentralizedRNGAward::IAwardRNG* CreateAwardRNG()
{
    try
    {
        return new DecentralizedRNGAward::AwardRNG();
    }
    catch (const std::exception&)
    {
        return nullptr;
    }
}

EXPORT void DestroyAwardRNG(DecentralizedRNGAward::IAwardRNG* rng)
{
    if (!rng)
    {
        return;
    }

    rng->Destroy();
}
