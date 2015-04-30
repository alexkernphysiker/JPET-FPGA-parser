library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity TDC_parser is
	port(
		new_data:in std_logic;
		dataWORD: in std_logic_vector(31 downto 0);
		eventID: in std_logic_vector(31 downto 0);
		triggerID: in std_logic_vector(31 downto 0);
		channel_offset: in std_logic_vector(31 downto 0)
	);
end TDC_parser;

architecture Behavioral of TDC_parser is

begin


end Behavioral;
