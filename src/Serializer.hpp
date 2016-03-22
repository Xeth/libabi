#pragma once

#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/algorithm/hex.hpp>


namespace Ethereum{namespace ABI{

using namespace boost::multiprecision;
typedef boost::multiprecision::cpp_dec_float_100 Decimal;


class Serializer
{
    public:
        std::string serialize(bool);
        std::string serialize(const uint256_t &);
        std::string serialize(const int256_t &);
        std::string serialize(const Decimal &);
        std::string serialize(const std::string &);
        std::string serialize(const char *);
        std::string serialize(const unsigned char *, size_t);
        std::string serializeFixedData(const unsigned char *, size_t );

    private:
        template<class Number>
        std::string serializeNumber(const Number &);

        int256_t makeTwosComplement(const int256_t &);

        template<class Iterator>
        std::string serializeDynamicBytes(Iterator begin, Iterator end, size_t size);

        template<class Iterator>
        std::string serializeBytes(Iterator begin, Iterator end, size_t size, const char *prefix, size_t prefixSize);

};


}}
