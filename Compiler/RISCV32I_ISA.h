
#ifndef BASE_INT
#define BASE_INT

enum BaseInt{

    NO_OP =    -1,
    NOP =       0,  // Incremement PC
    LUI =       1,  // Load Unsigned Immediate
    AUIPC =     2,  // Add Upper Immediate Program Counter
    JAL =       3,  // Jump and Link
    JALR =      4,  // Jump and Link Register
    BEQ =       5,  // Brach if Equal
    BNE =       6,  // Branch if Not Equal
    BLT =       7,  // Branch if Less Than
    BGE =       8,  // Branch if Greater Than
    BLTU =      9,  // Branch if Less Than Unsigned
    BGEU =      10, // Branch if Greater Than Unsigned
    LB =        11, // Load Byte
    LH =        12, // Load Halfword
    LW =        13, // Load Word
    LBU =       14, // Load Byte Unsigned
    LHU =       15, // Load Halfword Unsigned
    SB =        16, // Store Byte
    SH =        17, // Store Halfword
    SW =        18, // Store Word
    ADDI =      19, // Add Immediate
    SLTI =      20, // Set Less Than Immediate
    SLTIU =     21, // Set Less Than Immediate Unsigned
    XORI =      22, // XOR Immediate
    ORI =       23, // OR Immediate
    ANDI =      24, // AND Immediate
    SLLI =      25, // Shift Left Logical Immediate
    SRLI =      26, // Shift Right Logic Immediate
    SRAI =      27, // Shift Right Arithmetic Immediate
    ADD =       28, // Add
    SUB =       29, // Subtract
    SLL =       30, // Shift Left Logical
    SLT =       31, // Set Less Than
    SLTU =      32, // Set Less Than Unsigned
    XOR =       33, // XOR
    SRL =       34, // Shift Right Logical
    SRA =       35, // Shift Right Arithmetic
    OR =        36, // OR
    AND =       37  // AND

};

#endif