#pragma once 


#include "Arguments.hpp"
#include "Method.hpp"


namespace Ethereum{namespace ABI{


template<class Invoker>
class Reflection
{
    public:
        Reflection(const std::string &address, const Invoker &);
        Reflection(const char *, const Invoker &);

        std::string call(const char *, const Arguments &);
        std::string call(const std::string &, const Arguments &);


    private:
        std::string _address;
        Invoker _invoker;
};



}}

#include "Reflection.ipp"



