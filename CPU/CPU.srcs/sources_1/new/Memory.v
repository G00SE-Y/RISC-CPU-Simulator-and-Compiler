`timescale 1ns / 1ps
/*
    By: Donovan Reynolds
*/

module Memory();

    integer file;

    integer i;
    

    initial begin
        file = $fopen("memory.txt","r");
        if (file == 0) begin
            file = $fopen("memory.txt","w");
            for (i = 0; i < 256; i = i+1) begin
                $fwrite(file,"mem%d      00000000000000000000000000000000\n",i);
            end
        end
        $fclose(file);
    end


    
endmodule
