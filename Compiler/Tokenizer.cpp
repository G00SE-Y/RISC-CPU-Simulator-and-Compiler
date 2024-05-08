#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <cstdint>
#include <bitset>
#include <unordered_map>

#include "Tokenizer.h"
#include "RISCV32I_ISA.h"


namespace Tokenizer {

    // Anonymous Namespace to define helper functions
    namespace {


        // Private Function Declarations
        std::vector<Tokenizer::token> tokenize_line(std::string line); // Takes a single vector of string symbols and identifies them as tokens
        Tokenizer::token identify_token(std::string s); // Identifies a string as a token
        BaseInt32_Instruction is_op(std::string s); // Determines if the string is an operation and identify which operation
        std::string is_reg(std::string s); // Determines if the string is a register name
        std::string is_imm(std::string s); // Determines if the string is an immediate
        std::string is_label(std::string s); // Determines if the string is a label
        bool is_data_tag(std::string s); // Determines if the string is `.data`
        std::string is_address(std::string s); // Determines if the string is a memory location with an offset value
        bool is_comment(std::string s); // Determines if a comment has begun (comments end on a newline)
        std::string dec_to_bin(std::string s); // converts a string in base 10 to base 2
        std::string hex_to_bin(std::string s); // converts a string in base 16 to base 2
        void prettyPrintTokens(std::vector<std::vector<Tokenizer::token>> tokens); // Debug: prints all token data


        // Function Definitions

        void prettyPrintTokens(std::vector<std::vector<Tokenizer::token>> tokens) {

            int i = 1;
            for(auto line: tokens) {
                std::cout << "Line " << i++ << std::endl;
                for(auto tok: line) {

                    if(tok.type == token_type::NO_TOKEN) {
                        std::cout << "Not a token" << std::endl;
                    }
                    else if(tok.type == token_type::OPERATOR) {
                        std::cout << "Operation:\t" << tok.operation << std::endl;
                    }
                    else if (tok.type == token_type::REGISTER) {
                        std::cout << "Register:\t" << tok.value << std::endl;
                    }
                    else if (tok.type == token_type::IMMEDIATE) {
                        std::cout << "Immediate:\t" << tok.value << std::endl;
                    }
                    else if (tok.type == token_type::LABEL) {
                        std::cout << "Subroutine Tag: \t" << tok.value << std::endl;
                    }
                    else if (tok.type == token_type::DATA) {
                        std::cout << "Data Tag\t" << std::endl;
                    }
                    else if (tok.type == token_type::ADDRESS) {
                        std::cout << "Address:\t" << tok.value << " + " << tok.offset << std::endl;
                    }
                    else if (tok.type == token_type::COMMENT) {
                        std::cout << "Comment" << std::endl;
                    }
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
            if(is_comment(s)) {
                t.type = token_type::COMMENT;
            }
            else if((t.operation = is_op(s)) != BaseInt32_Instruction::NO_OP) { // if operation
                t.type = Tokenizer::token_type::OPERATOR;
                t.value = s; // useful for parsing later
            }
            else if((t.value = is_reg(s)) != "") { // if register 
                t.type = Tokenizer::token_type::REGISTER;
            }
            else if((t.value = is_label(s)) != "") { // if subroutine
                t.type = Tokenizer::token_type::LABEL;
            }
            else if(is_data_tag(s)) { // if data
                t.type = Tokenizer::token_type::DATA;
            }
            else if((t.value = is_address(s)) != "") { // if address
                t.type = Tokenizer::token_type::ADDRESS;
                std::string temp = t.value;
                t.value = temp.substr(0, temp.find(" "));
                t.offset = temp.substr(temp.find(" ") + 1);

            }
            else if((t.value = is_imm(s)) != "") { // if immediate
                t.type = Tokenizer::token_type::IMMEDIATE;
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

        std::string is_reg(std::string s) {

            if(std::regex_match(s, re_register)) {
                return s.substr(1);
            }

            return "";
        }


        /*
        Matches with a `-`, `0b` (binary encoding) or nothing followed by any sequence of 1 or more digits
        By default, a prefixless immediate is assumed to be base 10 and will be converted to binary  
        Binary encodings are signified by a `0b` prefix and any number of 0's or 1's.
        All immediate values will be left padded or truncated (tkaing the right most bits) to fit the operation's expected immediate size
        */ 
        const std::regex re_imm("(^[-]?[0-9]+$)|(^(0(b|B))[01]+$)|(^0(x|X)[a-fA-F0-9]+$)");

        std::string is_imm(std::string s) {

            if(!std::regex_match(s, re_imm)) return ""; // doesn't match

            std::string prefix = s.substr(0, 2);

            if(prefix == "0b" || prefix == "0B") return s.substr(2); // already in binary
            else if(prefix == "0x" || prefix == "0X") return hex_to_bin(s.substr(2)); // hex formatting
            else return dec_to_bin(s); // decimal formatting
        }


        /*
        Matches any alphanumeric string ending in a single `:` character
        e.g.) "loop:", "1:", "loop1:"
        */
        const std::regex re_label("^[a-zA-Z0-9][a-zA-Z0-9|_]*:$");

        std::string is_label(std::string s) {

            if(std::regex_match(s, re_label)) return s;
            else return "";
        }


        /*
        Matches `.data` exactly
        */
        const std::regex re_data_tag("^\\.data$");

        bool is_data_tag(std::string s) {

            if(std::regex_match(s, re_data_tag)) return true;
            else return false;
        }


        /*
        Matches a numeric string followed by `($`, a register name, then `)`
        */
        const std::regex re_addr("^[0-9]+\\(\\$[a-z]+[0-9]{0,2}\\)$");

        std::string is_address(std::string s) {

            if(std::regex_match(s, re_addr)) {
                int p1= s.find("(");
                std::string ret = s.substr(0, p1);
                ret += " ";
                ret += s.substr(p1 + 2, s.find(")") - p1 - 2);

                return ret;
            }
            else return "";
        }

        /*
        Matches anything that is or starts with `#`
        */
        bool is_comment(std::string s) {

            if(s[0] == '#') return true;
            else return false;
        }


        
        std::string dec_to_bin(std::string s) {

            uint32_t n = std::stoi(s);
            std::bitset<20> bin(n);

            return bin.to_string();
        }


        // this is a little cheesy, but its quick and it works
        const std::unordered_map<char, std::string> hex_byte_map {
            {'0', "0000"},
            {'1', "0001"},
            {'2', "0010"},
            {'3', "0011"},
            {'4', "0100"},
            {'5', "0101"},
            {'6', "0110"},
            {'7', "0111"},
            {'8', "1000"},
            {'9', "1001"},
            {'A', "1010"},
            {'a', "1010"},
            {'B', "1011"},
            {'b', "1011"},
            {'C', "1100"},
            {'c', "1100"},
            {'D', "1101"},
            {'d', "1101"},
            {'E', "1110"},
            {'e', "1110"},
            {'F', "1111"},
            {'f', "1111"},
        };


        std::string hex_to_bin(std::string s) {
            std::string hex = "";
            
            // the only reason this try-catch is here is because the byte_map is const. I like it const, though... :)
            try{

                for(char c: s) {
                    hex += hex_byte_map.at(c);
                }
            }
            catch(std::out_of_range) {
                std::cout << "how did we get here?" << std::endl;
            }

            return hex;
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

