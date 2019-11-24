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

LIBRARY WORK;
USE WORK.ALL;

ENTITY FPGA IS PORT
(	
	CLK				:IN STD_LOGIC;
	RS232_TX			:OUT STD_LOGIC;
	RS232_RX			:IN STD_LOGIC); END ENTITY;


ARCHITECTURE FPGA_ARCH OF FPGA IS	
	
	SIGNAL ZERO :STD_LOGIC; 
	
	SIGNAL TEMP1 :STD_LOGIC;
	SIGNAL TEMP2 :STD_LOGIC;
	
	SIGNAL TEMP3 :STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL TEMP4 :STD_LOGIC_VECTOR(31 DOWNTO 0);
	SIGNAL TEMP5 :STD_LOGIC_VECTOR(31 DOWNTO 0);
	signal tempclk:STD_LOGIC:='0';
	
	
BEGIN
	ZERO <= '0';
	
	pllunit: ENTITY WORK.pll PORT MAP (
			inclk0		=>CLK,
			c0 			=>tempclk
		);
	
	unit00: ENTITY WORK.RS232_STANDARD_INTERFACE PORT MAP (
			CLK		=> tempclk,
			INIT		=> ZERO,
			TX			=> RS232_TX,
			RX			=> RS232_RX,
			INT_WR	=> TEMP1,
			INT_RD	=> TEMP2,
			INT_ADDR	=> TEMP3,
			INT_DIN	=> TEMP4,
			INT_DOUT	=> TEMP5);
	
	unit01: ENTITY WORK.EXAMPLE PORT MAP (
			CLK	=> tempclk,
			INIT	=> ZERO,
			RD		=> TEMP2,
			WR		=> TEMP1,
			ADDR	=> TEMP3,
			DIN	=> TEMP5,
			DOUT	=> TEMP4);
	
END ARCHITECTURE;