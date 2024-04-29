`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module Memory(

    );

    integer file;


    

    initial begin
        file = $fopen("C:/Users/Donovan/Desktop/GitHubRepo/RISC-Compiler/CPU/memory.txt","w");
        $fwrite(file,"00000000000000000000000000000000");
        $fclose(file);
    end


    
endmodule
