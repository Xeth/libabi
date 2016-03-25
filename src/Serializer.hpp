#pragma once

#include <string>
#include <boost/algorithm/hex.hpp>

#include "types.hpp"


namespace Ethereum{namespace ABI{


class Serializer
{
    public:
        std::string serialize(bool) const;
        std::string serialize(const uint256_t &) const;
        std::string serialize(const int256_t &) const;
        std::string serialize(const decimal_t &) const;
        std::string serialize(const std::string &) const;
        std::string serialize(const char *) const;
        std::string serialize(const unsigned char *, size_t) const;
        std::string serializeFixedData(const unsigned char *, size_t ) const;
        std::string serializeAddress(const char *, size_t ) const;

    private:
        template<class Number>
        std::string serializeNumber(const Number &) const;

        int256_t makeTwosComplement(const int256_t &) const;

        template<class Iterator>
        std::string serializeDynamicBytes(Iterator begin, Iterator end, size_t size) const;

        template<class Iterator>
        std::string serializeBytes(Iterator begin, Iterator end, size_t size, const char *prefix, size_t prefixSize) const;

};


}}
