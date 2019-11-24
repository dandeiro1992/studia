LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY wszystko IS PORT
(
X :IN STD_LOGIC_VECTOR(2 DOWNTO 0);
Y :OUT STD_LOGIC
);
END ENTITY;

ARCHITECTURE arch_wszystko OF wszystko IS
--signal tmp: std_logic_vector (2 downto 0) := X;
signal m: std_logic_vector (1 downto 0);
signal n: std_logic_vector (2 downto 0);
signal a,b,c :std_logic;
signal k: std_logic_vector (1 downto 0);
signal l: std_logic_vector (1 downto 0);
BEGIN
m<= x(1) & x(0);
n<= x(2) & m;
k<= a & b;
l<= c & x(2);


suma : entity work.suma port map(m,a);
iloczyn : entity work.iloczyn port map(m,b);
suma_1: entity work.suma port map(k,c);
wynik1 : entity work.suma port map(l,Y);
END ARCHITECTURE;