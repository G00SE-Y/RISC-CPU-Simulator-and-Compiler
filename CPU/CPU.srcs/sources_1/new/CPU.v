`timescale 1ns / 100ps
/*
    By: Donovan Reynolds
*/

module CPU();

integer curStage = 0;
integer i = 0;
integer file;

reg clk;

initial clk = 0;
always #30 clk = ~clk;

reg [31:0] instruction;
reg [31:0] allInstructions [0:2];

initial for (i = 0; i < 3; i = i + 1) allInstructions[i] = 0;

initial instruction = 0;


wire [6:0] opcode;
wire [4:0] destination;
wire [2:0] funct3;
wire [4:0] source1;
wire [4:0] source2;
wire [6:0] funct7;
wire [31:0] immediate;

wire [31:0] dataOut1;
wire [31:0] dataOut2;

reg writeEn;
initial writeEn = 0;

wire [31:0] aluResultConnection;
wire [31:0] writeFromData;

reg clkDecode;
reg clkReg;
reg clkAlu;
reg clkMem;

initial clkDecode = 0;
initial clkReg = 0;
initial clkAlu = 0;
initial clkMem = 0;


Decoder decoderStage(.instruction(instruction),.clk(clkDecode),.opcode(opcode),.destination(destination),.funct3(funct3),.source1(source1),.source2(source2),.funct7(funct7),.immediate(immediate));

Registers testRegisters(.destination(destination),.source1(source1),.source2(source2),.dataIn(writeFromData),.writeEn(writeEn),.dataOut1(dataOut1),.dataOut2(dataOut2),.clk(clkReg));

ALU alu (.result(aluResultConnection), .source1(dataOut1), .source2(dataOut2),.immediate(immediate), .funct3(funct3),.funct7(funct7),.opcode(opcode),.clk(clkAlu));

Memory mem(.aluInput(aluResultConnection), .registersInput(dataOut2), .opcode(opcode), .funct3(funct3), .clk(clkMem), .registersOutput(writeFromData));



initial begin
    i = 0;
    file = $fopen("../../../../instructions.txt","r");
    while(!$feof(file)) begin
        $fscanf(file,"%x",instruction);
        allInstructions[i] = instruction;
        i = i + 1;
    end
    $fclose(file);
    i = 0;
    instruction = allInstructions[0];
end



always @(posedge clk)begin
    instruction = allInstructions[i];
    if (curStage == 0) begin
        clkDecode = 1;
        clkReg = 0;
        curStage = curStage + 1;
    end
    else if (curStage == 1) begin
        clkReg = 1;
        clkDecode = 0;
        curStage = curStage + 1;
    end
    else if (curStage == 2) begin
        clkAlu = 1;
        clkReg = 0;
        curStage = curStage + 1;
    end
    else if (curStage == 3) begin
        clkMem = 1;
        clkAlu = 0;
        curStage = curStage + 1;
    //Things that need to write to register 
    if (opcode == 7'b0110111 || opcode == 7'b0010111 || opcode == 7'b1101111 || opcode == 7'b1100111 || opcode == 7'b0000011 || opcode == 7'b0010011 || opcode == 7'b0110011) writeEn <= 1;
    end
    else begin
    clkReg = 1;
    clkMem = 0;
    curStage = 0;
    i = i + 1;
    #1 writeEn <= 0;
    end
    

end

endmodule
