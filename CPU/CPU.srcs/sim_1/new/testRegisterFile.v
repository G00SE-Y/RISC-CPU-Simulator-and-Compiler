`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module testRegisterFile();

integer i = 0;

reg clk;
initial clk = 0;

always #1 clk <= ~clk;

integer dest = 0;
integer s1 = 0;
integer s2 = 0;
integer dataIn = 0;
integer writeEn = 0;

reg [5:0] destination;
reg [5:0] source1;
reg [5:0] source2;
reg [31:0] dataIn;

reg writeEn;

wire [31:0] dataOut1;
wire [31:0] dataOut2;

initial begin
destination = 2;
source1 = 2;
source2 = 9;
dataIn = 1223;
writeEn = 0;
end

always #2 begin
    writeEn <= !writeEn;
    i = i + 1;
    dataIn = i;

end




Registers testRegisters(.destination(destination),.source1(source1),.source2(source2),.dataIn(dataIn),.writeEn(writeEn),.dataOut1(dataOut1),.dataOut2(dataOut2),.clk(clk));


endmodule
