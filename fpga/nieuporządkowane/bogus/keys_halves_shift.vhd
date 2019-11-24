LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY keys_halves_shift IS PORT
(
A :IN STD_LOGIC_VECTOR(55 DOWNTO 0);--analizowany podciag
B :IN STD_LOGIC_VECTOR(3 DOWNTO 0);			--numer cyklu
Y :OUT STD_LOGIC_VECTOR(55 DOWNTO 0) --wynik zrobienia shifta
);
END keys_halves_shift;
ARCHITECTURE ARCH_keys_halves_shift OF keys_halves_shift IS
signal shift_number : STD_LOGIC_VECTOR(0 TO 15):=B"0011111101111110";
BEGIN
Y(55 downto 28)<=A(54 DOWNTO 28) & A(55) when shift_number(to_integer(unsigned(B)))='0' else
						A(53 DOWNTO 28) & A(55) & A(54) when shift_number(to_integer(unsigned(B)))='1' else
					(others=>'0');

Y(27 downto 0)<=A(26 DOWNTO 0) & A(27) when shift_number(to_integer(unsigned(B)))='0' else
						A(25 DOWNTO 0) & A(27) & A(26) when shift_number(to_integer(unsigned(B)))='1' else
						(others=>'0');

END ARCHITECTURE;

--PROCESS(B)
--BEGIN
	--if (shift_number(B)='0') then
	--	Y(55 downto 28)<=A(54 DOWNTO 28) & A(55);
	--	Y(27 downto 0)<=A(26 DOWNTO 0) & A(27);
	--else
	--	Y(55 downto 28)<=A(53 DOWNTO 28) & A(55) & A(54);
	--	Y(27 downto 0)<=A(25 DOWNTO 0) & A(27) & A(26);
	--end if;
--END PROCESS;
--END ARCHITECTURE;
