#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <regex>

#include "Parser.h"
#include "RISCV32I_ISA.h"
#include "Tokenizer.h"
#include "Ins_Encoding_32I.h"

#define ADD_NEW_OPERATOR(name, NAME, type)                                              \
    Parser::definitions[#name] = Parser::Rule(                                          \
    Parser::definition_type::TERM,                                                      \
    Tokenizer::Token(Tokenizer::token_type::OPERATOR, BaseInt32_Instruction::NAME),     \
        {}                                                                              \
    );                                                                                  \
    Parser::definitions[#NAME "_OP"] = Parser::Rule(                                    \
        Parser::definition_type::DEF,                                                   \
        Tokenizer::Token(),                                                             \
        {#name, #type "TYPE_OPERANDS"}                                                  \
    );                                                                                  \



namespace Parser {

    std::unordered_map<std::string, Parser::Rule> definitions;

    void init_definitions();
    
    namespace {


        // parse_operation only parses ONE operation!!!
        Parser::Compiler_Return parse_operation(std::vector<Tokenizer::Token>::iterator start, std::vector<Tokenizer::Token>::iterator end);
        // this function saves hundreds of lines of code... don't @ me
        Parser::Compiler_Return parse_operation_switch(std::string rule_name, std::string encoder(std::vector<std::string>), std::vector<std::string>::iterator start, std::vector<std::string>::iterator stop);
        
        // functions for parsing terminals
        std::string parse_regiser(Tokenizer::token);

        // functions for verifying that terminals are valid/formatting them
        std::string verify(std::string type, Tokenizer::token tok);
        std::string verify_register(std::string r);

        // used for NON-INFINITE recursive rule expansion
        std::vector<std::string> expand_rule_list(std::vector<std::string> rules);

        void pretty_print_definitions(); // debug Note: this will print a lot of text



        // all terminals currently only have lowercase names, so this works. Might be worth devolping a better convention // todo
        const std::regex re_terminal("^[a-z]*$");
        std::vector<std::string> expand_rule_list(std::vector<std::string> rules) {
            
            for(int i = 0; i < rules.size(); i++) {
                if(!std::regex_match(rules[i], re_terminal)) { // if it is expandable
                    
                    std::vector<std::string> new_rules = definitions[rules[i]].def;
                    int tmp = i + 1;
                    
                    for(auto s: new_rules) {
                        rules.insert(rules.begin() + tmp++, s);
                    }
                    rules.erase(rules.begin() + i);
                }
            }

            return rules;
        }


        std::string verify(std::string type, Tokenizer::token tok) { // todo
            return tok.value;
        }

        Parser::Compiler_Return parse_operation_switch(std::string rule_name, std::string encoder(std::vector<std::string>), std::vector<Tokenizer::token>::iterator start, std::vector<Tokenizer::token>::iterator stop) {
            
            Parser::Compiler_Return ret;
            ret.is_error = false;
            ret.error = "";
            ret.output = "";

            std::vector<std::string> rule_list = expand_rule_list(definitions[rule_name].def);
            std::string s;
            std::vector<std::string> operands;

            for(int i = 0; i < rule_list.size(); i++, start++) {
                
                if((s = verify(rule_list[i], *start)).size() == 0) { // if it isn't verified
                    
                    ret.is_error = true;
                    ret.error = "Unrecognized symbol: `" + (*start).value +"`   Expected symbol of type '" + rule_list[i] +"'\n";
                    ret.output = "";

                    return ret;
                }

                operands.push_back(s);
            }

            ret.output = encoder(operands);

            if(ret.output.size() != 0) return ret;
            else {
                ret.is_error = true;
                ret.error = "Invalid operands (error in validator?)";
            }
            
            return ret;
        }


        Parser::Compiler_Return parse_operation(std::vector<Tokenizer::Token>::iterator start, std::vector<Tokenizer::Token>::iterator stop) {

            Parser::Compiler_Return ret;


            // empty line, return
            if(start == stop) return ret;

            
            if((*start).type == Tokenizer::token_type::OPERATOR) {

                std::vector<std::string> rule_list;
                std::string s; // temp string for verification
                std::vector<std::string> operands;

                switch((*start).operation) {

                    case ADD:

                        return parse_operation_switch("ADD_OP", Encode_32I::RType, start, stop);


                    case SUB:

                        return parse_operation_switch("SUB_OP", Encode_32I::RType, start, stop);

                    default: // this should never be reached
                        std::cout << "Something broke in the parser (but the issue is probably in the tokenizer)  :'(" << std::endl; 
                        ret.error = "Unrecognized operation: `" + (*start).value + "`";
                        ret.is_error = true;
                        ret.output = "";

                        return ret;
                }
            }
            else {
                ret.is_error = true;
                ret.error = "Unrecognized operation: `" + (*start).value +"`";
                ret.output = "";

                return ret;
            }

        }


        void pretty_print_definitions() {

            std::cout << "DEFINITIONS:" << std::endl;
            auto it = definitions.begin();
            while(it != definitions.end()) {
                std::cout << (*it).first;

                if((*it).second.type == Parser::definition_type::TERM) std::cout << std::endl;
                else {

                    for(auto s: (*it).second.def) {
                        std::cout << " " << s;
                    }
                    std::cout << std::endl;
                }
                it++;

            }
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

        // used for program blocks
        Parser::definitions["label"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::LABEL, BaseInt32_Instruction::NO_OP), 
            {}
        );

        Parser::definitions["data"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::DATA, BaseInt32_Instruction::NO_OP), 
            {}
        );

        // used as operands
        Parser::definitions["register"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::REGISTER, BaseInt32_Instruction::NO_OP), 
            {}
        );

        Parser::definitions["immediate"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::IMMEDIATE, BaseInt32_Instruction::NO_OP), 
            {}
        );


        Parser::definitions["address"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::ADDRESS, BaseInt32_Instruction::NO_OP), 
            {}
        );


        // operand types
        Parser::definitions["RTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "register"}
        );

        Parser::definitions["ITYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate"}
        );

        Parser::definitions["STYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate"}
        );

        Parser::definitions["BTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate"}
        );

        Parser::definitions["UTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "immediate"}
        );

        Parser::definitions["JTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "immediate"}
        );

        
        // All the operations, I'm so sorry... it has to be done

        Parser::definitions["nop"] = Parser::Rule(
            Parser::definition_type::TERM,
            Tokenizer::Token(Tokenizer::token_type::OPERATOR, BaseInt32_Instruction::NOP),
                {}
            );
            Parser::definitions["NOP_OP"] = Parser::Rule(
                Parser::definition_type::DEF,
                Tokenizer::Token(),
                {"nop"}
        );

        ADD_NEW_OPERATOR(add, ADD, R)
        ADD_NEW_OPERATOR(addi, ADDI, I)
        ADD_NEW_OPERATOR(and, AND, R)
        ADD_NEW_OPERATOR(andi, ANDI, I)
        ADD_NEW_OPERATOR(auipc, AUIPC, U)
        ADD_NEW_OPERATOR(beq, BEQ, B)
        ADD_NEW_OPERATOR(bge, BGE, B)
        ADD_NEW_OPERATOR(bgeu, BGEU, B)
        ADD_NEW_OPERATOR(blt, BLT, B)
        ADD_NEW_OPERATOR(bltu, BLTU, B)
        ADD_NEW_OPERATOR(bne, BNE, B)
        ADD_NEW_OPERATOR(jal, JAL, J)
        ADD_NEW_OPERATOR(jalr, JALR, I)
        ADD_NEW_OPERATOR(lb, LB, I)
        ADD_NEW_OPERATOR(lbu, LBU, I)
        ADD_NEW_OPERATOR(lh, LH, I)
        ADD_NEW_OPERATOR(lhu, LHU, I)
        ADD_NEW_OPERATOR(lui, LUI, U)
        ADD_NEW_OPERATOR(lw, LW, I)
        ADD_NEW_OPERATOR(or, OR, R)
        ADD_NEW_OPERATOR(ori, ORI, I)
        ADD_NEW_OPERATOR(sb, SB, S)
        ADD_NEW_OPERATOR(sh, SH, S)
        ADD_NEW_OPERATOR(sll, SLL, R)
        ADD_NEW_OPERATOR(slli, SLLI, R)
        ADD_NEW_OPERATOR(slt, SLT, R)
        ADD_NEW_OPERATOR(slti, SLTI, I)
        ADD_NEW_OPERATOR(sltu, SLTU, R)
        ADD_NEW_OPERATOR(sltiu, SLTIU, I)
        ADD_NEW_OPERATOR(sra, SRA, R)
        ADD_NEW_OPERATOR(srai, SRAI, R)
        ADD_NEW_OPERATOR(srl, SRL, R)
        ADD_NEW_OPERATOR(srli, SRLI, R)
        ADD_NEW_OPERATOR(sub, SUB, R)
        ADD_NEW_OPERATOR(sw, SW, S)
        ADD_NEW_OPERATOR(xor, XOR, R)
        ADD_NEW_OPERATOR(xori, XORI, I)
    }
}