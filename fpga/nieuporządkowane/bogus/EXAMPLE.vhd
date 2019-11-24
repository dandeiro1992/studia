----------------------------------
-- Łukasz DZIEŁ (883533374)     --
-- FPGACOMMEXAMPLE-v2           --
-- 01.2016                      --
-- 1.0                          --
----------------------------------

LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY EXAMPLE IS PORT
(	
	CLK	:IN STD_LOGIC;
	INIT	:IN STD_LOGIC;
	RD   	:IN STD_LOGIC;
	WR		:IN STD_LOGIC;
	ADDR	:IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	DIN	:IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	DOUT	:OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
);
END ENTITY;

ARCHITECTURE EXAMPLE_ARCH OF EXAMPLE IS
	
	TYPE MEMORY_BLOCK IS ARRAY (0 TO 15) OF STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL MEM : MEMORY_BLOCK;
	
	SIGNAL PLAINTEXT :STD_LOGIC_VECTOR(63 DOWNTO 0):=X"0000000000000000";
	SIGNAL CIPHERTEXT :STD_LOGIC_VECTOR(63 DOWNTO 0):=X"0000000000000000";
	SIGNAL BEGIN_NUMBER :STD_LOGIC_VECTOR(63 DOWNTO 0):=X"0000000000000000";
	SIGNAL KEY		: STD_LOGIC_VECTOR(55 DOWNTO 0):=X"00000000000000";
	SIGNAL END_NUMBER :STD_LOGIC_VECTOR(63 DOWNTO 0):=X"0000100000000000";
	SIGNAL RESULT		: STD_LOGIC_VECTOR(63 DOWNTO 0):=X"0000000000000000";
	
BEGIN
	
	PROCESS(CLK)
	BEGIN
		IF (CLK'EVENT AND CLK = '1') THEN
			IF (WR = '1') THEN
				MEM(conv_integer(ADDR)) <= DIN;
			else 
				PLAINTEXT<=MEM(conv_integer(X"00000000")) & MEM(conv_integer(X"00000001"));
				CIPHERTEXT<=MEM(conv_integer(X"00000002")) & MEM(conv_integer(X"00000003"));
				BEGIN_NUMBER<=MEM(conv_integer(X"00000004")) & MEM(conv_integer(X"00000005"));
				END_NUMBER<=MEM(conv_integer(X"00000006")) & MEM(conv_integer(X"00000007"));
				MEM(conv_integer(X"00000008")) <= RESULT(55 downto 28) & b"0000";
				MEM(conv_integer(X"00000009")) <= RESULT(27 downto 0) & b"0000";
			END IF;         
			
		END IF;
	END PROCESS;
	
	PROCESS(CLK)
	BEGIN
		IF (CLK'EVENT AND CLK = '1') THEN
			IF(RD = '1') THEN
				DOUT <= MEM(conv_integer(ADDR));
			ELSE
				DOUT <= (others => 'Z');
			END IF;
		END IF;
	END PROCESS;
	KEY <=CIPHERTEXT(63 DOWNTO 8);
	DES: entity work.des port map(PLAINTEXT,KEY,RESULT);
	--done: entity work.DONE port map(CLK,BEGIN_NUMBER,CIPHERTEXT,END_NUMBER,PLAINTEXT,RESULT);
	

	
END ARCHITECTURE;