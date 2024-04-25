
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

//OPCODES TODO


enum BaseInt{

    NO_OP =    -1,


    NOP =       0,  // Incremement PC                               Immediate?
    LUI =       1,  // Load Unsigned Immediate                      U-type
    AUIPC =     2,  // Add Upper Immediate Program Counter          U-type
    JAL =       3,  // Jump and Link                                U-type
    JALR =      4,  // Jump and Link Register                       I-type
    BEQ =       5,  // Brach if Equal                               B-type
    BNE =       6,  // Branch if Not Equal                          B-type
    BLT =       7,  // Branch if Less Than                          B-type
    BGE =       8,  // Branch if Greater Than                       B-type
    BLTU =      9,  // Branch if Less Than Unsigned                 B-type
    BGEU =      10, // Branch if Greater Than Unsigned              B-type
    LB =        11, // Load Byte                                    I-type
    LH =        12, // Load Halfword                                I-type
    LW =        13, // Load Word                                    I-type
    LBU =       14, // Load Byte Unsigned                           I-type
    LHU =       15, // Load Halfword Unsigned                       I-type
    SB =        16, // Store Byte                                   S-type
    SH =        17, // Store Halfword                               S-type
    SW =        18, // Store Word                                   S-type
    ADDI =      19, // Add Immediate                                I-type
    SLTI =      20, // Set Less Than Immediate                      I-type
    SLTIU =     21, // Set Less Than Immediate Unsigned             I-type
    XORI =      22, // XOR Immediate                                I-type
    ORI =       23, // OR Immediate                                 I-type
    ANDI =      24, // AND Immediate                                I-type
    SLLI =      25, // Shift Left Logical Immediate                 R-type
    SRLI =      26, // Shift Right Logic Immediate                  R-type
    SRAI =      27, // Shift Right Arithmetic Immediate             R-type
    ADD =       28, // Add                                          R-type
    SUB =       29, // Subtract                                     R-type
    SLL =       30, // Shift Left Logical                           R-type
    SLT =       31, // Set Less Than                                R-type
    SLTU =      32, // Set Less Than Unsigned                       R-type
    XOR =       33, // XOR                                          R-type
    SRL =       34, // Shift Right Logical                          R-type
    SRA =       35, // Shift Right Arithmetic                       R-type
    OR =        36, // OR                                           R-type
    AND =       37  // AND                                          R-type

};

#endif