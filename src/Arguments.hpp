#pragma once

#include <vector>
#include <string>
#include <boost/array.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

#include "Serializer.hpp"


namespace Ethereum{namespace ABI{

class FixedArgumentTag{};


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
        Arguments & operator()(const unsigned char *, size_t, const FixedArgumentTag &);

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

#define DYNAMIC(data, size) (data, size)
#define FIXED(data, size) (data, size, FixedArgumentTag())

#define ESCAPE_ARG(x) ( x )
#define PARSE_ARGUMENTS_SEQ_ITEM(r, data, x) BOOST_PP_IF(BOOST_PP_IS_BEGIN_PARENS(x), x, ESCAPE_ARG(x))
#define ARGUMENTS_FROM_SEQ(SEQ) BOOST_PP_SEQ_FOR_EACH(PARSE_ARGUMENTS_SEQ_ITEM, ~, SEQ)

#define ARGUMENTS(...) Arguments() ARGUMENTS_FROM_SEQ(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))




}}

#define CONTRACT_ARGUMENTS Ethereum::ABI::ARGUMENTS

#include "Arguments.ipp"

