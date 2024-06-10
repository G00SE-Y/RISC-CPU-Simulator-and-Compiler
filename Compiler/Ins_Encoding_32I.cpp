#include <string>
#include <vector>

#include "Ins_Encoding_32I.h"
#include "RISCV32I_ISA.h"

namespace Encode_32I {

    /*
    R-type breakdown

                    funct7   rs1     rs2    funct3   rd     opcode
    bits:           31-25   24-20   19-15   14-12   11-7     6-0
    string index:    0-6    7-11    12-16   17-19   20-24   25-31
    */
    std::string RType(std::vector<std::string> op) {

        if(op.size() != 4) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string rs1 = op[2];
        std::string rs2 = op[3];
        
        std::string ins = "";
        std::string funct3 = "";
        std::string funct7 = "";


        switch(str_ins_BI32.at(opname)) {
            
            case ADD:
                ins += "0110011";
                funct3 += "000";
                funct7 += "0000000";

                break;
            
            case AND:
                ins += "0110011";
                funct3 += "111";
                funct7 += "0000000";
                break;

            case OR:
                ins += "0110011";
                funct3 += "110";
                funct7 += "0000000";
                break;
            
            case SLL:
                ins += "0110011";
                funct3 += "001";
                funct7 += "0000000";
                break;

            case SLT:
                ins += "0110011";
                funct3 += "010";
                funct7 += "0000000";
                break;
            
            case SLTU:
                ins += "0110011";
                funct3 += "011";
                funct7 += "0000000";
                break;
            
            case SRA:
                ins += "0110011";
                funct3 += "101";
                funct7 += "0100000";
                break;

            case SRL:
                ins += "0110011";
                funct3 += "101";
                funct7 += "0000000";
                break;

            case SUB:
                ins += "0110011";
                funct3 += "000";
                funct7 += "0100000";
                break;

            case XOR:
                ins += "0110011";
                funct3 += "100";
                funct7 += "0000000";
                break;

            default:
                return ins;
        }

        std::string s = funct7 + rs2 + rs1 + funct3 + rd + ins;

        if(s.size() == 32) return s;
        else return "";
    }


    /*
    I-type breakdown (12-bit immediate)

                    imm      rs1    funct3   rd     opcode
    bits:           31-20   19-15   14-12   11-7     6-0
    string index:   0-11    12-16   17-19   20-24   25-31
    */
    std::string IType(std::vector<std::string> op) {

        if(op.size() != 4) return "";

        /*
        in SLLI, SRLI, and SRAI, `imm` will be a 5 bit encoded shamt instead of the normal 12 bit immediate and supplemented with a funct7 value
        */

        std::string opname = op[0];
        std::string rd = op[1];
        std::string rs1 = op[2];
        std::string imm = op[3]; 

        std::string ins = "";
        std::string funct3 = "";
        std::string funct7 = ""; // only used in shift logical ops

        switch(str_ins_BI32.at(opname)) {

            case ADDI:
                ins += "0010011";
                funct3 += "000";
                break;

            case ANDI:
                ins += "0010011";
                funct3 += "111";
                break;

            case JALR:
                ins += "1100111";
                funct3 += "000";
                break;

            case LB:
                ins += "0000011";
                funct3 += "000";
                break;

            case LBU:
                ins += "0000011";
                funct3 += "100";
                break;

            case LH:
                ins += "0000011";
                funct3 += "001";
                break;

            case LHU:
                ins += "0000011";
                funct3 += "101";
                break;

            case LW:
                ins += "0000011";
                funct3 += "010";
                break;

            case ORI:
                ins += "0010011";
                funct3 += "110";
                break;

            case SLLI:
                ins += "0010011";
                funct3 += "001";
                funct7 += "0000000";
                break;

            case SLTI:
                ins += "0010011";
                funct3 += "010";
                break;

            case SLTIU:
                ins += "0010011";
                funct3 += "011";
                break;

            case SRAI:
                ins += "0010011";
                funct3 += "101";
                funct7 += "0100000";
                break;

            case SRLI:
                ins += "0010011";
                funct3 += "101";
                funct7 += "0000000";
                break;

            case XORI:
                ins += "0010011";
                funct3 += "100";
                break;

            default:
                return ins;
        }
    
        std::string s = funct7 + imm + rs1 + funct3 + rd + ins;

        if(s.size() == 32) return s;
        else return "";
    }


    /*
    S-type breakdown (12-bit immediate)

                    imm[11:5]   rs2     rs1    funct3   imm[4:0]   opcode
    bits:           31-25      24-20   19-15   14-12     11-7       6-0
    string index:   0-6        7-11    12-16   17-19     20-24     25-31
    */
    std::string SType(std::vector<std::string> op) {

        if(op.size() != 4) return "";

        std::string opname = op[0];
        std::string rs1 = op[1];
        std::string rs2 = op[2];
        std::string imm = op[3];

        std::string ins = "";
        std::string funct3 = "";

        switch(str_ins_BI32.at(opname)) {

            case SB:
                ins += "0100011";
                funct3 += "000";
                break;

            case SH:
                ins += "0100011";
                funct3 += "001";
                break;

            case SW:
                ins += "0100011";
                funct3 += "010";
                break;

            default:
                return ins; 
        }

        std::string s = imm.substr(0, 7) + rs2 + rs1 + funct3 + imm.substr(7, 5) + ins;

        if(s.size() == 32) return s;
        else return "";
    }


    /*
    B-type breakdown (12-bit immediate)

                    imm[12]  imm[10:5]  rs2     rs1    funct3  imm[4:1]  imm[11]  opcode
    bits:              31      30-25   24-20   19-15   14-12     11-8      7       6-0 
    string index:      0        1-6    7-11    12-16   17-19     20-23     24     25-31
    */
    std::string BType(std::vector<std::string> op) {

        if(op.size() != 4) return "";

        std::string opname = op[0];
        std::string rs1 = op[1];
        std::string rs2 = op[2];
        std::string imm = op[3];

        std::string ins = "";
        std::string funct3 = "";

        switch(str_ins_BI32.at(opname)) {

            case BEQ:
                ins += "1100011";
                funct3 += "000";
                break;

            case BGE:
                ins += "1100011";
                funct3 += "101";
                break;

            case BGEU:
                ins += "1100011";
                funct3 += "111";
                break;

            case BLT:
                ins += "1100011";
                funct3 += "100";
                break;

            case BLTU:
                ins += "1100011";
                funct3 += "110";
                break;

            case BNE:
                ins += "1100011";
                funct3 += "001";
                break;

            default:
                return ins;
        }
    
        std::string s = imm.substr(0, 1) + imm.substr(1, 6) + rs2 + rs1 + funct3 + imm.substr(7, 4) + imm.substr(1, 1) + ins;

        if(s.size() == 32) return s;
        else return "";
    }


    /*
    U-type breakdown (20-bit immediate)

                    imm[31:12]   rd     opcode
    bits:             31-12     12-7     6-0
    string index:      0-19     20-24   25-31
    */
    std::string UType(std::vector<std::string> op) {

        if(op.size() != 3) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string imm = op[2];

        std::string ins = "";

        switch(str_ins_BI32.at(opname)) {

            case AUIPC:
                ins += "0010111";
                break;

            case LUI:
                ins += "0110111";
                break;

            default:
                return ins;
        }

        std::string s = imm + rd + ins;

        if(s.size() == 32) return s;
        else return "";
    }


    /*
    J-type breakdown (20-bit immediate)

                    imm[20]  imm[10:1]  imm[11]  imm[19:12]  rd     opcode
    bits:              31      30-21      20       19-12    11-7     6-0
    string index:      0       1-10       11       12-19    20-24   25-31
    */
    std::string JType(std::vector<std::string> op) {
        
        if(op.size() != 3) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string imm = op[2];
        
        std::string ins = "";

        switch(str_ins_BI32.at(opname)) {

            case JAL:
                ins += "1101111";
                break;

            default:
                return ins;
        }

        std::string s = imm[0] + imm.substr(10, 10) + imm[9] + imm.substr(1, 8) + rd + ins;

        if(s.size() == 32) return s;
        else return "";
    }
}