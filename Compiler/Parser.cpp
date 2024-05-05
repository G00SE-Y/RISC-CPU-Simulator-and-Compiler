#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Parser.h"
#include "RISCV32I_ISA.h"
#include "Tokenizer.h"

#define ADD_NEW_OPERATOR(name, NAME, type)                                              \
    Parser::definitions["name"] = Parser::Rule(                                         \
    Parser::definition_type::TERM,                                                      \
    Tokenizer::Token(Tokenizer::token_type::OPERATOR, BaseInt32_Instruction::NAME),     \
        {}                                                                              \
    );                                                                                  \
    Parser::definitions["NAME_OP"] = Parser::Rule(                                      \
        Parser::definition_type::DEF,                                                   \
        Tokenizer::Token(),                                                             \
        {"name", "TYPE_OPERANDS"}                                                                \
    );                                                                                  \



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