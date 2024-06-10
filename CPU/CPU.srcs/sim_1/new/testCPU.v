`timescale 1ns / 1ps


module testCPU();
reg clk;
initial clk = 0;

always #10 clk = ~clk;
CPU cpu(clk);
endmodule
