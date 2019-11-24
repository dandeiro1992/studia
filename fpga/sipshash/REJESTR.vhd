LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
use work.siphash_package.all;

ENTITY REJESTR IS 
	generic (c : integer := 2);
	PORT(	
	CLK	:IN STD_LOGIC;
	v0_init, v1_init, v2_init, v3_init     : in  std_logic_vector(V_WIDTH-1 downto 0);
	m     :in STD_LOGIC_VECTOR(BLOCK_WIDTH-1 downto 0);
	b		:in STD_LOGIC_VECTOR(LENGTH_WIDTH-1 downto 0);
	v0_in, v1_in, v2_in, v3_in     : in  std_logic_vector(V_WIDTH-1 downto 0);
	
	hash   : out  std_logic_vector(HASH_WIDTH-1 downto 0);
	v0, v1, v2, v3     :  out  std_logic_vector(V_WIDTH-1 downto 0)
	
	);
END ENTITY;

ARCHITECTURE rtl OF REJESTR IS
	
	signal block_counter : unsigned(COUNT_WIDTH-1 downto 0);
   signal current_count : unsigned(COUNT_WIDTH-1 downto 0);

   signal this_m, last_m : std_logic_vector(BLOCK_WIDTH-1 downto 0);
	signal total_bytes : std_logic_vector(LENGTH_WIDTH-1 downto 0);

	
BEGIN
	
	PROCESS(m, v0_in, v1_in, v2_in, v3_in )
		variable v0, v1, v2, v3 : unsigned(V_WIDTH-1 downto 0);
		variable m : unsigned(BLOCK_WIDTH-1 downto 0);
	BEGIN
		
	END PROCESS;
	
END ARCHITECTURE;