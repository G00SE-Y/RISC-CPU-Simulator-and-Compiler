`timescale 1ns / 1ps

/*
    By: Donovan Reynolds
*/

module testALU();

reg clk;
reg [31:0]  source1;
reg [31:0]  source2;
reg [31:0]  result;
wire [2:0]  funct;
wire [6:0]  funct7;
wire [6:0]  opcode;


wire [31:0] resultConnection;


initial clk = 0;
initial source1 = -8;
initial source2 = 1;
initial result = 0;

assign funct = 6;
assign funct7 = 7'b0;
assign opcode = 7'b0110011;

ALU alu (.result(resultConnection), .source1(source1), .source2(source2), .funct3(funct),.funct7(funct7),.opcode(opcode),.clk(clk));

always @(posedge clk) begin
    result <= resultConnection;
end

always #1 clk = ~clk;


endmodule
