#include "Serializer.hpp"


namespace Ethereum{namespace ABI{

std::string Serializer::serializeAddress(const char *address, size_t size) const
{
    if(!size||size<2)
    {
        return "0000000000000000000000000000000000000000000000000000000000000000";
    }

    if(address[1]=='x'||address[1]=='X')
    {
        size-=2;
        address+=2;
    }

    std::string result;
    result.reserve(64);
    result = "000000000000000000000000";
    result.append(address, size);
    return result;
}


std::string Serializer::serialize(const decimal_t &val) const
{
    decimal_t result = pow(decimal_t(2), 128);
    result *= val;
    return serialize(uint256_t(result.str()));
}


std::string Serializer::serialize(const uint256_t &val) const
{
    return serializeNumber(val);
}


std::string Serializer::serialize(const int256_t &val) const
{
    return serializeNumber((val<0)?makeTwosComplement(val):val);
}


int256_t Serializer::makeTwosComplement(const int256_t &val) const
{
    int256_t result("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    result+=val;
    result+=1;
    return result;
}


template<class Number>
std::string Serializer::serializeNumber(const Number &val) const
{
    std::string result = val.str(64, std::ios_base::hex);
    size_t padding = 64 - result.size();

    if(padding)
    {
        result.insert(0, padding, '0');
    }

    return result;
}


std::string Serializer::serialize(bool val) const
{
    std::string result = "000000000000000000000000000000000000000000000000000000000000000";
    result += (val?"1":"0");
    return result;
}


std::string Serializer::serialize(const std::string &val) const
{
    return serializeDynamicBytes(val.begin(), val.end(), val.size());
}


template<class Iterator>
std::string Serializer::serializeDynamicBytes(Iterator begin, Iterator end, size_t size) const
{
    std::string prefix = serialize(uint256_t(size));
    return serializeBytes(begin, end, size, prefix.data(), prefix.size());
}


template<class Iterator>
std::string Serializer::serializeBytes(Iterator begin, Iterator end, size_t size, const char *prefix, size_t prefixSize) const
{
    size_t strSize = size*2 + prefixSize;
    size_t resultSize = ceil(double(strSize)/64)*64;
    size_t padding = resultSize - strSize;

    std::string result;
    result.reserve(resultSize);
    if(prefixSize)
    {
        result.append(prefix, prefixSize);
    }

    result.resize(strSize);
    boost::algorithm::hex(begin, end, result.begin()+prefixSize);

    if(padding)
    {
        result.append(padding, '0');
    }

    return result;
}



std::string Serializer::serialize(const char *val) const
{
    size_t size = strlen(val);
    return serializeDynamicBytes(val, val+size, size);
}


std::string Serializer::serialize(const unsigned char *buffer, size_t size) const
{
    return serializeDynamicBytes(buffer, buffer+size, size);
}


std::string Serializer::serializeFixedData(const unsigned char *buffer, size_t size) const
{
    return serializeBytes(buffer, buffer+size, size, NULL, 0);
}



}}
