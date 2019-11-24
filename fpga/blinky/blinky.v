module blinky (input clk, //50MHz clock
					input button, //PIN_AH17
					output reg led);
					
	//reg[31:0] counter;
	always @ (posedge button)
	
	begin 
		//if(counter<=25000000)
		//begin
			//counter<=counter+1;
		//end
		//else
		//begin
			//counter<=0;
			led<=~led;
		//end
	end
	
endmodule