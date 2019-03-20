----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/13/2019 12:09:39 PM
-- Design Name: 
-- Module Name: clkgen - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clkgen is
    Port ( clkin : in STD_LOGIC;
           clkout1 : out STD_LOGIC;
           clkout2 : out STD_LOGIC);
end clkgen;

architecture Behavioral of clkgen is

signal r_clkin        : STD_LOGIC := '0';
signal r_clkout       : STD_LOGIC := '0';
signal r_reset        : STD_LOGIC := '0';
signal r_counter      : STD_LOGIC_VECTOR (15 downto 0);
begin

CLKWIZ: entity work.clk_wiz_0
port map(
	clk_in1 => r_clkin,
	clk_out1 => r_clkout,
	reset => r_reset
);

COUNTER: entity work.c_counter_binary_0
port map(
	CLK =>  r_clkout,
	Q => r_counter
);

r_clkin <= clkin;
clkout1 <= r_clkout;
clkout2 <= r_counter(1);
r_reset <= '0';

end Behavioral;
