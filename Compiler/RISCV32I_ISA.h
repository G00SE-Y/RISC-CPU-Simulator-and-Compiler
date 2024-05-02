
#ifndef BASE_INT
#define BASE_INT

#include <string>
#include <unordered_map>

/*
R-type: opcode: 7   rd:5        funct3:3    rs1:5   rs2:5   funct7:7
        Operation   Destination Fuction     Source1 & 2     Function

I-type: opcode: 7   rd:5        funct3:3    rs1:5   imm[11:0]:12
        Operation   Destination Function    Source  Immediate value

S-type: opcode: 7   imm[4:0]:5      funct3:3    rs1:5     rs2:5     imm[11:5]:6
        Operation   Bottom offset   Width       Base      Source    Top offset

U-type: opcode: 7   rd:5            imm[31:12]:20
        Operation   Destination     Upper 20 bits of the value with sign

B-type: Just like S-type but encoded different
B-type: opcode: 7   imm[11]:1           imm[4:1]:4    funct3:3    rs1:5     rs2:5   imm[10:5]:6    imm[12]:1
        Operation   11th bit of value   bits 1-4      Function    Source 1 & 2      bits 5-10      bit 12 Sign bit

J-type: Like U-type but only shifted 1 bit instead of 12 and encoded different
J-type: opcode: 7   rd:5        imm[19:12]:8    imm[11]:1   imm[10:1]:10    imm[20]:1
        Operation   Destination bits 12-19      bit 11      bits 1 -10      bit 20


*/


enum BaseInt32_Instruction {

                        //                                     Instruction format type     OP Codes
        ADD =       0,  // Add                                          R-type              0110011
        ADDI =      1,  // Add Immediate                                I-type              0010011
        AND =       2,  // AND                                          R-type              0110011
        ANDI =      3,  // AND Immediate                                I-type              0010011
        AUIPC =     4,  // Add Upper Immediate Program Counter          U-type              0010111
        BEQ =       5,  // Brach if Equal                               B-type              1100011
        BGE =       6,  // Branch if Greater Than                       B-type              1100011
        BGEU =      7,  // Branch if Greater Than Unsigned              B-type              1100011
        BLT =       8,  // Branch if Less Than                          B-type              1100011
        BLTU =      9,  // Branch if Less Than Unsigned                 B-type              1100011
        BNE =       10, // Branch if Not Equal                          B-type              1100011
        JAL =       11, // Jump and Link                                J-type              1101111
        JALR =      12, // Jump and Link Register                       I-type              1100111
        LB =        13, // Load Byte                                    I-type              0000011
        LBU =       14, // Load Byte Unsigned                           I-type              0000011
        LH =        15, // Load Halfword                                I-type              0000011
        LHU =       16, // Load Halfword Unsigned                       I-type              0000011
        LUI =       17, // Load Unsigned Immediate                      U-type              0110111
        LW =        18, // Load Word                                    I-type              0000011
        NOP =       19, // Incremement PC                               Immediate?          N/A
        OR =        20, // OR                                           R-type              0110011
        ORI =       21, // OR Immediate                                 I-type              0010011
        SB =        22, // Store Byte                                   S-type              0100011
        SH =        23, // Store Halfword                               S-type              0100011
        SLL =       24, // Shift Left Logical                           R-type              0110011
        SLLI =      25, // Shift Left Logical Immediate                 R-type              0010011
        SLT =       26, // Set Less Than                                R-type              0110011
        SLTI =      27, // Set Less Than Immediate                      I-type              0010011
        SLTU =      28, // Set Less Than Unsigned                       R-type              0110011
        SLTIU =     29, // Set Less Than Immediate Unsigned             I-type              0010011
        SRA =       30, // Shift Right Arithmetic                       R-type              0110011
        SRAI =      31, // Shift Right Arithmetic Immediate             R-type              0010011
        SRL =       32, // Shift Right Logical                          R-type              0110011
        SRLI =      33, // Shift Right Logic Immediate                  R-type              0010011
        SUB =       34, // Subtract                                     R-type              0110011
        SW =        35, // Store Word                                   S-type              0100011
        XOR =       36, // XOR                                          R-type              0110011
        XORI =      37, // XOR Immediate                                I-type              0010011
        NO_OP =     38,

};

/*
Possible additions to ISA:

Jump (J)

*/ 

const std::unordered_map<std::string, BaseInt32_Instruction> str_ins_BI32 {
        {"nop",         BaseInt32_Instruction::NOP},
        {"lui",         BaseInt32_Instruction::LUI},
        {"auipc",       BaseInt32_Instruction::AUIPC},
        {"jal",         BaseInt32_Instruction::JAL},
        {"jalr",        BaseInt32_Instruction::JALR},
        {"beq",         BaseInt32_Instruction::BEQ},
        {"bne",         BaseInt32_Instruction::BNE},
        {"blt",         BaseInt32_Instruction::BLT},
        {"bge",         BaseInt32_Instruction::BGE},
        {"bltu",        BaseInt32_Instruction::BLTU},
        {"bgeu",        BaseInt32_Instruction::BGEU},
        {"lb",          BaseInt32_Instruction::LB},
        {"lh",          BaseInt32_Instruction::LH},
        {"lw",          BaseInt32_Instruction::LW},
        {"lbu",         BaseInt32_Instruction::LBU},
        {"lhu",         BaseInt32_Instruction::LHU},
        {"sb",          BaseInt32_Instruction::SB},
        {"sh",          BaseInt32_Instruction::SH},
        {"sw",          BaseInt32_Instruction::SW},
        {"addi",        BaseInt32_Instruction::ADDI},
        {"slti",        BaseInt32_Instruction::SLTI},
        {"sltiu",       BaseInt32_Instruction::SLTIU},
        {"xori",        BaseInt32_Instruction::XORI},
        {"ori",         BaseInt32_Instruction::ORI},
        {"andi",        BaseInt32_Instruction::ANDI},
        {"slli",        BaseInt32_Instruction::SLLI},
        {"srli",        BaseInt32_Instruction::SRLI},
        {"srai",        BaseInt32_Instruction::SRAI},
        {"add",         BaseInt32_Instruction::ADD},
        {"sub",         BaseInt32_Instruction::SUB},
        {"sll",         BaseInt32_Instruction::SLL},
        {"slt",         BaseInt32_Instruction::SLT},
        {"sltu",        BaseInt32_Instruction::SLTU},
        {"xor",         BaseInt32_Instruction::XOR},
        {"srl",         BaseInt32_Instruction::SRL},
        {"sra",         BaseInt32_Instruction::SRA},
        {"or",          BaseInt32_Instruction::OR},
        {"and",         BaseInt32_Instruction::AND},

};

#endif