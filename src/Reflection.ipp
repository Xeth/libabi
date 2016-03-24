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
Result Reflection<Invoker>::call(const char *method, const Arguments &args)
{
    return Result(_invoker.call(_address, Method::Encode(method, args)));
}


template<class Invoker>
Result Reflection<Invoker>::call(const std::string &method, const Arguments &args)
{
    return Result(_invoker.call(_address, Method::Encode(method, args)));
}


template<class Invoker>
Result Reflection<Invoker>::call(const char *from, const char *method, const Arguments &args)
{
    return Result(_invoker.call(from, _address, Method::Encode(method, args)));
}


template<class Invoker>
Result Reflection<Invoker>::call(const std::string &from, const std::string &method, const Arguments &args)
{
    return Result(_invoker.call(from, _address, Method::Encode(method, args)));
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const char *method, const Arguments &args)
{
    return _invoker.execute(_address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const std::string &method, const Arguments &args)
{
    return _invoker.execute(_address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const char *from, const char *method, const Arguments &args)
{
    return _invoker.execute(from, _address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const std::string &from, const std::string &method, const Arguments &args)
{
    return _invoker.execute(from, _address, Method::Encode(method, args));
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const char *method, const Arguments &args, const uint256_t &gas)
{
    return _invoker.execute(_address, Method::Encode(method, args), gas);
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const std::string &method, const Arguments &args, const uint256_t &gas)
{
    return _invoker.execute(_address, Method::Encode(method, args), gas);
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const char *from, const char *method, const Arguments &args, const uint256_t &gas)
{
    return _invoker.execute(from, _address, Method::Encode(method, args), gas);
}


template<class Invoker>
std::string Reflection<Invoker>::execute(const std::string &from, const std::string &method, const Arguments &args, const uint256_t &gas)
{
    return _invoker.execute(from, _address, Method::Encode(method, args), gas);
}


template<class Invoker>
Invoker & Reflection<Invoker>::getInvoker()
{
    return _invoker;
}

template<class Invoker>
const std::string & Reflection<Invoker>::getAddress()
{
    return _address;
}

}}
