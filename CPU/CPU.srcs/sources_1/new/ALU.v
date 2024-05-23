`timescale 1ns / 1ps

/*
    By: Donovan Reynolds
*/


/*
    Currently Done Ops:
    ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR,  AND


*/

module ALU(result,source1,source2,funct3,funct7,opcode,clk);

input [31:0]  source1;
input [31:0]  source2;
input [2:0]   funct3;
input [6:0]   funct7;
input [6:0]   opcode;
input         clk;

output [31:0] result;

reg    [31:0] internalResult;

initial internalResult = 0;

assign result = internalResult;



always @(posedge clk) begin
    /*
    opcode 0110011 used for ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR,  AND
    funct3:                 000, 000, 001, 010, 011,  100, 101, 101, 110, 111

    funct7: 0100000 used for only SUB and SRA
    */
    if (opcode == 7'b0110011)begin
        case(funct3)
            0: internalResult <= (funct7 == 7'b01) ? source1 - source2 : source1 + source2; 
            1: internalResult <= source1 << source2[4:0]; 
            2: begin 
                if (source1[31] == 1 && source2[31] == 0) internalResult <= 1;
                else if (source1[31] == 0 && source2[31] == 1) internalResult <= 0;
                else internalResult <= (source1<source2) ? 1 : 0;
            end
            3: internalResult <= (source1<source2) ? 1 : 0; //By default verilog is unsigned here
            4: internalResult <= (source1 ^ source2);
            5: internalResult <= source1 >> source2[4:0];
            6: begin
                internalResult <= source1 >> source2[4:0];
                if (source1[31] == 1) internalResult[31] <= 1;
            end
            7: internalResult <= source1 | source2;
            8: internalResult <= source1 & source2;
            default: internalResult <= 0;
        endcase

    /*
    opcode b0010011 used for ADDI, SLLI, SLTI, SLTIU, XORI, SRLI, SRAI, ORI,  ANDI
    funct3:                  000,  001 , 010 , 011 ,  100 , 101 , 101 , 110 , 111

    */
    if opcode == 7'b0010011)begin
        case(funct3)
        0: internalResult <= immediate;
        default: internalResult <= 0;
        endcase
    end
    end
end


endmodule
