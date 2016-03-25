#pragma once 

#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/algorithm/hex.hpp>

#include "types.hpp"

namespace Ethereum{namespace ABI{


class Decoder
{
    public:

        std::string decodeString(const std::string &) const;
        std::string decodeString(const char *, size_t) const;

        uint256_t decodeUint(const std::string &) const;
        uint256_t decodeUint(const char *, size_t ) const;

        int256_t decodeInt(const std::string &) const;
        int256_t decodeInt(const char *, size_t) const;

        decimal_t decodeDecimal(const std::string &) const;
        decimal_t decodeDecimal(const char *, size_t) const;

        bool decodeBool(const std::string &) const;
        bool decodeBool(const char *, size_t) const;

        std::string decodeAddress(const std::string &) const;
        std::string decodeAddress(const char *, size_t ) const;

    private:
        void assertWordSize(size_t ) const;
        int256_t parseInt(const int256_t &) const;
        decimal_t parseDecimal(const decimal_t &) const;

};


}}
