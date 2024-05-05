#include <string>
#include <vector>

#include "Ins_Encoding_32I.h"
#include "RISCV32I_ISA.h"

namespace Encode_32I {

    /*
    R-type breakdown
    opcode   destination   funct3   source 1   source 2   funct7
    31-25       24-20      19-17     16-12      11-7       6-0
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
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";

                break;
            
            case AND:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case OR:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;
            
            case SLL:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case SLLI:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case SLT:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;
            
            case SLTU:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;
            
            case SRA:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;
            
            case SRAI:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case SRL:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case SRLI:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case SUB:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            case XOR:
                ins += "__op___";
                funct3 += "_3_";
                funct7 += "___7___";
                break;

            default:
                return ins;
        }
    
        
        ins += rd + funct3 + rs1 + rs2 + funct7;

        if(ins.size() == 32) return ins;
        else return "";
    }


    /*
    I-type breakdown
    12-bit immediate

    opcode   destination   funct3   source 1   imm[11:0]
    31-25       24-20      19-17     16-12         11-0
    */
    std::string IType(std::vector<std::string> op) {

        if(op.size() != 4) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string rs1 = op[2];
        std::string imm = op[3];

        std::string ins = "";
        std::string funct3 = "";

        switch(str_ins_BI32.at(opname)) {

            case ADDI:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case ANDI:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case JALR:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case LB:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case LBU:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case LH:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case LHU:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case LW:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case ORI:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case SLTI:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case SLTIU:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case XORI:
                ins += "__op___";
                funct3 += "_3_";
                break;

            default:
                return ins;
        }
    
        ins += rd + funct3 + rs1 + imm;

        if(ins.size() == 32) return ins;
        else return "";
    }


    /*
    S-type breakdown
    12-bit immediate

    opcode   imm[4:0]   funct3   source 1   source 2   imm[11:5]
    31-25     24-20      19-17    16-12      11-7        6-0
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
                ins += "__op___";
                funct3 += "_3_";
                break;

            case SH:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case SW:
                ins += "__op___";
                funct3 += "_3_";
                break;

            default:
                return ins; 
        }

        ins += imm.substr(7, 5) + funct3 + rs1 + rs2 + imm.substr(0, 7);

        if(ins.size() == 32) return ins;
        else return "";
    }


    /*
    B-type breakdown
    12-bit immediate

    opcode   imm[11]   imm[4:1]   funct3   source 1   source 2   imm[10:5]   imm[12]
    31-25     24        23-20     19-17     16-12      11-7         6-1        0
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
                ins += "__op___";
                funct3 += "_3_";
                break;

            case BGE:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case BGEU:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case BLT:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case BLTU:
                ins += "__op___";
                funct3 += "_3_";
                break;

            case BNE:
                ins += "__op___";
                funct3 += "_3_";
                break;

            default:
                return ins;
        }
    
        ins += imm.substr(1, 1) + imm.substr(7, 4) + funct3 + rs1 + rs2 + imm.substr(1, 6) + imm.substr(0, 1);

        if(ins.size() == 32) return ins;
        else return "";
    }


    /*
    U-type breakdown
    20-bit immediate

    opcode   destination   imm[31-12]
    31-25       24-20         19-0
    */
    std::string UType(std::vector<std::string> op) {

        if(op.size() != 3) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string imm = op[2];

        std::string ins = "";

        switch(str_ins_BI32.at(opname)) {

            case AUIPC:
                ins += "__op___";
                break;

            case LUI:
                ins += "__op___";
                break;

            default:
                return ins;
        }

        ins += rd + imm;

        if(ins.size() == 32) return ins;
        else return "";
    }


    /*
    J-type breakdown
    20-bit immediate
    
    opcode   destination   imm[19:12]   imm[11]   imm[10:1]   imm[20]
    31-25       24-20        19-12         11       10-1         0
    */
    std::string JType(std::vector<std::string> op) {
        
        if(op.size() != 3) return "";

        std::string opname = op[0];
        std::string rd = op[1];
        std::string imm = op[2];
        
        std::string ins = "";

        switch(str_ins_BI32.at(opname)) {

            case JAL:
                ins += "__op___";
                break;

            default:
                return ins;
        }

        ins += rd + imm.substr(1, 19) + imm.substr(0, 1);

        if(ins.size() == 32) return ins;
        else return "";
    }
}