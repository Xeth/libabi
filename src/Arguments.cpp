#include "Arguments.hpp"


namespace Ethereum{namespace ABI{

Arguments::Arguments() : 
    _dynamicOffset(0)
{}


Arguments & Arguments::operator()(const unsigned char *data, size_t size) 
{
    add(data, size);
    return *this;
}

Arguments & Arguments::operator()(const unsigned char *data, size_t size, const FixedArgumentTag &)
{
    addFixed(data, size);
    return *this;
}


void Arguments::add(bool val)
{
    addFixedVar(_serializer.serialize(val));
}

void Arguments::add(const uint256_t &val)
{
    addFixedVar(_serializer.serialize(val));
}

void Arguments::add(const int256_t &val)
{
    addFixedVar(_serializer.serialize(val));
}


void Arguments::add(const decimal_t &val)
{
    addFixedVar(_serializer.serialize(val));
}


void Arguments::add(const std::string &val)
{
    addDynamicVar(_serializer.serialize(val));
}


void Arguments::add(const char *val)
{
    addDynamicVar(_serializer.serialize(val));
}


void Arguments::add(const unsigned char *val, size_t size)
{
    addDynamicVar(_serializer.serialize(val, size));
}


void Arguments::addFixed(const unsigned char *val, size_t size)
{
    addFixedVar(_serializer.serializeFixedData(val, size));
}


void Arguments::add(const std::vector<std::string> &)
{
    throw std::runtime_error("string vecctor is not implemented");
}

std::string Arguments::toHex() const
{
    uint256_t offset = _dynamicOffset;
    std::string fixed;
    std::string dynamic;
    for(Container::const_iterator it=_args.begin(), end=_args.end(); it!=end; ++it)
    {
        if(it->second==Dynamic_Type)
        {
            fixed += _serializer.serialize(offset);
            dynamic += it->first;
            offset += it->first.size()/2;
        }
        else
        {
            fixed += it->first;
        }
    }

    return fixed + dynamic;
}


void Arguments::addFixedVar(const std::string &val)
{
    _args.push_back(std::make_pair(val, Fixed_Type));
    _dynamicOffset += (val.size()/2);
}


void Arguments::addDynamicVar(const std::string &val)
{
    _args.push_back(std::make_pair(val, Dynamic_Type));
    _dynamicOffset += 32; //ptr size
}


void Arguments::reset()
{
    _args.clear();
    _dynamicOffset = 0;
}

}}
