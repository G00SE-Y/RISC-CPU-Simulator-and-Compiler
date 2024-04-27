#include <iostream>
#include <string>
#include <regex>
#include <sstream>

#include "Tokenizer.h"
#include "RISCV32I_ISA.h"


namespace Tokenizer {


    /*

    */
    std::vector<Tokenizer::token> tokenize_line(std::string line) {

        std::vector<Tokenizer::token> tokens;
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

    // Anonymous Namespace
    namespace {


        // Private Function Definitions
        std::vector<token> tokenize_line(std::string line); // Takes a single vector of string symbols and identifies them as tokens
        token identify_token(std::string s); // Identifies a string as a token
        BaseInt32_Instruction Tokenizer::is_op(std::string s); // Determines which operation a string is
        std::string Tokenizer::is_reg(std::string s); // Determines if a string is a register name
        std::string Tokenizer::is_imm(std::string s); // determines if the string is an immediate 
        void prettyPrintTokens(std::vector<std::vector<token>> tokens); // Debug: prints all token data





        void prettyPrintTokens(std::vector<std::vector<Tokenizer::token>> tokens) {
    
            int i = 1;
            for(auto line: tokens) {
                std::cout << "Line " << i++ << std::endl;
                for(auto tok: line) {

                    std::cout << "Operation: " << tok.operation << "\t\tType of token: " << tok.type << "\t\tValue: " << tok.value << std::endl;
                }
                std::cout << std::endl;
            }
        }



        /*
        Takes a vector of strings in ASM and converts it into a vector of identified tokens
        */
        std::vector<std::vector<Tokenizer::token>> tokenize(std::vector<std::string> code) {

            std::vector<std::vector<token>> tokens;

            for(auto line: code) {

                tokens.push_back(tokenize_line(line));
            }

            prettyPrintTokens(tokens);

            return tokens;    
        }



        Tokenizer::token identify_token(std::string s) {

            token t;
            
            if((t.operation = is_op(s)) != BaseInt32_Instruction::NO_OP) { // if operation
                t.type = token_type::OP;
            }
            else if((t.value = is_reg(s)) != "") { // if register
                t.type = token_type::REG;
            }
            else if((t.value = is_imm(s)) != "") { // if immediate
                t.type = token_type::IMM;
            }

            return t;
        }

        

        BaseInt32_Instruction is_op(std::string s) {

            try {
                return str_ins_BI32.at(s); // throws OOR exception if `s` isn't in the map
            }
            catch (std::out_of_range& e) {
                return BaseInt32_Instruction::NO_OP;
            }
        }

        /*
        matches any string that consists of a `$`, then has a lowercase letter and a digit in that order
        e.g.) "$a0", "$z9"
        */
        const std::regex re_register("^\\$[a-z][0-9]$");

        /*
        matches with a `-` or nothing followed by any sequence of 1 or more digits
        */ 
        const std::regex re_imm10("^-?[0-9]+$");


        std::string is_reg(std::string s) {

            if(s[0] == '$' && s.length() >= 3) {

                std::string suffix = s.substr(1);
                if(std::regex_match(suffix, re_register)) {
                    return suffix;
                }
            }

            return "";
        }


        std::string is_imm(std::string s) {

            if(std::regex_match(s, re_imm10)) return s;
            else return "";
        }
    }
}


