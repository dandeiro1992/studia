LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY testbench IS END ENTITY;

ARCHITECTURE ARCH_testbench OF testbench IS

COMPONENT wszystko IS PORT(
X :IN STD_LOGIC_VECTOR(2 DOWNTO 0);
Y :OUT STD_LOGIC);
END COMPONENT;

SIGNAL CLK :STD_LOGIC := '0';
SIGNAL X :STD_LOGIC_VECTOR(2 DOWNTO 0) := B"000";
SIGNAL Y :STD_LOGIC := '1';
SIGNAL CLKp :time := 40 ns;

BEGIN 
uut: wszystko PORT MAP (X,Y);

PROCESS
BEGIN
CLK <= '0'; wait for CLKp/2;
CLK <= '1'; wait for CLKp/2;
END PROCESS;

PROCESS
BEGIN
X <= B"000"; wait for CLKp;
X <= B"001"; wait for CLKp;
X <= B"010"; wait for CLKp;
X <= B"011"; wait for CLKp;
X <= B"100"; wait for CLKp;
X <= B"101"; wait for CLKp;
X <= B"110"; wait for CLKp;
X <= B"111"; wait for CLKp;
wait;
END PROCESS;

END ARCHITECTURE;