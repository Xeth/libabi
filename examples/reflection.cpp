#include <iostream>

#include "abi/Reflection.hpp"


using namespace Ethereum::ABI;


class DummyInvoker
{
    public:
        std::string operator()(const std::string &address, const std::string &code);
};


int main()
{
    Reflection<DummyInvoker> contract("0x000000000000000000", DummyInvoker());
    std::cout<<"result : "<<contract.call("foo", ARGUMENTS(uint256_t(1), int256_t(-1), FIXED((const unsigned char *)"hello world", 11), std::string("hello world"), ((const unsigned char *)"hello world", 11)));
    return 0;
}


std::string DummyInvoker::operator()(const std::string &address, const std::string &code)
{
    std::cout<<"called ["<<address<<"] : "<<code<<std::endl<<std::flush;
    return "foobar";
}
