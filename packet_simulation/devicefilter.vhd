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
signal accept:std_logic:='0';
begin

check_device:process(new_data)
begin
	if rising_edge(new_data) then
		accept<='1';
	elsif falling_edge(new_data) then
		accept<='0';
	end if;
end process check_device;

accept_device:process(accept)
begin
	if rising_edge(accept)then
		accepted<='1';
	elsif falling_edge(accept) then
		accepted<='0';
	end if;
end process accept_device;

calculate_channel_offset:process(accept)
begin
	if rising_edge(accept) then
		for i in 31 downto 24 loop
			channel_offset(i)<='0';
		end loop;
		for i in 15 downto 0 loop
			channel_offset(i+8)<=deviceID(i);
		end loop;
		for i in 7 downto 0 loop
			channel_offset(i)<='0';
		end loop;
	end if;
end process calculate_channel_offset;
end Behavioral;
