LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;

ENTITY COMPARATOR IS PORT(
DES_OUT :IN STD_LOGIC_VECTOR(63 DOWNTO 0);
CIPHERTEXT :IN STD_LOGIC_VECTOR(63 DOWNTO 0);
KEY :IN STD_LOGIC_VECTOR(55 DOWNTO 0);
KEY_OUT :OUT STD_LOGIC_VECTOR(55 DOWNTO 0):=X"00000000000000";
COMPARISON_RESULT :OUT STD_LOGIC:='0'
);
END COMPARATOR;

ARCHITECTURE ARCH_COMPARATOR OF COMPARATOR IS

BEGIN
KEY_OUT<=KEY;

COMPARISON_RESULT<= '1' WHEN DES_OUT(63 DOWNTO 0)=CIPHERTEXT(63 DOWNTO 0)
										ELSE '0';
END ARCHITECTURE;