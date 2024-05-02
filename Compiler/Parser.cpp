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
        std::string encode_RType(std::string opname, std::string rd, std::string rs1, std::string rs2);
        std::string encode_IType(std::string opname, std::string rd, std::string rs1, std::string imm);
        std::string encode_SType(std::string opname, std::string rs1, std::string rs2, std::string imm);
        std::string encode_BType(std::string opname, std::string rs1, std::string rs2, std::string imm);
        std::string encode_UType(std::string opname, std::string rd, std::string imm);
        std::string encode_JType(std::string opname, std::string rd, std::string imm);


        

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


        /*
        R-type breakdown
        opcode   destination   funct3   source 1   source 2   funct7
        31-25       24-20      19-17     16-12      11-7       6-0
        */
        std::string encode_RType(std::string opname, std::string rd, std::string rs1, std::string rs2) {
            
            std::string ins = "";
            std::string funct3 = "";
            std::string funct7 = "";


            switch(str_ins_BI32.at(opname)) {
                
                case ADD:
                    ins += "add_op ";
                    funct3 += " add_f3 ";
                    funct7 += " add_f7";

                    break;
                
                case AND:
                    ins += "and_op ";
                    funct3 += " and_f3 ";
                    funct7 += " and_f7";
                    break;

                case OR:
                    ins += "op_op ";
                    funct3 += " or_f3 ";
                    funct7 += " or_f7";
                    break;
                
                case SLL:
                    ins += "sll_op ";
                    funct3 += " sll_f3 ";
                    funct7 += " sll_f7";
                    break;

                case SLLI:
                    ins += "slli_op ";
                    funct3 += " slli_f3 ";
                    funct7 += " slli_f7";
                    break;

                case SLT:
                    ins += "slt_op ";
                    funct3 += " slt_f3 ";
                    funct7 += " slt_f7";
                    break;
                
                case SLTU:
                    ins += "sltu_op ";
                    funct3 += " sltu_f3 ";
                    funct7 += " sltu_f7";
                    break;
                
                case SRA:
                    ins += "sra_op ";
                    funct3 += " sra_f3 ";
                    funct7 += " sra_f7";
                    break;
                
                case SRAI:
                    ins += "srai_op ";
                    funct3 += " srai_f3 ";
                    funct7 += " srai_f7";
                    break;

                case SRL:
                    ins += "srl_op ";
                    funct3 += " srl_f3 ";
                    funct7 += " srl_f7";
                    break;

                case SRLI:
                    ins += "srli_op ";
                    funct3 += " srli_f3 ";
                    funct7 += " srli_f7";
                    break;

                case SUB:
                    ins += "sub_op ";
                    funct3 += " sub_f3 ";
                    funct7 += " sub_f7";
                    break;

                case XOR:
                    ins += "xor_op ";
                    funct3 += " xor_f3 ";
                    funct7 += " xor_f7";
                    break;

                default:
                    return ins;
            }
        }


        /*
        I-type breakdown
        opcode   destination   funct3   source 1   imm[11:0]
        31-25       24-20      19-17     16-12         11-0
        */
        std::string encode_IType(std::string opname, std::string rd, std::string rs1, std::string imm) {

            std::string ins = "";
            std::string funct3 = "";

            switch(str_ins_BI32.at(opname)) {

                case ADDI:
                    ins += "addi_op ";
                    funct3 += " addi_f3 ";
                    break;

                case ANDI:
                    ins += "andi_op ";
                    funct3 += " andi_f3 ";
                    break;

                case JALR:
                    ins += "jalr_op ";
                    funct3 += " jalr_f3 ";
                    break;

                case LB:
                    ins += "lb_op ";
                    funct3 += " lb_f3 ";
                    break;

                case LBU:
                    ins += "lbu_op ";
                    funct3 += " lbu_f3 ";
                    break;

                case LH:
                    ins += "lh_op ";
                    funct3 += " lh_f3 ";
                    break;

                case LHU:
                    ins += "lhu_op ";
                    funct3 += " lhu_f3 ";
                    break;

                case LW:
                    ins += "lw_op ";
                    funct3 += " lw_f3 ";
                    break;

                case ORI:
                    ins += "ori_op ";
                    funct3 += " ori_f3 ";
                    break;

                case SLTI:
                    ins += "slti_op ";
                    funct3 += " slti_f3 ";
                    break;

                case SLTIU:
                    ins += "sltiu_op ";
                    funct3 += " sltiu_f3 ";
                    break;

                case XORI:
                    ins += "xori_op ";
                    funct3 += " xori_f3 ";
                    break;

                default:
                    return ins;
            }
        }


        /*
        S-type breakdown
        opcode   imm[4:0]   funct3   source 1   source 2   imm[11:5]
        31-25     24-20      19-17    16-12      11-7        6-0
        */
        std::string encode_SType(std::string opname, std::string rs1, std::string rs2, std::string imm) {

            std::string ins = "";
            std::string funct3 = "";

            switch(str_ins_BI32.at(opname)) {

                case SB:
                    ins += "sb_op ";
                    funct3 += " sb_f3 ";
                    break;

                case SH:
                    ins += "sh_op ";
                    funct3 += " sh_f3 ";
                    break;

                case SW:
                    ins += "sw_op ";
                    funct3 += " sw_f3 ";
                    break;

                default:
                    return ins; 
            }
        }


        /*
        B-type breakdown
        opcode   imm[11]   imm[4:1]   funct3   source 1   source 2   imm[10:5]   imm[12]
        31-25     24        23-20     19-17     16-12      11-7         6-1        0
        */
        std::string encode_BType(std::string opname, std::string rs1, std::string rs2, std::string imm) {

            std::string ins = "";
            std::string funct3 = "";

            switch(str_ins_BI32.at(opname)) {

                case BEQ:
                    ins += "beq_op ";
                    funct3 += " beq_f3 ";
                    break;

                case BGE:
                    ins += "bge_op ";
                    funct3 += " bge_f3 ";
                    break;

                case BGEU:
                    ins += "bgeu_op ";
                    funct3 += " bgeu_f3 ";
                    break;

                case BLT:
                    ins += "blt_op ";
                    funct3 += " blt_f3 ";
                    break;

                case BLTU:
                    ins += "bltu_op ";
                    funct3 += " bltu_f3 ";
                    break;

                case BNE:
                    ins += "bne_op ";
                    funct3 += " bne_f3 ";
                    break;

                default:
                    return ins;
            }
        }


        /*
        U-type breakdown
        opcode   destination   imm[31-12]
        31-25       24-20         19-0
        */
        std::string encode_UType(std::string opname, std::string rd, std::string imm) {

            std::string ins = "";

            switch(str_ins_BI32.at(opname)) {

                case AUIPC:
                    ins += "";
                    break;

                case LUI:
                    ins += "";
                    break;

                default:
            }
        }
        

        /*
        J-type breakdown
        opcode   destination   imm[19:12]   imm[11]   imm[10:1]   imm[20]
        31-25       24-20        19-12         11       10-1         0
        */
        std::string encode_JType(std::string opname, std::string rd, std::string imm) {
            
            std::string ins = "";

            switch(str_ins_BI32.at(opname)) {

               case JAL:
                   ins += "";
                    break;

                default:
                    return ins;
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