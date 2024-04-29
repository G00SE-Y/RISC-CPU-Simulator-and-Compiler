`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/


/*
    Currently Done Ops:
    ADD, 

*/

module ALU(result,source1,source2,funct,funct7,opcode,clk);

input [31:0]  source1;
input [31:0]  source2;
input [2:0]   funct;
input [6:0]   funct7;
input [6:0]   opcode;
input         clk;

output [31:0] result;

reg    [31:0] internalResult;

initial internalResult = 0;

assign result = internalResult;

always @(posedge clk) begin
    if (opcode == 7'b0110011) internalResult = source1 + source2;
end


endmodule
