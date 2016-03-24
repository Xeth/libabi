#pragma once 


#include "Arguments.hpp"
#include "Method.hpp"
#include "Result.hpp"


namespace Ethereum{namespace ABI{


template<class Invoker>
class Contract
{
    public:
        Contract(const std::string &address, const Invoker &);
        Contract(const char *, const Invoker &);

        Result call(const char *);
        Result call(const char *, const Arguments &);
        std::string execute(const char *, const Arguments &);
        std::string execute(const char *);

        Invoker & getInvoker();
        const std::string & getAddress() const;

    private:
        std::string _address;
        Invoker _invoker;
};



}}

#include "Contract.ipp"



