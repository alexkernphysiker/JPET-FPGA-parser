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
			  isreading:out std_logic
			);
end parser;
architecture Behavioral of parser is
type data_state is(IDLE,PACKET);
signal current_data_state,next_data_state:data_state:=IDLE;
type parcer_state is(IDLE,QUEUE_HEADER,SUBQUEUE_HEADER,DATAITEM);
signal current_parcer_state,next_parcer_state:parcer_state:=IDLE;
signal take_data:std_logic:='0';
begin
parcer_state_proc:process(clk_read,reset)
begin
	if reset='1' then
		current_data_state<=IDLE;
		current_parcer_state<=IDLE;
	elsif rising_edge(clk_read) then
		current_data_state<=next_data_state;
		current_parcer_state<=next_parcer_state;
	end if;
end process parcer_state_proc;
packet_state_proc:process(clk_read)
begin
	if falling_edge(clk_read) then
		if start_packet='1' then
			next_data_state<=PACKET;
		end if;
		if end_packet='1' then
			next_data_state<=IDLE;
		end if;
	end if;
end process packet_state_proc;
data_state_proc:process(clk_read)
begin
	if falling_edge(clk_read)then
		if data_valid='1' then
			if current_data_state=PACKET or start_packet='1' then
				take_data<='1';
			else
				take_data<='0';
			end if;
		else
			take_data<='0';
		end if;
	else
		if rising_edge(clk_read) then
			take_data<='0';
		end if;
	end if;
end process data_state_proc;
parcer_main:process(take_data)
begin
	if rising_edge(take_data)then
	end if;
end process parcer_main;
end Behavioral;
