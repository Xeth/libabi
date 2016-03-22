#pragma once 

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/algorithm/hex.hpp>


namespace Ethereum{namespace ABI{


typedef boost::multiprecision::cpp_dec_float_100 decimal_t;
typedef boost::multiprecision::uint256_t uint256_t;
typedef boost::multiprecision::int256_t int256_t;


}}
