`timescale 1ns / 1ps

module randomWriteTest();


    integer file;
    integer i;


    
    //Either open the memory file that already exists or make a new one of all 0's
    initial begin
        file = $fopen("../../../../randomTest.txt","w");
        $fwrite(file,"yo");
        $fclose(file);
        end
endmodule
