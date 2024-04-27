#include <iostream>
#include <string>
#include <regex>
#include <sstream>

#include "Tokenizer.h"
#include "RISCV32I_ISA.h"


namespace Tokenizer {

    // Anonymous Namespace to define helper functions
    namespace {


        // Private Function Declarations
        std::vector<Tokenizer::token> tokenize_line(std::string line); // Takes a single vector of string symbols and identifies them as tokens
        Tokenizer::token identify_token(std::string s); // Identifies a string as a token
        BaseInt32_Instruction is_op(std::string s); // Determines which operation a string is
        std::string is_reg(std::string s); // Determines if a string is a register name
        std::string is_imm(std::string s); // determines if the string is an immediate 
        void prettyPrintTokens(std::vector<std::vector<Tokenizer::token>> tokens); // Debug: prints all token data


        // Function Definitions

        void prettyPrintTokens(std::vector<std::vector<Tokenizer::token>> tokens) {

            int i = 1;
            for(auto line: tokens) {
                std::cout << "Line " << i++ << std::endl;
                for(auto tok: line) {

                    if(tok.operation != BaseInt32_Instruction::NO_OP)
                        std::cout << "Operation: " << tok.operation << std::endl;
                    else
                        std::cout << "\t\t\tType of token: " << tok.type << "\t\tValue: " << tok.value << std::endl;
                }
                std::cout << std::endl;
            }
        }


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



        Tokenizer::token identify_token(std::string s) {

            Tokenizer::token t;
            
            if((t.operation = is_op(s)) != BaseInt32_Instruction::NO_OP) { // if operation
                t.type = Tokenizer::token_type::OP;
            }
            else if((t.value = is_reg(s)) != "") { // if register
                t.type = Tokenizer::token_type::REG;
            }
            else if((t.value = is_imm(s)) != "") { // if immediate
                t.type = Tokenizer::token_type::IMM;
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
        const std::regex re_register("^\\$[a-z]+[0-9]{0,2}$");

        /*
        matches with a `-` or nothing followed by any sequence of 1 or more digits
        */ 
        const std::regex re_imm10("^-?[0-9]+$");


        std::string is_reg(std::string s) {

            if(std::regex_match(s, re_register)) {
                return s.substr(1);
            }

            return "";
        }


        std::string is_imm(std::string s) {

            if(std::regex_match(s, re_imm10)) return s;
            else return "";
        }

    } // End of anonymous namespace

    
    /*
    Takes a vector of strings in ASM and converts it into a vector of identified tokens
    */
    std::vector<std::vector<Tokenizer::token>> tokenize(std::vector<std::string> code) {

        std::vector<std::vector<Tokenizer::token>> tokens;

        for(auto line: code) {

            tokens.push_back(tokenize_line(line));
        }

        prettyPrintTokens(tokens); // debug

        return tokens;    
    }
}

