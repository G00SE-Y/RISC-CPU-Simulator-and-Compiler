#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Parser.h"
#include "RISCV32I_ISA.h"
#include "Tokenizer.h"



namespace Parser {

    std::unordered_map<std::string, Parser::Rule> definitions;

    void init_definitions();

    namespace {

        Parser::Compiler_Return parse_operation(std::vector<Tokenizer::Token>::iterator start, std::vector<Tokenizer::Token>::iterator end);
        bool verify_terminal(std::string type, Tokenizer::token tok);        

        Parser::Compiler_Return parse_operation(std::vector<Tokenizer::Token>::iterator start, std::vector<Tokenizer::Token>::iterator end) {

            Parser::Compiler_Return ret;

            // empty line or file
            if(start == end) {
                ret.error = "Write some code, idiot!\n";
                ret.is_error = true;
                ret.output = "";

                return ret;
            }

            while(start != end) {
                
                if((*start).type == Tokenizer::token_type::OPERATOR) {

                    std::vector<std::string> rule_list;

                    switch((*start).operation) {

                        case ADD:

                            // ret.output += "[add_opcode]";

                            rule_list = Parser::definitions["ADD_OP"].def;

                            for(int i = 0; i < rule_list.size(); i++, start++) {
                                
                                if(verify_terminal(rule_list[i], *start)) {
                                    ret.output += "terminal(" + (*start).value + ") ";
                                }
                            }

                            return ret;

                        case SUB:

                            ret.output += "[sub_opcode]";

                            rule_list = Parser::definitions["SUB_OP"].def;

                            for(int i = 0; i < rule_list.size(); i++, start++) {
                                
                                if(verify_terminal(rule_list[i], *start)) {
                                    ret.output += "terminal(" + (*start).value + ") ";
                                }
                            }

                            return ret;

                        default:

                            ret.error = "Some error occured in parsing `" + (*start).value + "` .";
                            ret.is_error = true;

                            return ret;// early stopping if error is found
                    }
                }
            }

            return ret;

        }


        bool verify_terminal(std::string type, Tokenizer::token tok) {

            // std::cout << "verify(" << type << ", " << tok.value << ")" << std::endl;
            
            if(type == "register") {
                // verify that it is a valid register
                return true;
            }

            return false;
        }


    }

    Parser::Compiler_Return parse(std::vector<std::vector<Tokenizer::token>> tokens) {

        init_definitions();

        Parser::Compiler_Return ret1 = parse_operation(tokens[0].begin(), tokens[0].end());
        Parser::Compiler_Return ret2 = parse_operation(tokens[1].begin(), tokens[1].end());

        ret1.error += ret2.error;
        ret1.is_error |= ret2.is_error;
        ret1.output += ret2.output;

        return ret1;
    }


    // This is not going to be pretty
    void init_definitions() {
        Parser::definitions["add"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::OPERATOR, BaseInt32_Instruction::ADD), 
            {}
        );

        Parser::definitions["register"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::REGISTER, BaseInt32_Instruction::NO_OP), 
            {}
        );

        Parser::definitions["ADD_OP"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"add", "register", "register", "register"}
        );

        Parser::definitions["sub"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::OPERATOR, BaseInt32_Instruction::SUB), 
            {}
        );

        Parser::definitions["SUB_OP"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"sub", "register", "register", "register"}
        );
    }
}