library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parser is
    Port ( 
	        clk_read : in  STD_LOGIC;
           clk_parse : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           data_valid : in  STD_LOGIC;
			  data_in : in STD_LOGIC_VECTOR(7 downto 0);
           start_packet : in  STD_LOGIC;
           end_packet : in  STD_LOGIC;
			  
			  debug_output: out STD_LOGIC_VECTOR (127 downto 0)
			  
			);
end parser;

architecture Behavioral of parser is

begin


end Behavioral;

