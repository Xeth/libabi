#include <iostream>

#include "abi/Contract.hpp"


using namespace Ethereum::ABI;


class DummyInvoker
{
    public:
        std::string execute(const std::string &address, const std::string &code);
        std::string call(const std::string &address, const std::string &code);
};


int main()
{
    Contract<DummyInvoker> contract("0x000000000000000000", DummyInvoker());
    std::cout<<"result : "<<contract.execute("foo", ARGUMENTS(uint256_t(1), int256_t(-1), FIXED((const unsigned char *)"hello world", 11), std::string("hello world"), ((const unsigned char *)"hello world", 11)));
    std::cout<<std::endl;
    return 0;
}


std::string DummyInvoker::execute(const std::string &address, const std::string &code)
{
    std::cout<<"called ["<<address<<"] : "<<code<<std::endl<<std::flush;
    return "foobar";
}


std::string DummyInvoker::call(const std::string &address, const std::string &code)
{
    std::cout<<"called ["<<address<<"] : "<<code<<std::endl<<std::flush;
    return "0x0000000000000000000000000000000000000000000000000000000000000001";
}


