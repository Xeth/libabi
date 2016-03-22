namespace Ethereum{namespace ABI{


template<class Invoker>
Reflection<Invoker>::Reflection(const char *address, const Invoker &invoker) :
    _address(address),
    _invoker(invoker)
{}


template<class Invoker>
Reflection<Invoker>::Reflection(const std::string &address, const Invoker &invoker) :
    _address(address),
    _invoker(invoker)
{}



template<class Invoker>
std::string Reflection<Invoker>::call(const char *method, const Arguments &args)
{
    return _invoker(_address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::call(const std::string &method, const Arguments &args)
{
    return _invoker(_address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::call(const char *from, const char *method, const Arguments &args)
{
    return _invoker(from, _address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::call(const std::string &from, const std::string &method, const Arguments &args)
{
    return _invoker(from, _address, Method::Encode(method, args));
}


}}
