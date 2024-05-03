#ifndef INS_ENCODING_32I
#define INS_ENCODING_32I

#include <string>

#include "RISCV32I_ISA.h"

namespace Encode_32I {

    /*
    These encoding functions assume that the operand inputs are all in binary already!!!

    They take in the expected operands and will return a string of binary encoded instructions of 32 characters 
    OR an empty string is something goes wrong.
    ex.) an opname that is R-type is given to the I-type encoder.
         an operand given is too many digits long.

    All they do is properly format the given info.
    */

    std::string RType(std::string opname, std::string rd, std::string rs1, std::string rs2);
    std::string IType(std::string opname, std::string rd, std::string rs1, std::string imm);
    std::string SType(std::string opname, std::string rs1, std::string rs2, std::string imm);
    std::string BType(std::string opname, std::string rs1, std::string rs2, std::string imm);
    std::string UType(std::string opname, std::string rd, std::string imm);
    std::string JType(std::string opname, std::string rd, std::string imm);
} 


#endif