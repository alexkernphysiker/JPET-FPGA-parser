library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity devicefilter is
	port(
		deviceID: in std_logic_vector(15 downto 0);
		new_data: in std_logic;
		
		channel_offset: out std_logic_vector(31 downto 0);
		accepted: out std_logic
	);
end devicefilter;

architecture Behavioral of devicefilter is

begin

end Behavioral;
