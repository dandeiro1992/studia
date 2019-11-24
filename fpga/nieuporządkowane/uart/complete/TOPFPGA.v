module TOPFPGA (
	input RX,
	input clk,
	output TX

);

reg jeden = 1'b1;

reg [7:0] bufor;
reg start;

wire [7:0] temp1;
wire temp2;

wire tx_ready;

assign JEDEN = jeden;
assign tdata_in = bufor;


rUART receiver (
	.data_out	(temp1),					
	.data_valid	(temp2),			
	.data_in		(RX)	,					
	.reset		(JEDEN)	,			
	.clk			(clk)							
);

tUART transmitter (
	.data_out	(TX),
	.tx_ready	(tx_ready),
	.start 		(start),
	.data_in		(tdata_in),
	.reset 		(JEDEN),
	.clk 		(clk)

);

initial begin

	start <= 1'b0;
	jeden <= 1'b1;
	
end



always @ (posedge clk) begin
	if (tx_ready) begin
		start <= 1'b1;
	end else begin
		start <= 1'b0;
	end
	

end

always @ (posedge clk) begin
	if (temp2) begin
		bufor <= temp1;
	end

end


endmodule
