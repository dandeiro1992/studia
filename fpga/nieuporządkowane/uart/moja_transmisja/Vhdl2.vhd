library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;
use std.textio.all ;
use ieee.std_logic_textio.all ;


-- Entity
entity tUART_sim is
port (
	start_sim		: out std_logic;	
	data_out_sim 		:out  std_logic_vector(7 downto 0);
	reset_sim 		: out std_logic;
	clk 		: in std_logic);
end;


-- Architecture
architecture dzialanie of tUART_sim is
signal clk_sim 			: std_logic := '0';

begin

	clk_proc : process
		begin
		wait for 20 ns;
		clk_sim <= not clk_sim;
	end process clk_proc;
	
	
	-- Simulate the stimulus's to our design
	stimulus:  process
	begin
	
		-- Pull reset high
		wait for 4 ns;
		reset_sim <= '1';
		
		wait for 240 us;
		
		-- Transmit 'H'
		data_out_sim <= x"48";
		start_sim <= '1';
		wait for 60 ns;
		start_sim <= '0';
		wait for 86806 ns;	-- transmission should be complete
		wait for 52500 ns;	-- delay should be complete (52us)
		
		wait for 240 us;
		
		-- Transmit 'E'
		data_out_sim <= x"45";
		start_sim <= '1';
		wait for 60 ns;
		start_sim <= '0';
		wait for 86806 ns;	-- transmission should be complete
		wait for 52500 ns;	-- delay should be complete (52us)
		
		wait for 240 us;
		
		-- Transmit 'L'
		data_out_sim <= x"4C";
		start_sim <= '1';
		wait for 60 ns;
		start_sim <= '0';
		wait for 86806 ns;	-- transmission should be complete
		wait for 52500 ns;	-- delay should be complete (52us)
		
		wait for 240 us;
		
		-- Transmit 'L'
		data_out_sim <= x"4C";
		start_sim <= '1';
		wait for 60 ns;
		start_sim <= '0';
		wait for 86806 ns;	-- transmission should be complete
		wait for 52500 ns;	-- delay should be complete (52us)
		
		wait for 240 us;
		
		-- Transmit 'O'
		data_out_sim <= x"4F";
		start_sim <= '1';
		wait for 60 ns;
		start_sim <= '0';
		wait for 86806 ns;	-- transmission should be complete
		wait for 52500 ns;	-- delay should be complete (52us)
		
		-- Total simulation time of 2048 uS
		-- Report that UART Terminal has completed
		report "UART Terminal Test Completed!";
	end process stimulus;
end dzialanie;