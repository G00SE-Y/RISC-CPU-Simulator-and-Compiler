#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "RISCV32I_ISA.h"


namespace Tokenizer {

    /*
    NO_TOK: Unidentified token and will result in a compiler error during parsing

    OP:     An operation token that matches a predefined operation in the related *_ISA.h's enum

    REG:    A Register name that begins with `$` and is followed by some alphanumeric symbols

    IMM:    A numeric value in base 10 (default immediate)
    */
    enum token_type {NO_TOK = 0, OP = 1, REG = 2, IMM = 3};


    // Structure that describes a symbol in terms of what token definition it matches
    typedef struct Token {
        token_type type =  NO_TOK;
        BaseInt32_Instruction operation = NO_OP;
        std::string value = ""; // register identifier or numeric immediate
    }token;


    // returns a vector of identified tokens in the same line order as the given argument vector
    std::vector<std::vector<token>> tokenize(std::vector<std::string> code);
}

#endif