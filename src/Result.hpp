#pragma

#include <string>

#include "Decoder.hpp"


namespace Ethereum{namespace ABI{

/* supports only single return variable */
/* supports only string, uint, int, decimal primitives, no array's yet */


class Result
{
    public:
        Result(const std::string &data);

        std::string toString() const;
        uint256_t toUint() const;
        int256_t toInt() const;
        decimal_t toDecimal() const;

    private:
        std::string _value;
        Decoder _decoder;
};


}}
