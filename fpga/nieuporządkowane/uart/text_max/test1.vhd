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
-- Signals used for edge detection circuitry
signal start_count_lead			: std_logic := '0';
signal start_count_follow		: std_logic := '0';
signal start_trans				: std_logic := '0';
signal tmp				: std_logic := '0';

signal counter						:integer :=0;
begin

-------------------------------------------------------------------------------
--								EDGE DETECTION
-------------------------------------------------------------------------------	
	-- edge detection circuitry
	start_trans <= start_count_lead and (not start_count_follow);
	
	-- Process to begin transmitting data
	-- This process fires off the State Machine
	begin_trans_proc: process(clk,zero)
	begin
		if(rising_edge(clk)) then
			if(zero = '1') then
				start_count_lead <= '0';
				start_count_follow <= '0';
			else
				start_count_lead <= not zero;
				start_count_follow <=start_count_lead;
			end if;
		end if;
	end process begin_trans_proc;
	
-------------------------------------------------------------------------------
process(clk)
	begin
		if(start_trans='1') then
		counter<=0;
		elsif(rising_edge(clk))then
		case counter is
		when 0=>data_out<='0';
		counter<=counter+1;
		when 1041=>data_out<='1';
		counter<=counter+1;
		when 2083=>data_out<='0';
		counter<=counter+1;
		when 3125=>data_out<='0';
		counter<=counter+1;
		when 4166=>data_out<='0';
		counter<=counter+1;
		when 5208=>data_out<='0';
		counter<=counter+1;
		when 6250=>data_out<='0';
		counter<=counter+1;
		when 7291=>data_out<='1';
		counter<=counter+1;
		when 8333=>data_out<='0';
		counter<=counter+1;
		when 9375=>data_out<='1';
		counter<=counter+1;
		when others =>counter<=counter+1;
		end case;
		end if;
end process;

end behavior;