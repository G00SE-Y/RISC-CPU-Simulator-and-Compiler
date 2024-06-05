
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
        NO_OP,          // default value

        ADD,            // Add                                          R-type              0110011
        ADDI,           // Add Immediate                                I-type              0010011
        AND,            // AND                                          R-type              0110011
        ANDI,           // AND Immediate                                I-type              0010011
        AUIPC,          // Add Upper Immediate Program Counter          U-type              0010111
        BEQ,            // Brach if Equal                               B-type              1100011
        BGE,            // Branch if Greater Than                       B-type              1100011
        BGEU,           // Branch if Greater Than Unsigned              B-type              1100011
        BLT,            // Branch if Less Than                          B-type              1100011
        BLTU,           // Branch if Less Than Unsigned                 B-type              1100011
        BNE,           // Branch if Not Equal                          B-type              1100011
        JAL,            // Jump and Link                                J-type              1101111
        JALR,           // Jump and Link Register                       I-type              1100111
        LB,             // Load Byte                                    I-type              0000011
        LBU,            // Load Byte Unsigned                           I-type              0000011
        LH,             // Load Halfword                                I-type              0000011
        LHU,            // Load Halfword Unsigned                       I-type              0000011
        LUI,            // Load Unsigned Immediate                      U-type              0110111
        LW,             // Load Word                                    I-type              0000011
        NOP,            // Incremement PC                               Immediate?          N/A
        OR,             // OR                                           R-type              0110011
        ORI,            // OR Immediate                                 I-type              0010011
        SB,             // Store Byte                                   S-type              0100011
        SH,             // Store Halfword                               S-type              0100011
        SLL,            // Shift Left Logical                           R-type              0110011
        SLLI,           // Shift Left Logical Immediate                 I-type              0010011
        SLT,            // Set Less Than                                R-type              0110011
        SLTI,           // Set Less Than Immediate                      I-type              0010011
        SLTU,           // Set Less Than Unsigned                       R-type              0110011
        SLTIU,          // Set Less Than Immediate Unsigned             I-type              0010011
        SRA,            // Shift Right Arithmetic                       R-type              0110011
        SRAI,           // Shift Right Arithmetic Immediate             I-type              0010011
        SRL,            // Shift Right Logical                          R-type              0110011
        SRLI,           // Shift Right Logic Immediate                  I-type              0010011
        SUB,            // Subtract                                     R-type              0110011
        SW,             // Store Word                                   S-type              0100011
        XOR,            // XOR                                          R-type              0110011
        XORI,           // XOR Immediate                                I-type              0010011

        SYSCALL,        // Performas a system call (only used for I/O currently)
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
        {"syscall",     BaseInt32_Instruction::SYSCALL},
};

#endif