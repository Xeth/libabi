namespace Ethereum{namespace ABI{


template<class Invoker>
Contract<Invoker>::Contract(const char *address, const Invoker &invoker) :
    _address(address),
    _invoker(invoker)
{}


template<class Invoker>
Contract<Invoker>::Contract(const std::string &address, const Invoker &invoker) :
    _address(address),
    _invoker(invoker)
{}



template<class Invoker>
Result Contract<Invoker>::call(const char *method, const Arguments &args)
{
    return Result(_invoker.call(_address, Method::Encode(method, args)));
}


template<class Invoker>
std::string Contract<Invoker>::execute(const char *method, const Arguments &args)
{
    return _invoker.execute(_address, Method::Encode(method, args));
}


template<class Invoker>
Result Contract<Invoker>::call(const char *method)
{
    return Result(_invoker.call(_address, Method::Encode(method)));
}


template<class Invoker>
std::string Contract<Invoker>::execute(const char *method)
{
    return _invoker.execute(_address, Method::Encode(method));
}


template<class Invoker>
Invoker & Contract<Invoker>::getInvoker()
{
    return _invoker;
}

template<class Invoker>
const std::string & Contract<Invoker>::getAddress() const
{
    return _address;
}

}}
