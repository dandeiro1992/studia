LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY xor_des IS PORT
(
A :IN STD_LOGIC_VECTOR(31 DOWNTO 0);
B :IN STD_LOGIC_VECTOR(31 DOWNTO 0);
Y :OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
);
END xor_des;

ARCHITECTURE ARCH_xor_des OF xor_des IS

BEGIN
Y(31)<=A(31) xor B(31);
Y(30)<=A(30) xor B(30);
Y(29)<=A(29) xor B(29);
Y(28)<=A(28) xor B(28);
Y(27)<=A(27) xor B(27);
Y(26)<=A(26) xor B(26);
Y(25)<=A(25) xor B(25);
Y(24)<=A(24) xor B(24);
Y(23)<=A(23) xor B(23);
Y(22)<=A(22) xor B(22);
Y(21)<=A(21) xor B(21);
Y(20)<=A(20) xor B(20);
Y(19)<=A(19) xor B(19);
Y(18)<=A(18) xor B(18);
Y(17)<=A(17) xor B(17);
Y(16)<=A(16) xor B(16);
Y(15)<=A(15) xor B(15);
Y(14)<=A(14) xor B(14);
Y(13)<=A(13) xor B(13);
Y(12)<=A(12) xor B(12);
Y(11)<=A(11) xor B(11);
Y(10)<=A(10) xor B(10);
Y(9)<=A(9) xor B(9);
Y(8)<=A(8) xor B(8);
Y(7)<=A(7) xor B(7);
Y(6)<=A(6) xor B(6);
Y(5)<=A(5) xor B(5);
Y(4)<=A(4) xor B(4);
Y(3)<=A(3) xor B(3);
Y(2)<=A(2) xor B(2);
Y(1)<=A(1) xor B(1);
Y(0)<=A(0) xor B(0);
END ARCHITECTURE;