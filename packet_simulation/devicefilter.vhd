-- This source file was created for J-PET project in WFAIS (Jagiellonian University in Cracow)
-- License for distribution outside WFAIS UJ and J-PET project is GPL v 3
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity devicefilter is
	port(
		deviceID: in std_logic_vector(15 downto 0);
		in_data: in std_logic;
		clock: in std_logic;
		
		channel_offset: out std_logic_vector(15 downto 0);
		accepted: out std_logic
	);
end devicefilter;

architecture Behavioral of devicefilter is
signal accept:std_logic:='0';
signal counter:integer:=0;
begin

check_device:process(in_data,clock)
begin
	if rising_edge(in_data) then
		counter<=4;
	elsif rising_edge(clock)then
		if counter>0 then
			counter<=counter-1;
			if counter=1 then
				accept<='1';
			end if;
		end if;
	elsif falling_edge(clock) then
		accept<='0';
	end if;
end process check_device;

accept_device:process(accept)
begin
	if rising_edge(accept)then
		accepted<='1';
	elsif accept='0' then
		accepted<='0';
	end if;
end process accept_device;

calculate_channel_offset:process(accept)
begin
	if rising_edge(accept) then
		channel_offset<=deviceID;
	end if;
end process calculate_channel_offset;
end Behavioral;
