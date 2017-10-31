#include "Method.hpp"


namespace Ethereum{namespace ABI{


std::string Method::Encode(const char *name)
{
    return Encode(name, strlen(name));
}

std::string Method::Encode(const std::string &name)
{
    return Encode(name.data(), name.size());
}

std::string Method::Encode(const char *name, size_t size)
{
    CryptoPP::SHA3_256 hash;
    unsigned char digest[32];
    std::string result;
    result.reserve(10);
    result.resize(8);
    hash.CalculateDigest( digest, (const unsigned char*) name, size);
    boost::algorithm::hex(digest, digest+4, result.begin());
    result.insert(0, "0x");
    return result;
}

std::string Method::Encode(const std::string &name, const Arguments &args)
{
    return Encode(name.data(), name.size(), args);
}


std::string Method::Encode(const char *name, const Arguments &args)
{
    return Encode(name, strlen(name), args);
}


std::string Method::Encode(const char *name, size_t size, const Arguments &args)
{
    return Encode(name, size) + args.toHex();
}


}}
