LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE IEEE.NUMERIC_STD.ALL;
ENTITY des IS PORT
(
DATA_IN :IN STD_LOGIC_VECTOR(63 DOWNTO 0);
KEY		:IN STD_LOGIC_VECTOR(63 DOWNTO 0);
DATA_OUT :OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
);
END des;
ARCHITECTURE ARCH_des OF des IS
signal data_after_initial_permutation :STD_LOGIC_VECTOR(63 DOWNTO 0);
signal key_done :STD_LOGIC_VECTOR(767 DOWNTO 0);
signal ext_per_1 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_1 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_1 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_1 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal finite:STD_LOGIC_VECTOR(63 DOWNTO 0);
signal R1:STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R2 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R3 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R4 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R5 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R6 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R7 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R8 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R9 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R10 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R11 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R12 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R13 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R14 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R15 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R16 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal R17 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L1 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L2 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L3 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L4 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L5 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L6 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L7 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L8 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L9 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L10 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L11 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L12 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L13 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L14 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L15 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L16 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal L17 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_2 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_2 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_2 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_2 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_3 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_3 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_3 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_3 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_4 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_4 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_4 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_4 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_5 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_5 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_5 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_5 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_6 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_6 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_6 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_6 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_7 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_7 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_7 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_7 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_8 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_8 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_8 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_8 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_9 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_9 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_9 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_9 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_10 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_10 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_10 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_10 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_11 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_11 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_11 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_11 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_12 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_12 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_12 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_12 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_13 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_13 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_13 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_13 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_14 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_14 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_14 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_14 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_15 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_15 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_15 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_15 :STD_LOGIC_VECTOR(31 DOWNTO 0);

signal ext_per_16 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_xor_16 :STD_LOGIC_VECTOR(47 DOWNTO 0);
signal after_sbox_16 :STD_LOGIC_VECTOR(31 DOWNTO 0);
signal after_p_block_16 :STD_LOGIC_VECTOR(31 DOWNTO 0);

BEGIN
initial_permutation: entity work.initial_permutation port map(DATA_IN,data_after_initial_permutation);
key_making: entity work.keys_generator port map(KEY,key_done);

L1<=data_after_initial_permutation(63 downto 32);
R1<=data_after_initial_permutation(31 downto 0);
--1 runda
first_round_1: entity work.extended_permutation port map(R1,ext_per_1);
first_round_2: entity work.key_xor port map(ext_per_1,key_done(767 downto 720),after_xor_1);
first_round_3: entity work.sbox port map(after_xor_1,after_sbox_1);
first_round_4: entity work.p_block_permutation port map(after_sbox_1,after_p_block_1);
first_round_5: entity work.xor_des port map(L1,after_p_block_1,R2);
L2<=R1;
--2 runda
second_round_1: entity work.extended_permutation port map(R2,ext_per_2);
second_round_2: entity work.key_xor port map(ext_per_2,key_done(719 downto 672),after_xor_2);
second_round_3: entity work.sbox port map(after_xor_2,after_sbox_2);
second_round_4: entity work.p_block_permutation port map(after_sbox_2,after_p_block_2);
second_round_5: entity work.xor_des port map(L2,after_p_block_2,R3);
L3<=R2;
--3 runda
third_round_1: entity work.extended_permutation port map(R3,ext_per_3);
third_round_2: entity work.key_xor port map(ext_per_3,key_done(671 downto 624),after_xor_3);
third_round_3: entity work.sbox port map(after_xor_3,after_sbox_3);
third_round_4: entity work.p_block_permutation port map(after_sbox_3,after_p_block_3);
third_round_5: entity work.xor_des port map(L3,after_p_block_3,R4);
L4<=R3;
--4 runda
four_round_1: entity work.extended_permutation port map(R4,ext_per_4);
four_round_2: entity work.key_xor port map(ext_per_4,key_done(623 downto 576),after_xor_4);
four_round_3: entity work.sbox port map(after_xor_4,after_sbox_4);
four_round_4: entity work.p_block_permutation port map(after_sbox_4,after_p_block_4);
four_round_5: entity work.xor_des port map(L4,after_p_block_4,R5);
L5<=R4;
--5 runda
five_round_1: entity work.extended_permutation port map(R5,ext_per_5);
five_round_2: entity work.key_xor port map(ext_per_5,key_done(575 downto 528),after_xor_5);
five_round_3: entity work.sbox port map(after_xor_5,after_sbox_5);
five_round_4: entity work.p_block_permutation port map(after_sbox_5,after_p_block_5);
five_round_5: entity work.xor_des port map(L5,after_p_block_5,R6);
L6<=R5;
--6 runda
six_round_1: entity work.extended_permutation port map(R6,ext_per_6);
six_round_2: entity work.key_xor port map(ext_per_6,key_done(527 downto 480),after_xor_6);
six_round_3: entity work.sbox port map(after_xor_6,after_sbox_6);
six_round_4: entity work.p_block_permutation port map(after_sbox_6,after_p_block_6);
six_round_5: entity work.xor_des port map(L6,after_p_block_6,R7);
L7<=R6;
--7 runda
seven_round_1: entity work.extended_permutation port map(R7,ext_per_7);
seven_round_2: entity work.key_xor port map(ext_per_7,key_done(479 downto 432),after_xor_7);
seven_round_3: entity work.sbox port map(after_xor_7,after_sbox_7);
seven_round_4: entity work.p_block_permutation port map(after_sbox_7,after_p_block_7);
seven_round_5: entity work.xor_des port map(L7,after_p_block_7,R8);
L8<=R7;
--8 runda
eight_round_1: entity work.extended_permutation port map(R8,ext_per_8);
eight_round_2: entity work.key_xor port map(ext_per_8,key_done(431 downto 384),after_xor_8);
eight_round_3: entity work.sbox port map(after_xor_8,after_sbox_8);
eight_round_4: entity work.p_block_permutation port map(after_sbox_8,after_p_block_8);
eight_round_5: entity work.xor_des port map(L8,after_p_block_8,R9);
L9<=R8;
--9 runda
nine_round_1: entity work.extended_permutation port map(R9,ext_per_9);
nine_round_2: entity work.key_xor port map(ext_per_9,key_done(383 downto 336),after_xor_9);
nine_round_3: entity work.sbox port map(after_xor_9,after_sbox_9);
nine_round_4: entity work.p_block_permutation port map(after_sbox_9,after_p_block_9);
nine_round_5: entity work.xor_des port map(L9,after_p_block_9,R10);
L10<=R9;
--10 runda
ten_round_1: entity work.extended_permutation port map(R10,ext_per_10);
ten_round_2: entity work.key_xor port map(ext_per_10,key_done(335 downto 288),after_xor_10);
ten_round_3: entity work.sbox port map(after_xor_10,after_sbox_10);
ten_round_4: entity work.p_block_permutation port map(after_sbox_10,after_p_block_10);
ten_round_5: entity work.xor_des port map(L10,after_p_block_10,R11);
L11<=R10;
--11 runda
eleven_round_1: entity work.extended_permutation port map(R11,ext_per_11);
eleven_round_2: entity work.key_xor port map(ext_per_11,key_done(287 downto 240),after_xor_11);
eleven_round_3: entity work.sbox port map(after_xor_11,after_sbox_11);
eleven_round_4: entity work.p_block_permutation port map(after_sbox_11,after_p_block_11);
eleven_round_5: entity work.xor_des port map(L11,after_p_block_11,R12);
L12<=R11;
--12 runda
twelve_round_1: entity work.extended_permutation port map(R12,ext_per_12);
twelve_round_2: entity work.key_xor port map(ext_per_12,key_done(239 downto 192),after_xor_12);
twelve_round_3: entity work.sbox port map(after_xor_12,after_sbox_12);
twelve_round_4: entity work.p_block_permutation port map(after_sbox_12,after_p_block_12);
twelve_round_5: entity work.xor_des port map(L12,after_p_block_12,R13);
L13<=R12;
--13 runda
thirteen_round_1: entity work.extended_permutation port map(R13,ext_per_13);
thirteen_round_2: entity work.key_xor port map(ext_per_13,key_done(191 downto 144),after_xor_13);
thirteen_round_3: entity work.sbox port map(after_xor_13,after_sbox_13);
thirteen_round_4: entity work.p_block_permutation port map(after_sbox_13,after_p_block_13);
thirteen_round_5: entity work.xor_des port map(L13,after_p_block_13,R14);
L14<=R13;
--14 runda
fourteen_round_1: entity work.extended_permutation port map(R14,ext_per_14);
fourteen_round_2: entity work.key_xor port map(ext_per_14,key_done(143 downto 96),after_xor_14);
fourteen_round_3: entity work.sbox port map(after_xor_14,after_sbox_14);
fourteen_round_4: entity work.p_block_permutation port map(after_sbox_14,after_p_block_14);
fourteen_round_5: entity work.xor_des port map(L14,after_p_block_14,R15);
L15<=R14;
--15 runda
fifteen_round_1: entity work.extended_permutation port map(R15,ext_per_15);
fifteen_round_2: entity work.key_xor port map(ext_per_15,key_done(95 downto 48),after_xor_15);
fifteen_round_3: entity work.sbox port map(after_xor_15,after_sbox_15);
fifteen_round_4: entity work.p_block_permutation port map(after_sbox_15,after_p_block_15);
fifteen_round_5: entity work.xor_des port map(L15,after_p_block_15,R16);
L16<=R15;
--16 runda
sixteen_round_1: entity work.extended_permutation port map(R16,ext_per_16);
sixteen_round_2: entity work.key_xor port map(ext_per_16,key_done(47 downto 0),after_xor_16);
sixteen_round_3: entity work.sbox port map(after_xor_16,after_sbox_16);
sixteen_round_4: entity work.p_block_permutation port map(after_sbox_16,after_p_block_16);
sixteen_round_5: entity work.xor_des port map(L16,after_p_block_16,R17);
L17<=R16;
finite<=R17&L17;
final: entity work.final_permutation port map(finite,DATA_OUT);


END ARCHITECTURE;