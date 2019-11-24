LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY key_compression IS PORT
(
A :IN STD_LOGIC_VECTOR(55 DOWNTO 0);
Y :OUT STD_LOGIC_VECTOR(47 DOWNTO 0)
);
END key_compression;
ARCHITECTURE ARCH_key_compression OF key_compression IS
BEGIN
Y(47)<=A(42);
Y(46)<=A(39);
Y(45)<=A(45);
Y(44)<=A(32);
Y(43)<=A(55);
Y(42)<=A(51);
Y(41)<=A(53);
Y(40)<=A(28);
Y(39)<=A(41);
Y(38)<=A(50);
Y(37)<=A(35);
Y(36)<=A(46);
Y(35)<=A(33);
Y(34)<=A(37);
Y(33)<=A(44);
Y(32)<=A(52);
Y(31)<=A(30);
Y(30)<=A(48);
Y(29)<=A(40);
Y(28)<=A(49);
Y(27)<=A(29);
Y(26)<=A(36);
Y(25)<=A(43);
Y(24)<=A(54);
Y(23)<=A(15);
Y(22)<=A(4);
Y(21)<=A(25);
Y(20)<=A(19);
Y(19)<=A(9);
Y(18)<=A(1);
Y(17)<=A(26);
Y(16)<=A(16);
Y(15)<=A(5);
Y(14)<=A(11);
Y(13)<=A(23);
Y(12)<=A(8);
Y(11)<=A(12);
Y(10)<=A(7);
Y(9)<=A(17);
Y(8)<=A(0);
Y(7)<=A(22);
Y(6)<=A(3);
Y(5)<=A(10);
Y(4)<=A(14);
Y(3)<=A(6);
Y(2)<=A(20);
Y(1)<=A(27);
Y(0)<=A(24);

END ARCHITECTURE;