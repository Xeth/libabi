#pragma once 


#include "Arguments.hpp"
#include "Method.hpp"
#include "Result.hpp"


namespace Ethereum{namespace ABI{


template<class Invoker>
class Reflection
{
    public:
        Reflection(const std::string &address, const Invoker &);
        Reflection(const char *, const Invoker &);

        Result call(const char *, const Arguments &);
        Result call(const std::string &, const Arguments &);

        Result call(const char *from, const char *name, const Arguments &);
        Result call(const std::string &from, const std::string &name, const Arguments &);

        std::string execute(const char *, const Arguments &);
        std::string execute(const std::string &, const Arguments &);
        std::string execute(const char *from, const char *name, const Arguments &);
        std::string execute(const std::string &from, const std::string &name, const Arguments &);

        std::string execute(const char *, const Arguments &, const uint256_t &gas);
        std::string execute(const std::string &, const Arguments &, const uint256_t &gas);
        std::string execute(const char *from, const char *name, const Arguments &, const uint256_t &gas);
        std::string execute(const std::string &from, const std::string &name, const Arguments &, const uint256_t &gas);

        Invoker & getInvoker();
        const std::string & getAddress() const;

    private:
        std::string _address;
        Invoker _invoker;
};



}}

#include "Reflection.ipp"



