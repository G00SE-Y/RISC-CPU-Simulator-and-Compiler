#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include "RISCV32I_ISA.h"


namespace Tokenizer {

    enum token_type {
        // Default
        NO_TOKEN,           // Unidentified token and will result in a compiler error during parsing

        // Comment (subsequent tokens ignored)
        COMMENT,            // A comment that is disregarded during parsing
        
        // Alias token (memory address)
        ALIAS,              // A tag indicating the start of a subroutine or a data member
        
        // Code segment tokens
        TEXT,               // A Tag indicating the following values are instructions
        OPERATOR,           // An operation token that matches a predefined operation in the related *_ISA.h's enum
        REGISTER,           // A Register name that begins with `$` and is followed by some alphanumeric symbols
        IMMEDIATE,          // A numeric value in base 10 (default immediate)
        ADDRESS,            // An operand that provides a memory address with possible offset value
        
        // Data segment tokens
        DATA,               // A Tag indicating the following values are data members
        WORD,               // Indicates that this data should be 4-byte aligned
        HALF,               // indicates that this data should be 2-byte aligned
        ASCII,              // Used in the data section to specify that the following is a string of congitguous ascii chars
        ASCIIZ,             // Used in the data section to specify that the following string should be interpreted the same as with `.ascii`, but ending with a null terminator (0x0)
        RESERVE,            // Used to reserve bytes in stack
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
        Token(Tokenizer::token_type t, std::string v) {
            type = t;
            operation = BaseInt32_Instruction::NO_OP;
            value = v;
        }
        Token() {}
    };

    // returns a vector of identified tokens in the same line order as the given argument vector
    std::vector<std::vector<Tokenizer::Token>> tokenize(std::vector<std::string> code);
}

#endif