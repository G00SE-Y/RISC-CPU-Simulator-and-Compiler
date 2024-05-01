#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "RISCV32I_ISA.h"


namespace Tokenizer {

    enum token_type {
        NO_TOKEN = 0, // Unidentified token and will result in a compiler error during parsing
        OPERATOR = 1, // An operation token that matches a predefined operation in the related *_ISA.h's enum
        REGISTER = 2, // A Register name that begins with `$` and is followed by some alphanumeric symbols
        IMMEDIATE = 3, // A numeric value in base 10 (default immediate)
        LABEL = 4, // A tag indicating the start of a subroutine
        DATA = 5, // A Tag indicating the following values are constant data
        ADDRESS = 6, // An operand that provides a memory address with possible offset value
        COMMENT = 7, // A comment that is disregarded during parsing
    };


    // Structure that describes a symbol in terms of what token definition it matches
    typedef struct Token {
        Tokenizer::token_type type =  NO_TOKEN;
        BaseInt32_Instruction operation = NO_OP;
        std::string value = ""; // register identifier or numeric immediate
        std::string offset = "";

        // this is only for slightly more convenient addition of definitions to the map
        Token(Tokenizer::token_type t, BaseInt32_Instruction op) {
            type = t;
            operation = op;
        }
        Token() {} // TODO figure out why this needs to be here
    }token;


    // returns a vector of identified tokens in the same line order as the given argument vector
    std::vector<std::vector<token>> tokenize(std::vector<std::string> code);
}

#endif