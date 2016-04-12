#pragma once

#include <string>
#include "cryptopp/sha3.h"

#include "Arguments.hpp"


namespace Ethereum{namespace ABI{


class Method
{
    public:
        static std::string Encode(const std::string &method);
        static std::string Encode(const char *method);
        static std::string Encode(const char *method, size_t size);
        static std::string Encode(const char *method, const Arguments &args);
        static std::string Encode(const std::string &method, const Arguments &args);
        static std::string Encode(const char *method, size_t size, const Arguments &args);
};


}}
