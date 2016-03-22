#include "Serializer.hpp"


namespace Ethereum{namespace ABI{


std::string Serializer::serialize(const Decimal &val)
{
    Decimal result = pow(Decimal(2), 128);
    result *= val;
    return serialize(uint256_t(result.str()));
}


std::string Serializer::serialize(const uint256_t &val)
{
    return serializeNumber(val);
}


std::string Serializer::serialize(const int256_t &val)
{
    return serializeNumber((val<0)?makeTwosComplement(val):val);
}


int256_t Serializer::makeTwosComplement(const int256_t &val)
{
    int256_t result("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    result+=val;
    result+=1;
    return result;
}


template<class Number>
std::string Serializer::serializeNumber(const Number &val)
{
    std::string result = val.str(64, std::ios_base::hex);
    size_t padding = 64 - result.size();

    if(padding)
    {
        result.insert(0, padding, '0');
    }

    return result;
}


std::string Serializer::serialize(bool val)
{
    std::string result = "000000000000000000000000000000000000000000000000000000000000000";
    result += (val?"1":"0");
    return result;
}


std::string Serializer::serialize(const std::string &val)
{
    return serializeDynamicBytes(val.begin(), val.end(), val.size());
}


template<class Iterator>
std::string Serializer::serializeDynamicBytes(Iterator begin, Iterator end, size_t size)
{
    std::string prefix = serialize(uint256_t(size));
    return serializeBytes(begin, end, size, prefix.data(), prefix.size());
}


template<class Iterator>
std::string Serializer::serializeBytes(Iterator begin, Iterator end, size_t size, const char *prefix, size_t prefixSize)
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



std::string Serializer::serialize(const char *val)
{
    size_t size = strlen(val);
    return serializeDynamicBytes(val, val+size, size);
}


std::string Serializer::serialize(const unsigned char *buffer, size_t size)
{
    return serializeDynamicBytes(buffer, buffer+size, size);
}


std::string Serializer::serializeFixedData(const unsigned char *buffer, size_t size)
{
    return serializeBytes(buffer, buffer+size, size, NULL, 0);
}



}}
