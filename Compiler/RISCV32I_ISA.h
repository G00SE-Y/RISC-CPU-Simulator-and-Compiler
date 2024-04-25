
#ifndef BASE_INT
#define BASE_INT



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


enum BaseInt{

    NO_OP =    -1,

                    //                                                                  OP Codes
    NOP =       0,  // Incremement PC                               Immediate?          N/A
    LUI =       1,  // Load Unsigned Immediate                      U-type              0110111
    AUIPC =     2,  // Add Upper Immediate Program Counter          U-type              0010111
    JAL =       3,  // Jump and Link                                U-type              1101111
    JALR =      4,  // Jump and Link Register                       I-type              1100111
    BEQ =       5,  // Brach if Equal                               B-type              1100011
    BNE =       6,  // Branch if Not Equal                          B-type              1100011
    BLT =       7,  // Branch if Less Than                          B-type              1100011
    BGE =       8,  // Branch if Greater Than                       B-type              1100011
    BLTU =      9,  // Branch if Less Than Unsigned                 B-type              1100011
    BGEU =      10, // Branch if Greater Than Unsigned              B-type              1100011
    LB =        11, // Load Byte                                    I-type              0000011
    LH =        12, // Load Halfword                                I-type              0000011
    LW =        13, // Load Word                                    I-type              0000011
    LBU =       14, // Load Byte Unsigned                           I-type              0000011
    LHU =       15, // Load Halfword Unsigned                       I-type              0000011
    SB =        16, // Store Byte                                   S-type              0100011
    SH =        17, // Store Halfword                               S-type              0100011
    SW =        18, // Store Word                                   S-type              0100011
    ADDI =      19, // Add Immediate                                I-type              0010011
    SLTI =      20, // Set Less Than Immediate                      I-type              0010011
    SLTIU =     21, // Set Less Than Immediate Unsigned             I-type              0010011
    XORI =      22, // XOR Immediate                                I-type              0010011
    ORI =       23, // OR Immediate                                 I-type              0010011
    ANDI =      24, // AND Immediate                                I-type              0010011
    SLLI =      25, // Shift Left Logical Immediate                 R-type              0010011
    SRLI =      26, // Shift Right Logic Immediate                  R-type              0010011
    SRAI =      27, // Shift Right Arithmetic Immediate             R-type              0010011
    ADD =       28, // Add                                          R-type              0110011
    SUB =       29, // Subtract                                     R-type              0110011
    SLL =       30, // Shift Left Logical                           R-type              0110011
    SLT =       31, // Set Less Than                                R-type              0110011
    SLTU =      32, // Set Less Than Unsigned                       R-type              0110011
    XOR =       33, // XOR                                          R-type              0110011
    SRL =       34, // Shift Right Logical                          R-type              0110011
    SRA =       35, // Shift Right Arithmetic                       R-type              0110011
    OR =        36, // OR                                           R-type              0110011
    AND =       37  // AND                                          R-type              0110011

};

#endif