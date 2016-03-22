#include "Result.hpp"


namespace Ethereum{namespace ABI{


Result::Result(const std::string &data) : 
    _value((data[1]=='x'||data[1]=='X') ? data.substr(2) : data)
{}


std::string Result::toString() const
{
    return _decoder.decodeString(_value);
}


uint256_t Result::toUint() const
{
    return _decoder.decodeUint(_value);
}


int256_t Result::toInt() const
{
    return _decoder.decodeInt(_value);
}


decimal_t Result::toDecimal() const
{
    return _decoder.decodeDecimal(_value);
}


}}
