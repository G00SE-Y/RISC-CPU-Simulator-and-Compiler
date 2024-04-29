`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module Decoder(instruction,clk,opcode,destination,funct3,source1,source2,funct7,immediate);
input [31:0] instruction;
input clk;

output [6:0] opcode;
output [4:0] destination;
output [2:0] funct3;
output [4:0] source1;
output [4:0] source2;
output [6:0] funct7;
output [31:0] immediate;

reg [31:0] internalImm;
initial internalImm = 0;

assign opcode = instruction[6:0];
assign destination = instruction[11:7];
assign funct3 = instruction[14:12];
assign source1 = instruction[19:15];
assign source2 = instruction[24:20];
assign funct7 = instruction[31:25];
assign immediate = internalImm;


always @(posedge clk) begin
    case(opcode)
    7'b0110111  :   internalImm[31:12] = instruction[31:12];    //U-type
    7'b0010111  :   internalImm[31:12] = instruction[31:12];    //U-type
    7'b1101111  :   internalImm[31:12] = instruction[31:12];    //U-type
    7'b1100111  :   internalImm[11:0]  = instruction[31:20];    //I-type
    7'b1100011  :   //B-type            
    begin
                    internalImm[11]     = instruction[7];
                    internalImm[4:1]    = instruction[11:8];
                    internalImm[10:5]   = instruction[30:25];
                    internalImm[12]     = instruction[31];
    end
    7'b0000011  :   internalImm[11:0]  = instruction[31:20];    //I-type
    7'b0100011  :   //S-type
    begin
                    internalImm[4:0]  = instruction[11:7];
                    internalImm[11:5] = instruction[31:25];
    end
    7'b0010011  :   internalImm[11:0]  = instruction[31:20];    //I-type
    default     :   internalImm = 0;
    endcase
    
end


endmodule
