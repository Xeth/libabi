#include "Decoder.hpp"

namespace Ethereum{namespace ABI{


std::string Decoder::decodeAddress(const std::string &input) const
{
    return decodeAddress(input.data(), input.size());
}


std::string Decoder::decodeAddress(const char *data, size_t size) const
{
    if(data[1]=='x'||data[1]=='x')
    {
        size-=2;
        data+=2;
    }

    if(size<64)
    {
        return "0x0000000000000000000000000000000000000000";
    }

    size_t offset = size - 40;

    std::string address;
    address.resize(40);


    std::copy(data+offset, data+size, address.begin());


    return address;

}

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
        return uint256_t(0);
    }
    return uint256_t(input);
}


uint256_t Decoder::decodeUint(const char *input, size_t size) const
{
    if(size < 64)
    {
        return uint256_t(0);
    }
    //ToDo: optimize, construct without another string
    return uint256_t(std::string(input, size));
}


int256_t Decoder::decodeInt(const std::string &input) const
{
    if(input.size() < 64)
    {
        return int256_t(0);
    }
    return parseInt(int256_t(input));
}


int256_t Decoder::decodeInt(const char *input, size_t size) const
{
    if(size < 64)
    {
        return int256_t(0);
    }
    //ToDo: optimize, construct without another string
    return parseInt(int256_t(std::string(input, size)));
}


decimal_t Decoder::decodeDecimal(const std::string &input) const
{
    if(input.size() < 64)
    {
        throw decimal_t(0);
    }
    return parseDecimal(decimal_t(input));
}


decimal_t Decoder::decodeDecimal(const char *input, size_t size) const
{
    if(size < 64)
    {
        throw decimal_t(0);
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


bool Decoder::decodeBool(const std::string &input) const
{
    return decodeBool(input.data(), input.size());
}


bool Decoder::decodeBool(const char *input, size_t size) const
{
    uint256_t val = decodeUint(input, size);
    return val>0;
}


decimal_t Decoder::parseDecimal(const decimal_t &input) const
{
    decimal_t result = input / pow(decimal_t(2), 128);
    return result;
}



}}
