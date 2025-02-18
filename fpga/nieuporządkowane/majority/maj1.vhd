LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY maj1 IS PORT
(
X :IN STD_LOGIC_VECTOR(2 DOWNTO 0);
Y :OUT STD_LOGIC
);

END ENTITY;
ARCHITECTURE ARCH_maj1 OF maj1 IS
BEGIN
Y <= (X(0) or X(1));
END ARCHITECTURE;