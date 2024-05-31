#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <regex>

#include "Parser.h"
#include "RISCV32I_ISA.h"
#include "Tokenizer.h"
#include "Ins_Encoding_32I.h"


// thse 2 macros save 360 lines of code
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


#define OPERATOR_SWITCH(NAME, type)                                                     \
    case NAME:                                                                          \
    return parse_operation_switch(#NAME "_OP", Encode_32I::type, start, stop);          \



namespace Parser {

    std::unordered_map<std::string, Parser::Rule> definitions;
    std::unordered_map<std::string, std::string> registers;

    void init_definitions();
    void init_registers();
    
    namespace {


        // parse_operation only parses ONE operation!!!
        Parser::Compiler_Return parse_operation(std::vector<Tokenizer::Token>::iterator start, std::vector<Tokenizer::Token>::iterator end);
        // this function saves hundreds of lines of code... don't @ me
        Parser::Compiler_Return parse_operation_switch(std::string rule_name, std::string encoder(std::vector<std::string>), std::vector<Tokenizer::token>::iterator start, std::vector<Tokenizer::token>::iterator stop);
        
        // functions for verifying that terminals are valid/formatting them
        std::string verify(std::string type, Tokenizer::token tok);
        std::string verify_register(std::string r);
        std::string verify_immediate5(std::string imm);
        std::string verify_immediate12(std::string imm);
        std::string verify_immediate20(std::string imm);

        // used for NON-INFINITE recursive rule expansion
        std::vector<std::string> expand_rule_list(std::vector<std::string> rules);

        void pretty_print_definitions(); // debug Note: this will print a lot of text



        // all terminals currently only have lowercase names, so this works. Might be worth devolping a better convention // todo
        const std::regex re_terminal("^[a-z]*[0-9]{0,2}$");
        std::vector<std::string> expand_rule_list(std::vector<std::string> rules) {
            
            for(std::size_t i = 0; i < rules.size(); i++) {
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

            std::cout << type << " : " << tok.value << std::endl;

            if(type == "register") return verify_register(tok.value);
            else if(type == "immediate5") return verify_immediate5(tok.value);
            else if(type == "immediate12") return verify_immediate12(tok.value);
            else if(type == "immediate20") return verify_immediate20(tok.value);

            else return tok.value;
        }


        std::string verify_register(std::string r) {
            std::cout << "register " << r << " became ";

            try{
                r = registers.at(r);
            }
            catch(std::out_of_range& e) {
                return "";
            }

            std::cout << r << std::endl;
            return r;
        }

        const std::regex re_bin5bit("[0|1]{1,5}");
        std::string verify_immediate5(std::string imm) {

            if(std::regex_match(imm, re_bin5bit)) { // already binary

                imm.insert(imm.begin(), 5 - imm.size(), '0');
            }
            else {
                imm = imm.substr(imm.size() - 5, 5);
            }

            std::cout << "immediate " << imm << " became ";
            std::cout << imm << "(" << imm.size() << ")" << std::endl;
            return imm;
        }

        const std::regex re_bin12bit("[0|1]{1,12}");
        std::string verify_immediate12(std::string imm) {

            if(std::regex_match(imm, re_bin12bit)) { // already binary

                imm.insert(imm.begin(), 12 - imm.size(), '0');
            }
            else {
                imm = imm.substr(imm.size() - 12, 12);
            }

            std::cout << "immediate " << imm << " became ";
            std::cout << imm << "(" << imm.size() << ")" << std::endl;
            return imm;
        }


        const std::regex re_bin20bit("[0|1]{1,20}");
        std::string verify_immediate20(std::string imm) {

            if(std::regex_match(imm, re_bin20bit)) { // already binary

                imm.insert(imm.begin(), 20 - imm.size(), '0');
            }
            else {
                imm = imm.substr(imm.size() - 20, 20);
            }

            std::cout << "immediate " << imm << " became ";
            std::cout << imm << "(" << imm.size() << ")" << std::endl;
            return imm;
        }



        Parser::Compiler_Return parse_operation_switch(std::string rule_name, std::string encoder(std::vector<std::string>), std::vector<Tokenizer::token>::iterator start, std::vector<Tokenizer::token>::iterator stop) {
            
            Parser::Compiler_Return ret;
            ret.error = "";

            std::vector<std::string> rule_list = expand_rule_list(definitions[rule_name].def);
            std::string s;
            std::vector<std::string> operands;

            for(std::size_t i = 0; i < rule_list.size(); i++, start++) {
                
                if((s = verify(rule_list[i], *start)).size() == 0) { // if it isn't verified
                    
                    ret.error = "Unrecognized symbol: `" + (*start).value +"`   Expected symbol of type '" + rule_list[i] +"'\n";

                    return ret;
                }

                operands.push_back(s);
            }

            ret.output.push_back(encoder(operands));

            if(ret.output.back().size() != 0) return ret;
            else {
                ret.error = "Invalid operands for `" + rule_list[0] + "`:";
                for(auto s: operands) {
                    ret.error += " " + s; 
                }
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

                    // all of these just call the operator switch function, but this makes my life easier and the code smaller
                    OPERATOR_SWITCH(ADD, RType)
                    OPERATOR_SWITCH(ADDI, IType)
                    OPERATOR_SWITCH(AND, RType)
                    OPERATOR_SWITCH(ANDI, IType)
                    OPERATOR_SWITCH(AUIPC, UType)
                    OPERATOR_SWITCH(BEQ, BType)
                    OPERATOR_SWITCH(BGE, BType)
                    OPERATOR_SWITCH(BGEU, BType)
                    OPERATOR_SWITCH(BLT, BType)
                    OPERATOR_SWITCH(BLTU, BType)
                    OPERATOR_SWITCH(BNE, BType)
                    OPERATOR_SWITCH(JAL, JType)
                    OPERATOR_SWITCH(JALR, IType)
                    OPERATOR_SWITCH(LB, IType)
                    OPERATOR_SWITCH(LBU, IType)
                    OPERATOR_SWITCH(LH, IType)
                    OPERATOR_SWITCH(LHU, IType)
                    OPERATOR_SWITCH(LUI, UType)
                    OPERATOR_SWITCH(LW, IType)
                    OPERATOR_SWITCH(OR, RType)
                    OPERATOR_SWITCH(ORI, IType)
                    OPERATOR_SWITCH(SB, SType)
                    OPERATOR_SWITCH(SH, SType)
                    OPERATOR_SWITCH(SLL, RType)
                    OPERATOR_SWITCH(SLLI, IType)
                    OPERATOR_SWITCH(SLT, RType)
                    OPERATOR_SWITCH(SLTI, IType)
                    OPERATOR_SWITCH(SLTU, RType)
                    OPERATOR_SWITCH(SLTIU, IType)
                    OPERATOR_SWITCH(SRA, RType)
                    OPERATOR_SWITCH(SRAI, IType)
                    OPERATOR_SWITCH(SRL, RType)
                    OPERATOR_SWITCH(SRLI, IType)
                    OPERATOR_SWITCH(SUB, RType)
                    OPERATOR_SWITCH(SW, SType)
                    OPERATOR_SWITCH(XOR, RType)
                    OPERATOR_SWITCH(XORI, IType)

                    case NOP: // special case because NOP is just ADD with the pc and takes no operands
                        
                        if(start + 1 == stop) { // nop takes no operands
                            
                            ret.output.push_back(Encode_32I::IType(std::vector<std::string>({"addi", "00000", "00000", "000000000000"})));

                            if(ret.output.back().size() != 0) {
                                ret.error = "";

                                return ret;
                            }
                        }

                    default: // this should never be reached
                        std::cout << "Something broke in the parser (but the issue is probably in the tokenizer)  :'(" << std::endl; 
                        ret.error = "Unrecognized operation: `" + (*start).value + "`";

                        return ret;
                }
            }
            else {
                ret.error = "Unrecognized operation: `" + (*start).value +"`";

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
        init_registers();

        Parser::Compiler_Return ret;

        for(auto &line: tokens) {

            for(std::size_t i = 0; i < line.size(); i++) { // convert all addresses into register, immediate
                if(line[i].type == Tokenizer::token_type::ADDRESS) {
                    line.insert(line.begin() + i, Tokenizer::Token(Tokenizer::token_type::REGISTER, line[i].offset));
                    line[i + 1].type = Tokenizer::token_type::IMMEDIATE;
                }
            }

            

            Parser::Compiler_Return ret1 = parse_operation(line.begin(), line.end());
            ret.error += ret1.error;
            ret.output.push_back(ret1.output[0]);

            if(ret.error.size()) break;
        }


        return ret;
    }


    void init_registers() {
        Parser::registers["rd"] = "11111";
        Parser::registers["r0"] = "00000";
        Parser::registers["r1"] = "00001";
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

        Parser::definitions["immediate12"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::IMMEDIATE, BaseInt32_Instruction::NO_OP), 
            {}
        );

        Parser::definitions["immediate20"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::IMMEDIATE, BaseInt32_Instruction::NO_OP), 
            {}
        );

        // this is a special case for SLLI, SRLI, and SRAI which have a 5-bit encoded shamt instead of the 12-bit immediate expected by their op type
        Parser::definitions["immediate5"] = Parser::Rule(
            Parser::definition_type::TERM, 
            Tokenizer::Token(Tokenizer::token_type::IMMEDIATE, BaseInt32_Instruction::NO_OP), 
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
            {"register", "register", "immediate12"}
        );

        Parser::definitions["SHIFT_ITYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate5"}
        );

        Parser::definitions["STYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate12"}
        );

        Parser::definitions["BTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "register", "immediate12"}
        );

        Parser::definitions["UTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "immediate20"}
        );

        Parser::definitions["JTYPE_OPERANDS"] = Parser::Rule(
            Parser::definition_type::DEF, 
            Tokenizer::Token(), 
            {"register", "immediate20"}
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
        ADD_NEW_OPERATOR(slli, SLLI, SHIFT_I)
        ADD_NEW_OPERATOR(slt, SLT, R)
        ADD_NEW_OPERATOR(slti, SLTI, I)
        ADD_NEW_OPERATOR(sltu, SLTU, R)
        ADD_NEW_OPERATOR(sltiu, SLTIU, I)
        ADD_NEW_OPERATOR(sra, SRA, R)
        ADD_NEW_OPERATOR(srai, SRAI, SHIFT_I)
        ADD_NEW_OPERATOR(srl, SRL, R)
        ADD_NEW_OPERATOR(srli, SRLI, SHIFT_I)
        ADD_NEW_OPERATOR(sub, SUB, R)
        ADD_NEW_OPERATOR(sw, SW, S)
        ADD_NEW_OPERATOR(xor, XOR, R)
        ADD_NEW_OPERATOR(xori, XORI, I)
    }
}