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
-- CREATED		"Mon Jun 11 17:20:52 2018"

LIBRARY ieee;
USE ieee.std_logic_1164.all; 

LIBRARY work;

ENTITY schemat IS 
	PORT
	(
		CLK :  IN  STD_LOGIC;
		DATA_IN :  IN  STD_LOGIC_VECTOR(63 DOWNTO 0);
		DATA_OUT :  OUT  STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END schemat;

ARCHITECTURE bdf_type OF schemat IS 

COMPONENT cezar
	PORT(DATA_IN : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
		 DATA_OUT : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END COMPONENT;

COMPONENT comparator
	PORT(CLK : IN STD_LOGIC;
		 DATA_IN_1 : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
		 DATA_IN_2 : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
		 DATA_IN_3 : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
		 DATA_OUT : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END COMPONENT;

SIGNAL	SYNTHESIZED_WIRE_0 :  STD_LOGIC_VECTOR(63 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_1 :  STD_LOGIC_VECTOR(63 DOWNTO 0);
SIGNAL	SYNTHESIZED_WIRE_2 :  STD_LOGIC_VECTOR(63 DOWNTO 0);


BEGIN 



b2v_inst : cezar
PORT MAP(DATA_IN => DATA_IN,
		 DATA_OUT => SYNTHESIZED_WIRE_0);


b2v_inst1 : cezar
PORT MAP(DATA_IN => DATA_IN,
		 DATA_OUT => SYNTHESIZED_WIRE_1);


b2v_inst2 : cezar
PORT MAP(DATA_IN => DATA_IN,
		 DATA_OUT => SYNTHESIZED_WIRE_2);


b2v_inst3 : comparator
PORT MAP(CLK => CLK,
		 DATA_IN_1 => SYNTHESIZED_WIRE_0,
		 DATA_IN_2 => SYNTHESIZED_WIRE_1,
		 DATA_IN_3 => SYNTHESIZED_WIRE_2,
		 DATA_OUT => DATA_OUT);


END bdf_type;