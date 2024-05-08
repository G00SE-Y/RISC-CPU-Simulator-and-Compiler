`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module Registers(destination,source1,source2,dataIn,writeEn,dataOut1,dataOut2,clk);

input [5:0] destination;
input [5:0] source1;
input [5:0] source2;
input [31:0] dataIn;
input clk;
input writeEn;

output [31:0] dataOut1;
output [31:0] dataOut2;

reg [31:0] tempDataOut1;
reg [31:0] tempDataOut2;
assign dataOut1 = tempDataOut1;
assign dataOut2 = tempDataOut2;

reg [31:0] registers [31:0];

integer i;

initial begin
    for (i = 0; i < 32; i= i + 1) begin
        registers[i] = 0;
    end
    tempDataOut1 = 0;
    tempDataOut2 = 0;
end

always @(posedge clk) begin

    tempDataOut1 <= registers[source1];
    tempDataOut2 <= registers[source2];
    if (writeEn)begin
        registers[destination] <= dataIn;
    end

end


endmodule
