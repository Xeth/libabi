#pragma once 

#include "Arguments.hpp"


namespace Ethereum{namespace ABI{


class ContractConstructor
{
    public:
        static std::string Encode(const char *code);
        static std::string Encode(const char *code, const Arguments &args);
};


}}
