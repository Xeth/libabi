#include "Decoder.hpp"

namespace Ethereum{namespace ABI{


std::string Decoder::decodeString(const std::string &input) const
{
    return decodeString(input.data(), input.size());
}


std::string Decoder::decodeString(const char *input, size_t size) const
{
    if(size < 64)
    {
        throw std::runtime_error("invalid string data");
    }

    uint256_t strSize = decodeUint(input, 64);

    if((size - 64) < strSize)
    {
        throw std::runtime_error("buffer overlflow");
    }

    input+=64;

    std::string result;
    size_t offset = strSize.template convert_to<size_t>();
    result.resize(offset);
    offset*=2;

    boost::algorithm::unhex(input, input+offset, result.begin());
    return result;
}


uint256_t Decoder::decodeUint(const std::string &input) const
{
    if(input.size() < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    return uint256_t(input);
}


uint256_t Decoder::decodeUint(const char *input, size_t size) const
{
    if(size < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    //ToDo: optimize, construct without another string
    return uint256_t(std::string(input, size));
}


int256_t Decoder::decodeInt(const std::string &input) const
{
    if(input.size() < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    return parseInt(int256_t(input));
}


int256_t Decoder::decodeInt(const char *input, size_t size) const
{
    if(size < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    //ToDo: optimize, construct without another string
    return parseInt(int256_t(std::string(input, size)));
}


decimal_t Decoder::decodeDecimal(const std::string &input) const
{
    if(input.size() < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    return parseDecimal(decimal_t(input));
}


decimal_t Decoder::decodeDecimal(const char *input, size_t size) const
{
    if(size < 64)
    {
        throw std::runtime_error("invalid string data");
    }
    //ToDo: optimize, construct without another string
    return parseDecimal(decimal_t(std::string(input, size)));
}


int256_t Decoder::parseInt(const int256_t &input) const
{
    /*ToDo: optimize check first bit instead */
    if(input > int256_t("0xEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"))
    {
        int256_t result = int256_t("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") - input;
        --result;
        return result;
    }
    return input;
}


decimal_t Decoder::parseDecimal(const decimal_t &input) const
{
    decimal_t result = input / pow(decimal_t(2), 128);
    return result;
}



}}
