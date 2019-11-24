LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY segment IS

PORT
(
A0 :IN STD_LOGIC;


zegar :IN STD_LOGIC;


C0 :OUT STD_LOGIC;
C1 :OUT STD_LOGIC;
C2 :OUT STD_LOGIC;
C3 :OUT STD_LOGIC;
C4 :OUT STD_LOGIC;
C5 :OUT STD_LOGIC;
C6 :OUT STD_LOGIC;
C7 :OUT STD_LOGIC
);
END segment;

ARCHITECTURE wyswietlacz OF segment IS
signal tmp :std_logic :='0';
signal counter : integer:=0; 
BEGIN
PROCESS (zegar) --podpowiedź zegar musi być jednym z portów
--deklaracja zmiennych

BEGIN

IF(rising_edge(zegar)) THEN
-- kod do wykonania
-- A 000 i zmieniam B same 0
if(A0='1') THEN
	if (tmp='0') then
	counter<=counter+1;
	tmp<='1';
	end if;
END IF;
if(A0='0') then
tmp<='0';
end if;

CASE counter IS
when 0=>
C0<='1';
C1<='0';
C2<='1';
C3<='1';
C4<='1';
C5<='1';
C6<='1';
C7<='0';
when 1 =>
C0<='0';
C1<='0';
C2<='0';
C3<='0';
C4<='1';
C5<='0';
C6<='1';
C7<='0';
when 2 =>
C0<='1';
C1<='1';
C2<='0';
C3<='1';
C4<='1';
C5<='1';
C6<='0';
C7<='0';
when 3 =>
C0<='0';
C1<='1';
C2<='0';
C3<='1';
C4<='1';
C5<='1';
C6<='1';
C7<='0';
when 4 =>
C0<='0';
C1<='1';
C2<='1';
C3<='0';
C4<='0';
C5<='0';
C6<='1';
C7<='0';
when 5 =>
C0<='0';
C1<='1';
C2<='1';
C3<='1';
C4<='0';
C5<='1';
C6<='1';
C7<='0';
when 6 =>
C0<='1';
C1<='1';
C2<='1';
C3<='1';
C4<='0';
C5<='1';
C6<='1';
C7<='0';
when 7 =>
C0<='0';
C1<='0';
C2<='0';
C3<='1';
C4<='1';
C5<='0';
C6<='1';
C7<='0';
when 8 =>
C0<='1';
C1<='1';
C2<='1';
C3<='1';
C4<='1';
C5<='1';
C6<='1';
C7<='0';
when 9 =>
C0<='0';
C1<='1';
C2<='1';
C3<='1';
C4<='1';
C5<='1';
C6<='1';
C7<='0';
when others =>
counter<=0;
END CASE;
END IF;
END PROCESS;
END wyswietlacz;