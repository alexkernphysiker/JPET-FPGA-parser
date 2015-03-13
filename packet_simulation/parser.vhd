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
reading:process(clk_read)
variable packet_started: boolean:=false;
variable queue_started:boolean:=false;
variable queue_counter:integer:=0;
variable subqueue_started:boolean:=false;
variable subqueue_counter:integer:=0;
begin
	if(rising_edge(clk_read))then
		if(packet_started)then
			case end_packet is
				when '1' => packet_started:=false;
				when others => packet_started:=true;
			end case;
		else
			case start_packet is
				when '1' => packet_started:=true;
				when others =>packet_started:=true;
			end case;
		end if;
		if(packet_started)then
		end if;
	end if;
end process reading;
end Behavioral;

