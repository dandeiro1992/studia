LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY keys_compression IS PORT
(
A :IN STD_LOGIC_VECTOR(27 DOWNTO 0);--analizowany podciag
B :IN integer range 0 to 15;			--numer cyklu
Y :OUT STD_LOGIC_VECTOR(27 DOWNTO 0) --wynik zrobienia shifta
);
END keys_compression;
ARCHITECTURE ARCH_keys_compression OF keys_compression IS
signal shift_number : STD_LOGIC_VECTOR(0 TO 15):=B"0011111101111110";
BEGIN
PROCESS(B,A)
BEGIN
	if (shift_number(B)='0') then
		Y<=A(26 DOWNTO 0) & A(27);
	else
		Y<=A(25 DOWNTO 0) & A(27) & A(26);
	end if;
END PROCESS;
END ARCHITECTURE;
