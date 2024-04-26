#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <iterator>

#include "Tokenizer.h"
#include "RISCV32I_ISA.h"

/*

*/
std::vector<token> Tokenizer::tokenize_line(const std::string& line) {

    std::vector<token> tokens;
    std::vector<std::string> symbols;

    // split line by whitespace and copy into symbols
    std::istringstream iss(line);
    std::copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter(symbols)
    );

    for(auto symbol: symbols) {
        tokens.push_back(identify_token(symbol));
    }

    return tokens;
}


/*
Takes a vector of strings in ASM and converts it into a vector of identified tokens
*/
std::vector<std::vector<token>> Tokenizer::tokenize(const std::vector<std::string>& code) {

    std::vector<std::vector<token>> tokens;

    for(auto line: code) {

        tokens.push_back(tokenize_line(line));
    }

    // TODO: missing return value
}



token Tokenizer::identify_token(const std::string& s) {

    token t;
    
    if( (t.operation = is_op(s) ) != BaseInt32_Instruction::NO_OP) { // if operation
        t.type = token_type::OP;
    }
    else if( !(t.value = is_reg(s)).empty() ) { // if register
        t.type = token_type::REG;
    }
    else if( !(t.value = is_imm(s)).empty() ) { // if immediate
        t.type = token_type::IMM;
    }

    return t;
}


BaseInt32_Instruction Tokenizer::is_op(const std::string& s) {

    try {
        return str_ins_BI32.at(s); // throws OOR exception if `s` isn't in the map
    }
    catch (std::out_of_range& e) {
        return BaseInt32_Instruction::NO_OP;
    }
}


std::string Tokenizer::is_reg(std::string s) {

    if(s[0] == '$' && s.length() >= 3) {

        std::string suffix = s.substr(1);
        if(std::regex_match(suffix, re_register)) {
            return suffix;
        }
    }

    return "";
}


std::string Tokenizer::is_imm(std::string s) {

    if(std::regex_match(s, re_imm10)) return s;
    else return "";
}
