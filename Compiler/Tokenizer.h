#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "RISCV32I_ISA.h"

/*
NO_TOK: Unidentified token and will result in a compiler error during parsing

OP:     An operation token that matches a predefined operation in the related *_ISA.h's enum

REG:    A Register name that begins with `$` and is followed by some alphanumeric symbols

IMM:    A numeric value in base 10 (default immediate)
*/

enum token_type {NO_TOK = 0, OP = 1, REG = 2, IMM = 3};

typedef struct Token {
    token_type type =  NO_TOK;
    BaseInt32_Instruction operation = NO_OP;
    std::string value; // register identifier or numeric immediate
}token;

class Tokenizer {

    public:
        std::vector<std::vector<token>> tokenize(const std::vector<std::string>& code);

    private:
        static std::vector<token> tokenize_line(const std::string& line);
        static token identify_token(const std::string& s);

        static BaseInt32_Instruction is_op(const std::string& s);
        static std::string is_reg(std::string s);
        static std::string is_imm(std::string s);
};


/*
matches any string that consists of a `$`, then has a lowercase letter and a digit in that order
e.g.) "$a0", "$z9"
*/
const std::regex re_register("^\\$[a-z][0-9]$");


/*
matches with a `-` or nothing followed by any sequence of 1 or more digits
*/ 
const std::regex re_imm10("^-?[0-9]+$");

#endif
