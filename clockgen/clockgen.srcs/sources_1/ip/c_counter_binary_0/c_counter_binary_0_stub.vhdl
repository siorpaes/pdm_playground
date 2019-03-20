-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
-- Date        : Wed Mar 13 12:57:13 2019
-- Host        : AGRCWD8123 running 64-bit Service Pack 1  (build 7601)
-- Command     : write_vhdl -force -mode synth_stub {c:/Users/david
--               siorpaes/Desktop/clockgen/clockgen.srcs/sources_1/ip/c_counter_binary_0/c_counter_binary_0_stub.vhdl}
-- Design      : c_counter_binary_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a35tcpg236-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity c_counter_binary_0 is
  Port ( 
    CLK : in STD_LOGIC;
    Q : out STD_LOGIC_VECTOR ( 15 downto 0 )
  );

end c_counter_binary_0;

architecture stub of c_counter_binary_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "CLK,Q[15:0]";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "c_counter_binary_v12_0_12,Vivado 2018.2";
begin
end;
