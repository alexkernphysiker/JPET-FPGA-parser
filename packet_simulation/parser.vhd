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
			  isreading:out std_logic;
			  counter:out integer
			);
end parser;
architecture Behavioral of parser is
begin
reading:process(clk_read)
variable packet_started: boolean:=false;
variable current_number: integer:=0;
variable current_number_counter: integer:=0;
variable queue_counter:integer:=0;
variable queue_size:integer:=0;
begin
	counter<=queue_counter;
	if(falling_edge(clk_read))then
		if packet_started then
			if end_packet>'0' then
				packet_started:=false;
			end if;
		else
			if start_packet>'0' then
				packet_started:=true;
			end if;
		end if;
		if(packet_started)then
			if(data_valid>'0')then
				isreading<='1';
				if(queue_counter=0)then
					current_number_counter:=4;
				else
					if(queue_counter=4)then
						queue_size:=current_number;
					else
						if(queue_size>0)then
							if(queue_counter>=queue_size)then
								queue_size:=0;
								queue_counter:=0;
								current_number_counter:=4;
							end if;
						else
							if(queue_counter>=4)then
								queue_size:=0;
								queue_counter:=0;
								current_number_counter:=4;
							end if;
						end if;
					end if;
				end if;
				if(current_number_counter>0)then
					for i in 7 downto 0 loop
						current_number:=current_number*2;
						if(data_in(i)='1')then
							current_number:=current_number+1;
						end if;
					end loop;
					current_number_counter:=current_number_counter-1;
				end if;
				queue_counter:=queue_counter+1;
			else
				isreading<='0';
			end if;
		else
			isreading<='0';
		end if;
	end if;
end process reading;
end Behavioral;

