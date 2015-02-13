library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use std.textio.all;
use ieee.std_logic_textio.all;

entity packet_simulation is
    Port ( 
	        clock : in  STD_LOGIC;
			  
           data_valid : out  STD_LOGIC;
           data_out : out  STD_LOGIC_VECTOR(7 downto 0);
           start_packet : out  STD_LOGIC;
           end_packet : out  STD_LOGIC;
			  debug_out: out STD_LOGIC_VECTOR(127 downto 0)
			 );
end packet_simulation;

architecture Behavioral of packet_simulation is
begin
reading: process(clock)
file source : text is in "test_data";
variable L : line;
variable K : STD_LOGIC_VECTOR (7 downto 0);
variable N : STD_LOGIC_VECTOR (7 downto 0);
variable goodnumber: boolean;
variable started: boolean:=false;
variable inside:boolean:=false;
variable maybenext:boolean:=false;
variable wait_cnt:integer:=0;
begin
if rising_edge(clock)then
	if(wait_cnt>0)then
		data_valid<='0';
		wait_cnt:=wait_cnt-1;
	else
		hread(L,N,goodnumber);
		if not goodnumber then
			if not endfile(source)then
				readline(source,L);
				hread(L,N,goodnumber);
				case N is
					when "00000000" => maybenext:=true;
					when others => maybenext:=false;
				end case;
				hread(L,N,goodnumber);
				case N is
					when "00000000" => inside:=not maybenext;
					when others => inside:=true;
				end case;
				if not inside then
					wait_cnt:=3;
					inside:=false;
					if started then
						end_packet<='1';
					else
						started:=true;
					end if;
				end if;
			else
				if inside then
					inside:=false;
					end_packet<='1';
				end if;
			end if;
			data_valid<='0';
		else
			if not inside then
				inside:=true;
				start_packet<='1';
			end if;
			data_valid<='1';
			data_out<=N;
		end if;
	end if;
else
	if falling_edge(clock) then
		start_packet<='0';
		end_packet<='0';
	end if;
end if;
end process reading;
end Behavioral;
