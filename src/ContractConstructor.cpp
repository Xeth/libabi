#include "ContractConstructor.hpp"


namespace Ethereum{namespace ABI{


std::string ContractConstructor::Encode(const char *code)
{
    return code;
}

std::string ContractConstructor::Encode(const char *code, const Arguments &args)
{
    std::string result = code;
    result += args.toHex();
    return result;
}

const std::string & ContractConstructor::Encode(const std::string &code)
{
    return code;
}

std::string ContractConstructor::Encode(const std::string &code, const Arguments &args)
{
    std::string result = code;
    result += args.toHex();
    return result;
}

}}
