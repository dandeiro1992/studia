LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY p_block_permutation IS PORT
(
A :IN STD_LOGIC_VECTOR(31 DOWNTO 0);
Y :OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
);
END p_block_permutation;

ARCHITECTURE ARCH_p_block_permutation OF p_block_permutation IS

BEGIN
Y(31)<=A(16);
Y(30)<=A(25);
Y(29)<=A(12);
Y(28)<=A(11);
Y(27)<=A(3);
Y(26)<=A(20);
Y(25)<=A(4);
Y(24)<=A(15);
Y(23)<=A(31);
Y(22)<=A(17);
Y(21)<=A(9);
Y(20)<=A(6);
Y(19)<=A(27);
Y(18)<=A(14);
Y(17)<=A(1);
Y(16)<=A(22);
Y(15)<=A(30);
Y(14)<=A(24);
Y(13)<=A(8);
Y(12)<=A(18);
Y(11)<=A(0);
Y(10)<=A(5);
Y(9)<=A(29);
Y(8)<=A(23);
Y(7)<=A(13);
Y(6)<=A(19);
Y(5)<=A(2);
Y(4)<=A(26);
Y(3)<=A(10);
Y(2)<=A(21);
Y(1)<=A(28);
Y(0)<=A(7);
END ARCHITECTURE;