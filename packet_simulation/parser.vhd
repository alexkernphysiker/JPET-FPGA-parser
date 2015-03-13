library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parser is
    Port ( 
	        clk_read : in  STD_LOGIC;
           clk_parse : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           start_packet : in  STD_LOGIC;
           end_packet : in  STD_LOGIC;
           data_valid : in  STD_LOGIC;
			  data_in : in STD_LOGIC_VECTOR(7 downto 0);
			  debug_output: out STD_LOGIC_VECTOR (127 downto 0)
			);
end parser;
architecture Behavioral of parser is
begin
reading:process(clk_read)
variable packet_started: boolean:=false;
begin
	if(falling_edge(clk_read))then
		debug_output(1)<=data_valid;
		debug_output(4)<=start_packet;
		debug_output(5)<=end_packet;
		if packet_started then
			debug_output(2)<='1';
			if end_packet>'0' then
				packet_started:=false;
			end if;
		else
			debug_output(2)<='0';
			if start_packet>'0' then
				packet_started:=true;
			end if;
		end if;
		if(packet_started)then
			if(data_valid>'0')then
				debug_output(3)<='1';
			else
				debug_output(3)<='0';
			end if;
		end if;
		case packet_started is
			when true => debug_output(0)<='1';
			when others => debug_output(0)<='0';
		end case;
	end if;
end process reading;
end Behavioral;

