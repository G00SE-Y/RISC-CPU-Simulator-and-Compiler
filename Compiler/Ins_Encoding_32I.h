#ifndef INS_ENCODING_32I
#define INS_ENCODING_32I

#include <string>

#include "RISCV32I_ISA.h"

namespace Encode_32I {

    /*
    These encoding functions assume that the operand inputs are all in binary already!!!

    They take in the expected operation and operands (as a vector of strings) and will return a string of binary encoded instructions of 32 characters 
    OR an empty string is something goes wrong.
    ex.) an opname that is R-type is given to the I-type encoder.
         an operand given is too many digits long.

    All they do is properly format the given info.
    */

    std::string RType(std::vector<std::string> op);
    std::string IType(std::vector<std::string> op);
    std::string SType(std::vector<std::string> op);
    std::string BType(std::vector<std::string> op);
    std::string UType(std::vector<std::string> op);
    std::string JType(std::vector<std::string> op);
} 


#endif