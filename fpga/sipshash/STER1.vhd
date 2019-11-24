LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
use work.siphash_package.all;

ENTITY STER1 IS 
	generic (c : integer := 2);
	PORT(	
	CLK	:IN STD_LOGIC;
	INIT	:IN STD_LOGIC;
	WR		:IN STD_LOGIC;
	ADDR	:IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	DIN	:IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	v0, v1, v2, v3     : out  std_logic_vector(V_WIDTH-1 downto 0);
	m     :out STD_LOGIC_VECTOR(BLOCK_WIDTH-1 downto 0);
	b		:out STD_LOGIC_VECTOR(LENGTH_WIDTH-1 downto 0)
	);
END ENTITY;

ARCHITECTURE rtl OF STER1 IS
	
	TYPE MEMORY_BLOCK IS ARRAY (0 TO 15) OF STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL MEM : MEMORY_BLOCK;
	signal k : std_logic_vector(KEY_WIDTH-1 downto 0);
	
	signal block_counter : unsigned(COUNT_WIDTH-1 downto 0);
   signal current_count : unsigned(COUNT_WIDTH-1 downto 0);

   signal this_m, last_m : std_logic_vector(BLOCK_WIDTH-1 downto 0);
	signal total_bytes : std_logic_vector(LENGTH_WIDTH-1 downto 0);

	
BEGIN
	
	PROCESS(CLK)
	BEGIN
		IF (CLK'EVENT AND CLK = '1') THEN
			IF (WR = '1') THEN
				MEM(conv_integer(ADDR)) <= DIN;
			END IF;
		END IF;
	END PROCESS;
	
	PROCESS(CLK)
	BEGIN
		IF (CLK'EVENT AND CLK = '1') THEN
				v0 <= V0_INIT xor k(BLOCK_WIDTH-1 downto 0);
				v1 <= V1_INIT xor k(KEY_WIDTH-1 downto BLOCK_WIDTH);
				v2 <= V2_INIT xor k(BLOCK_WIDTH-1 downto 0);
				v3 <= V3_INIT xor k(KEY_WIDTH-1 downto BLOCK_WIDTH) xor this_m;
		END IF;
	END PROCESS;
	
END ARCHITECTURE;