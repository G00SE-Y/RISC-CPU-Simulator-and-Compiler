#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "RISCV32I_ISA.h"


namespace Tokenizer {

    /*
    

    OP:     

    REG:    

    IMM:    

    SUBR:   

    DATA:   

    ADDR:   
    */
    enum token_type {
        NO_TOK = 0, // Unidentified token and will result in a compiler error during parsing
        OP = 1, // An operation token that matches a predefined operation in the related *_ISA.h's enum
        REG = 2, // A Register name that begins with `$` and is followed by some alphanumeric symbols
        IMM = 3, // A numeric value in base 10 (default immediate)
        SUBR = 4, // A tag indicating the start of a subroutine
        DATA = 5, // A Tag indicating the following values are constant data
        ADDR = 6, // An operand that provides a memory address with possible offset value
        COM = 7, // A comment that is disregarded during parsing
    };


    // Structure that describes a symbol in terms of what token definition it matches
    typedef struct Token {
        token_type type =  NO_TOK;
        BaseInt32_Instruction operation = NO_OP;
        std::string value = ""; // register identifier or numeric immediate
        std::string offset = "";
    }token;


    // returns a vector of identified tokens in the same line order as the given argument vector
    std::vector<std::vector<token>> tokenize(std::vector<std::string> code);
}

#endif