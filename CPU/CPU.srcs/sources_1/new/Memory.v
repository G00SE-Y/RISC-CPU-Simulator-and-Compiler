`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module Memory(aluInput, registersInput, opcode, funct3, clk, registersOutput);

    input [31:0] aluInput;
    input [31:0] registersInput;
    input [6:0] opcode;
    input [2:0] funct3;
    input clk;
    
    output [31:0] registersOutput;

    integer file;
    integer i;

    reg [31:0] address;
    reg [31:0] val;

    reg [31:0] allMemory [0:1023];

    assign registersOutput = val;

    
    //Either open the memory file that already exists or make a new one of all 0's
    initial begin
        i = 0;
        file = $fopen("../../../../memory.txt","r");
        while(!$feof(file)) begin
            $fscanf(file,"%x %x",address,val);
            allMemory[address/4] <= val;
        end
        $fclose(file);
    end

    always @(posedge clk) begin
        /*
            Store operations    SB, SH, SW
            funct3              0,  1,  2
        */
        if (opcode == 7'b0100011) begin
            case(funct3)
            0: allMemory[aluInput/4] <= (allMemory[aluInput/4] & 8'hffffff00) + registersInput[7:0];
            1: allMemory[aluInput/4] <= (allMemory[aluInput/4] & 8'hffff0000) + registersInput[15:0];
            2: allMemory[aluInput/4] <= registersInput;
            endcase
        end

        /*
            Load operations LB, LH, LW, LBU, LHU
            funct3          0,  1,  2,  4,   5
        */
        if (opcode == 7'b0000011)begin
            case(funct3)
            0: begin
                if (allMemory[aluInput/4] > 127) val <=  (allMemory[aluInput/4] & 8'h000000ff) + 4294967040;
                else val <= allMemory[aluInput/4] & 8'h000000ff;
            end
            1: begin
                if (allMemory[aluInput/4][15] == 1) val <=  (allMemory[aluInput/4] & 8'h0000ffff) + 4294901760;
                else val <= allMemory[aluInput/4] & 8'h0000ffff;
            end
            2: val <= allMemory[aluInput/4];
            4: val <= (allMemory[aluInput/4] & 8'h000000ff);
            5: val <= (allMemory[aluInput/4] & 8'h0000ffff);

            endcase
        end

        //LUI 
        if (opcode == 7'b0110111)  val <= aluInput;
        //AUIPC
        if (opcode == 7'b0010111) val <= aluInput;

        //Operations to write back to register
        if (opcode == 7'b0110011 || opcode == 7'b0010011) val <= aluInput;
                
    end



    
endmodule
