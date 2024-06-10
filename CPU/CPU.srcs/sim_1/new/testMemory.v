`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module testMemory();

reg clk;
reg [31:0] aluResult;
reg [31:0] fromRegisters;

wire [31:0] fromMemory;

wire [2:0]  funct;
wire [6:0]  opcode;



initial clk = 0;
initial fromRegisters = 8'h00000080;
initial aluResult = 0;




assign funct = 2;
assign opcode = 7'b0000011;

Memory mem(.aluInput(aluResult), .registersInput(fromRegisters), .opcode(opcode), .funct3(funct), .clk(clk), .registersOutput(fromMemory));

always #1 clk = ~clk;





endmodule
