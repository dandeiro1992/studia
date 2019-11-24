LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY extended_permutation IS PORT
(
A :IN STD_LOGIC_VECTOR(31 DOWNTO 0);
Y :OUT STD_LOGIC_VECTOR(47 DOWNTO 0)
);
END extended_permutation;

ARCHITECTURE ARCH_extended_permutation OF extended_permutation IS

BEGIN
Y(47)<=A(0);
Y(46)<=A(31);
Y(45)<=A(30);
Y(44)<=A(29);
Y(43)<=A(28);
Y(42)<=A(27);
Y(41)<=A(28);
Y(40)<=A(27);
Y(39)<=A(26);
Y(38)<=A(25);
Y(37)<=A(24);
Y(36)<=A(23);
Y(35)<=A(24);
Y(34)<=A(23);
Y(33)<=A(22);
Y(32)<=A(21);
Y(31)<=A(20);
Y(30)<=A(19);
Y(29)<=A(20);
Y(28)<=A(19);
Y(27)<=A(18);
Y(26)<=A(17);
Y(25)<=A(16);
Y(24)<=A(15);
Y(23)<=A(16);
Y(22)<=A(15);
Y(21)<=A(14);
Y(20)<=A(13);
Y(19)<=A(12);
Y(18)<=A(11);
Y(17)<=A(12);
Y(16)<=A(11);
Y(15)<=A(10);
Y(14)<=A(9);
Y(13)<=A(8);
Y(12)<=A(7);
Y(11)<=A(8);
Y(10)<=A(7);
Y(9)<=A(6);
Y(8)<=A(5);
Y(7)<=A(4);
Y(6)<=A(3);
Y(5)<=A(4);
Y(4)<=A(3);
Y(3)<=A(2);
Y(2)<=A(1);
Y(1)<=A(0);
Y(0)<=A(31);
END ARCHITECTURE;