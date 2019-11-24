library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;
use std.textio.all ;
use ieee.std_logic_textio.all ;

-- Entity Declaration

entity test1 is
port (
	data_out	:out std_logic;
	clk		:in std_logic;
	zero		:in std_logic);
end test1;


-- Architecture

architecture behavior of test1 is
signal counter:integer :=0;
begin
process(clk)
	begin
		if(zero='1') then
		counter<=0;
		elsif(rising_edge(clk))then
		case counter is
		when 0=>data_out<='0';
		counter<=counter+1;
		when 5208=>data_out<='1';
		counter<=counter+1;
		when 10416=>data_out<='0';
		counter<=counter+1;
		when 15625=>data_out<='0';
		counter<=counter+1;
		when 20833=>data_out<='0';
		counter<=counter+1;
		when 26041=>data_out<='0';
		counter<=counter+1;
		when 31250=>data_out<='0';
		counter<=counter+1;
		when 36458=>data_out<='1';
		counter<=counter+1;
		when 41666=>data_out<='0';
		counter<=counter+1;
		when 46875=>data_out<='1';
		counter<=counter+1;
		when others =>counter<=counter+1;
		end case;
		end if;
end process;

end behavior;