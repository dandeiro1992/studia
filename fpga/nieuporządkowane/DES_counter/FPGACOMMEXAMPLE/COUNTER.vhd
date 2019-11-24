LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY COUNTER IS PORT(
BEGIN_NUMBER :IN STD_LOGIC_VECTOR(63 DOWNTO 0);
END_NUMBER :IN STD_LOGIC_VECTOR(63 DOWNTO 0);
COMPARISON_RESULT :IN STD_LOGIC;
CLK :IN STD_LOGIC;
START: OUT STD_LOGIC;
NUMBER_OUT : OUT STD_LOGIC_VECTOR(55 DOWNTO 0):=X"00000000000000"
);
END COUNTER;

ARCHITECTURE ARCH_COUNTER OF COUNTER IS

SIGNAL PAUSE:STD_LOGIC:='0';
SIGNAL SET:STD_LOGIC:='0';
SIGNAL TMP_1:STD_LOGIC:='0';
SIGNAL TMP_2:STD_LOGIC:='0';
SIGNAL TMP_3:STD_LOGIC:='0';
SIGNAL ATTACHED:STD_LOGIC:='0';
SIGNAL FLAGS: STD_LOGIC_VECTOR(6 DOWNTO 0):=b"0000000";
SIGNAL COUNTER: STD_LOGIC_VECTOR(55 DOWNTO 0):=X"00000000000000";
BEGIN

PROCESS(CLK)
	BEGIN
		IF(CLK'EVENT AND CLK='1') THEN
			IF((FLAGS(2)='1' AND ATTACHED='0') or FLAGS(4)='1') THEN
				COUNTER <= BEGIN_NUMBER(63 DOWNTO 8);
				ATTACHED <='1';
				NUMBER_OUT<=COUNTER;
			ELSIF (PAUSE='0' AND (NOT(FLAGS(2)='1' AND ATTACHED='0'))) THEN
				COUNTER<=std_logic_vector(unsigned(COUNTER)+1);
				NUMBER_OUT<=COUNTER;
			ELSIF (COMPARISON_RESULT='1') THEN
				NUMBER_OUT<=COUNTER;
			ELSE
				NUMBER_OUT<=COUNTER;
			END IF;
		END IF;
END PROCESS;

START<=FLAGS(2);
TMP_1<='1' WHEN COUNTER=END_NUMBER(63 DOWNTO 8) ELSE '0';
TMP_2<= '1' WHEN FLAGS(3)='1' ELSE '0';
tmp_3<=COMPARISON_RESULT;
PAUSE<='1' WHEN (FLAGS(3)='1' OR FLAGS(4)='1' OR FLAGS(5)='1' OR FLAGS(1)='1' OR FLAGS(0)='1') ELSE '0';
FLAGS<=END_NUMBER(5) & END_NUMBER(4) & END_NUMBER(2) & END_NUMBER(0) & TMP_2 & TMP_1 & TMP_3;
END ARCHITECTURE;
