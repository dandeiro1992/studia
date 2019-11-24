/***************************************************
* File: testbench_example.v
* Author: Benjamin Morgan
* Class: EE 271
* Module: testbench_example
* Description: The top level module for the 
*
testbench
tutorial
* 
****************************************************/
module testbench_example(LEDR, SW);
output [0:0] LEDR;
input [2:0] SW;
mux my_mux(.f(LEDR[0]), .in0(SW[0]), .in1(SW[1]), .sel(SW[2]));
endmodule