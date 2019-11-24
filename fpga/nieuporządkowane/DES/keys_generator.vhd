LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY keys_generator IS PORT
(
A :IN STD_LOGIC_VECTOR(63 DOWNTO 0);--klucz początkowy
Y :OUT STD_LOGIC_VECTOR(767 DOWNTO 0) --wszystkie podklucze dla rund
);
END keys_generator;

ARCHITECTURE ARCH_keys_generator OF keys_generator IS
--variables
signal key_after_PC_1 :STD_LOGIC_VECTOR(55 DOWNTO 0);

signal TEMP1, TEMP3, TEMP5, TEMP7, TEMP9, TEMP11, TEMP13, TEMP15, TEMP17, TEMP19, TEMP21, TEMP23, TEMP25, TEMP27, TEMP29, TEMP31: STD_LOGIC_VECTOR(55 DOWNTO 0);

signal TEMP2, TEMP4, TEMP6, TEMP8, TEMP10, TEMP12, TEMP14, TEMP16, TEMP18, TEMP20, TEMP22, TEMP24, TEMP26, TEMP28, TEMP30, TEMP32: STD_LOGIC_VECTOR(47 DOWNTO 0);

BEGIN
--PC_1
		PC1:entity work.PC_1 port map(A,key_after_PC_1);
-- round 0
		round_0_shift: entity work.keys_halves_shift port map(key_after_PC_1,B"0000",TEMP1);
		round_0_compression: entity work.key_compression port map(TEMP1,TEMP2);
		Y(767-0*48 DOWNTO 768-(0+1)*48)<=TEMP2;
-- round 1
		round_1_shift: entity work.keys_halves_shift port map(TEMP1,B"0001",TEMP3);
		round_1_compression: entity work.key_compression port map(TEMP3,TEMP4);
		Y(767-1*48 DOWNTO 768-(1+1)*48)<=TEMP4;
-- round 2
		round_2_shift: entity work.keys_halves_shift port map(TEMP3,B"0010",TEMP5);
		round_2_compression: entity work.key_compression port map(TEMP5,TEMP6);
		Y(767-2*48 DOWNTO 768-(2+1)*48)<=TEMP6;
-- round 3
		round_3_shift: entity work.keys_halves_shift port map(TEMP5,B"0011",TEMP7);
		round_3_compression: entity work.key_compression port map(TEMP7,TEMP8);
		Y(767-3*48 DOWNTO 768-(3+1)*48)<=TEMP8;
-- round 4
		round_4_shift: entity work.keys_halves_shift port map(TEMP7,B"0100",TEMP9);
		round_4_compression: entity work.key_compression port map(TEMP9,TEMP10);
		Y(767-4*48 DOWNTO 768-(4+1)*48)<=TEMP10;
-- round 5
		round_5_shift: entity work.keys_halves_shift port map(TEMP9,B"0101",TEMP11);
		round_5_compression: entity work.key_compression port map(TEMP11,TEMP12);
		Y(767-5*48 DOWNTO 768-(5+1)*48)<=TEMP12;
-- round 6
		round_6_shift: entity work.keys_halves_shift port map(TEMP11,B"0110",TEMP13);
		round_6_compression: entity work.key_compression port map(TEMP13,TEMP14);
		Y(767-6*48 DOWNTO 768-(6+1)*48)<=TEMP14;
-- round 7
		round_7_shift: entity work.keys_halves_shift port map(TEMP13,B"0111",TEMP15);
		round_7_compression: entity work.key_compression port map(TEMP15,TEMP16);
		Y(767-7*48 DOWNTO 768-(7+1)*48)<=TEMP16;
-- round 8
		round_8_shift: entity work.keys_halves_shift port map(TEMP15,B"1000",TEMP17);
		round_8_compression: entity work.key_compression port map(TEMP17,TEMP18);
		Y(767-8*48 DOWNTO 768-(8+1)*48)<=TEMP18;
-- round 9
		round_9_shift: entity work.keys_halves_shift port map(TEMP17,B"1001",TEMP19);
		round_9_compression: entity work.key_compression port map(TEMP19,TEMP20);
		Y(767-9*48 DOWNTO 768-(9+1)*48)<=TEMP20;
-- round 10
		round_10_shift: entity work.keys_halves_shift port map(TEMP19,B"1010",TEMP21);
		round_10_compression: entity work.key_compression port map(TEMP21,TEMP22);
		Y(767-10*48 DOWNTO 768-(10+1)*48)<=TEMP22;
-- round 11
		round_11_shift: entity work.keys_halves_shift port map(TEMP21,B"1011",TEMP23);
		round_11_compression: entity work.key_compression port map(TEMP23,TEMP24);
		Y(767-11*48 DOWNTO 768-(11+1)*48)<=TEMP24;
-- round 12
		round_12_shift: entity work.keys_halves_shift port map(TEMP23,B"1100",TEMP25);
		round_12_compression: entity work.key_compression port map(TEMP25,TEMP26);
		Y(767-12*48 DOWNTO 768-(12+1)*48)<=TEMP26;
-- round 13
		round_13_shift: entity work.keys_halves_shift port map(TEMP25,B"1101",TEMP27);
		round_13_compression: entity work.key_compression port map(TEMP27,TEMP28);
		Y(767-13*48 DOWNTO 768-(13+1)*48)<=TEMP28;
-- round 14
		round_14_shift: entity work.keys_halves_shift port map(TEMP27,B"1110",TEMP29);
		round_14_compression: entity work.key_compression port map(TEMP29,TEMP30);
		Y(767-14*48 DOWNTO 768-(14+1)*48)<=TEMP30;
-- round 15
		round_15_shift: entity work.keys_halves_shift port map(TEMP29,B"1111",TEMP31);
		round_15_compression: entity work.key_compression port map(TEMP31,TEMP32);
		Y(767-15*48 DOWNTO 768-(15+1)*48)<=TEMP32;
		
END ARCHITECTURE;