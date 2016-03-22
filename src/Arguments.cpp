#include "Arguments.hpp"


namespace Ethereum{namespace ABI{


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
    _fixed += _serializer.serialize(val);
}

void Arguments::add(const uint256_t &val)
{
    _fixed += _serializer.serialize(val);
}

void Arguments::add(const int256_t &val)
{
    _fixed += _serializer.serialize(val);
}


void Arguments::add(const Decimal &val)
{
    _fixed += _serializer.serialize(val);
}


void Arguments::add(const std::string &val)
{
    _dynamic += _serializer.serialize(val);
}


void Arguments::add(const char *val)
{
    _dynamic += _serializer.serialize(val);
}


void Arguments::add(const unsigned char *val, size_t size)
{
    _dynamic += _serializer.serialize(val, size);
}


void Arguments::addFixed(const unsigned char *val, size_t size)
{
    _fixed += _serializer.serializeFixedData(val, size);
}


void Arguments::add(const std::vector<std::string> &)
{
    throw std::runtime_error("string vecctor is not implemented");
}

std::string Arguments::toHex() const
{
    return _fixed + _dynamic;
}


void Arguments::reset()
{
    _fixed = _dynamic = "";
}

}}
