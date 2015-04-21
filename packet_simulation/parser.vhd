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
			  is_reading: out STD_LOGIC
			);
end parser;
architecture Behavioral of parser is
type data_state is(IDLE,PACKET);
signal current_data_state,next_data_state:data_state:=IDLE;
signal isreading:std_logic:='0';

type queue_state is(IDLE,QUEUE_HEADER,QUEUE_BODY,QUEUE_TAIL);
signal current_parcer_state,next_parcer_state:queue_state:=IDLE;

type subqueue_state is(IDLE,SUBHEADER,SUBQUEUE);
signal current_subqueue_state,next_subqueue_state:subqueue_state:=IDLE;
signal eventID,triggerID:std_logic_vector(31 downto 0);

begin
reading_out_proc:process(isreading)
begin
	is_reading<=isreading;
end process reading_out_proc;
parcer_state_proc:process(clk_read,reset)
begin
	if reset='1' then
		current_data_state<=IDLE;
		current_parcer_state<=IDLE;
		current_subqueue_state<=IDLE;
	elsif rising_edge(clk_read) then
		current_data_state<=next_data_state;
		current_parcer_state<=next_parcer_state;
		current_subqueue_state<=next_subqueue_state;
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
				isreading<='1';
			else
				isreading<='0';
			end if;
		else
			isreading<='0';
		end if;
	else
		if rising_edge(clk_read) then
			isreading<='0';
		end if;
	end if;
end process data_state_proc;
parcer_queue:process(isreading)
variable queue_cnt,queue_size:integer:=0;
begin
	if rising_edge(isreading)then
		if not(current_parcer_state=IDLE)then
			queue_cnt:=queue_cnt+1;
		end if;
		case current_parcer_state is
		when IDLE => 
			next_parcer_state<=QUEUE_HEADER;
			queue_cnt:=0;
			queue_size:=0;
		when QUEUE_HEADER =>
			if queue_cnt<4 then
				for i in 7 downto 0 loop
					queue_size:=queue_size*2;
					if data_in(i)='1' then
						queue_size:=queue_size+1;
					end if;
				end loop;
			end if;
			if queue_cnt=7 then
				next_parcer_state<=QUEUE_BODY;
			end if;
		when QUEUE_BODY =>
			if queue_cnt>=(queue_size-1)then
				next_parcer_state<=QUEUE_TAIL;
				queue_cnt:=0;
			end if;
		when QUEUE_TAIL =>
			if queue_cnt=32 then
				next_parcer_state<=IDLE;
			end if;
		end case;
	end if;
end process parcer_queue;
parcer_subqueue:process(isreading)
variable subqueue_cnt,subqueue_size:integer:=0;
variable event_id,trigger_id:std_logic_vector(31 downto 0);
begin
	if(rising_edge(isreading))and(current_parcer_state=QUEUE_BODY)then
		if not(current_subqueue_state=IDLE)then
			subqueue_cnt:=subqueue_cnt+1;
		end if;
		case current_subqueue_state is
		when IDLE =>
				next_subqueue_state<=SUBHEADER;
				subqueue_cnt:=0;
				subqueue_size:=0;
		when SUBHEADER =>
			if subqueue_cnt<4 then
				for i in 7 downto 0 loop
					subqueue_size:=subqueue_size*2;
					if data_in(i)='1' then
						subqueue_size:=subqueue_size+1;
					end if;
				end loop;
			end if;
			if subqueue_cnt=4 then
				subqueue_size:=subqueue_size+4;
			end if;
			if(subqueue_cnt>=8)and(subqueue_cnt<12)then
				for i in 7 downto 0 loop
					event_id((11-subqueue_cnt)*8+i):=data_in(i);
				end loop;
			end if;
			if(subqueue_cnt>=12)and(subqueue_cnt<16)then
				for i in 7 downto 0 loop
					trigger_id((15-subqueue_cnt)*8+i):=data_in(i);
				end loop;
			end if;
			if subqueue_cnt=15 then
				next_subqueue_state<=SUBQUEUE;
				eventID<=event_id;
				triggerID<=trigger_id;
			end if;
		when SUBQUEUE =>
			if subqueue_cnt>=(subqueue_size-1)then
				next_subqueue_state<=IDLE;
				subqueue_cnt:=0;
			end if;
		end case;
	end if;
end process parcer_subqueue;
end Behavioral;
