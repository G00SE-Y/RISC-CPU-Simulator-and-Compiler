`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module testDecoder();

reg clk;
initial clk = 0;

always #1 clk = ~clk;

reg [31:0] instruction;
initial instruction = 32'b00000000000000000000111111100100;

wire [6:0] opcode;
wire [4:0] destination;
wire [2:0] funct3;
wire [4:0] source1;
wire [4:0] source2;
wire [6:0] funct7;
wire [31:0] immediate;

Decoder testDecode(.instruction(instruction),.clk(clk),.opcode(opcode),.destination(destination),.funct3(funct3),.source1(source1),.source2(source2),.funct7(funct7),.immediate(immediate));

endmodule
