#pragma once

#include <vector>
#include <string>
#include <boost/array.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#include "Serializer.hpp"

namespace Ethereum{namespace ABI{

class FixedArgumentTag{};
class AddressArgumentTag{};

}}


#define ABI_WRAP_MACRO(define, args) define args
#define ABI_CHECK(...) ABI_WRAP_MACRO(ABI_CHECK_N, (__VA_ARGS__, 0))
#define ABI_CHECK_N(x, n, ...) n

#define ABI_PROBE(x) x, 1,

#define ABI_IS_PAREN(x) ABI_CHECK(ABI_IS_PAREN_PROBE x)
#define ABI_IS_PAREN_PROBE(...) ABI_PROBE(~)


#define ABI_ESCAPE_ARG_PARAM(r, data, i, Name) BOOST_PP_COMMA_IF(i) Name

#define ABI_DYNAMIC(data, size) (data, size)
#define ABI_FIXED(...) (BOOST_PP_SEQ_FOR_EACH_I(ABI_ESCAPE_ARG_PARAM,,BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)), ::Ethereum::ABI::FixedArgumentTag())
#define ABI_ADDRESS(data) (data , ::Ethereum::ABI::AddressArgumentTag())

#define ABI_ESCAPE_ARG(x) ( x )
#define ABI_PARSE_ARGUMENTS_SEQ_ITEM(r, data, x) BOOST_PP_IF(ABI_IS_PAREN(x), x, ABI_ESCAPE_ARG(x))
#define ABI_ARGUMENTS_FROM_SEQ(SEQ) BOOST_PP_SEQ_FOR_EACH(ABI_PARSE_ARGUMENTS_SEQ_ITEM, ~, SEQ)

#define CONTRACT_ARGUMENTS(...) ::Ethereum::ABI::Arguments() ABI_ARGUMENTS_FROM_SEQ(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

namespace Ethereum{namespace ABI{


class Arguments
{
    public:

        Arguments();

        void add(bool);
        void add(const uint256_t &);
        void add(const int256_t &);
        void add(const decimal_t &);
        void add(const std::string &);
        void add(const char *);
        void add(const unsigned char *, size_t);

        template<class T>
        Arguments & operator()(const T &);

        Arguments & operator()(const unsigned char *, size_t);
        Arguments & operator()(const std::string &, const FixedArgumentTag &);
        Arguments & operator()(const char *, const FixedArgumentTag &);
        Arguments & operator()(const unsigned char *, size_t, const FixedArgumentTag &);
        Arguments & operator()(const std::string &, const AddressArgumentTag &);
        Arguments & operator()(const char *, size_t, const AddressArgumentTag &);

        template<size_t size>
        void add(const boost::array<unsigned char, size> &);

        template<class T, size_t size>
        void add(const boost::array<T, size> &);

        template<size_t size>
        void add(const boost::array<std::string, size> &);

        template<class T>
        void add(const std::vector<T> &);
        void add(const std::vector<std::string> &);

        void addFixed(const unsigned char *, size_t);
        void addAddress(const std::string &);
        void addAddress(const char *, size_t);

        std::string toHex() const;
        void reset();

    private:
        void addInt(const std::string &);
        void addUInt(const std::string &);
        void addDynamicVar(const std::string &);
        void addFixedVar(const std::string &);

    private:
        enum VariableType
        {
            Fixed_Type,
            Dynamic_Type
        };
        typedef std::vector<std::pair<std::string, VariableType> > Container;
    private:
        Serializer _serializer;
        Container _args;
        size_t _dynamicOffset;
};

#define DYNAMIC ABI_DYNAMIC
#define FIXED ABI_FIXED
#define ARGUMENTS CONTRACT_ARGUMENTS


}}



#include "Arguments.ipp"

