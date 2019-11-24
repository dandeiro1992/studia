-- Copyright (C) 2016  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel MegaCore Function License Agreement, or other 
-- applicable license agreement, including, without limitation, 
-- that your use is for the sole purpose of programming logic 
-- devices manufactured by Intel and sold by Intel or its 
-- authorized distributors.  Please refer to the applicable 
-- agreement for further details.

-- PROGRAM		"Quartus Prime"
-- VERSION		"Version 16.1.0 Build 196 10/24/2016 SJ Lite Edition"
-- CREATED		"Sat Apr 21 21:17:16 2018"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY encja IS 
	PORT
	(
		clk :  IN  STD_LOGIC;
		init :  IN  STD_LOGIC;
		ciphertext :  OUT  STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END encja;

ARCHITECTURE arch_encja OF encja IS 

COMPONENT MUC_PROJECT
	PORT(clk :  IN  STD_LOGIC;
		init :  IN  STD_LOGIC;
		plaintext :  IN  STD_LOGIC_VECTOR(63 DOWNTO 0);
		ciphertext :  OUT  STD_LOGIC_VECTOR(63 DOWNTO 0);
		lfsr_exit :  OUT  STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END COMPONENT;


SIGNAL	plain :  STD_LOGIC_VECTOR(63 DOWNTO 0):=B"0001000100010001000100010001000000010001000100010001000100010000";


BEGIN 


b2v_inst : MUC_PROJECT
PORT MAP(CLK => clk,
		 init => init,
		 plaintext=>plain,
		 ciphertext=>ciphertext);





END arch_encja;