#include "Method.hpp"


namespace Ethereum{namespace ABI{


std::string Method::Encode(const char *name)
{
    return Encode(name, strlen(name));
}


std::string Method::Encode(const char *name, size_t size)
{
    CryptoPP::SHA3_256 hash;
    byte digest[32];
    std::string result;
    result.resize(8);
    hash.CalculateDigest( digest, (const byte*) name, size);
    boost::algorithm::hex(digest, digest+4, result.begin());
    return result;
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
