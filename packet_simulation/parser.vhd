-- This source file was created for J-PET project in WFAIS (Jagiellonian University in Cracow)
-- License for distribution outside WFAIS UJ and J-PET project is GPL v 3
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity parser is
    Port ( 
	        clk_read : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           start_packet : in  STD_LOGIC;
           end_packet : in  STD_LOGIC;
           data_valid : in  STD_LOGIC;
			  data_in : in STD_LOGIC_VECTOR(7 downto 0);

			  eventID: out std_logic_vector(31 downto 0);
			  triggerID: out std_logic_vector(31 downto 0);
			  deviceID: out std_logic_vector(15 downto 0);
			  dataWORD: out std_logic_vector(31 downto 0);
			  out_data: out std_logic
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

type dataitem_state is (IDLE,ITEMHEADER,ITEMBODY);
signal current_item_state,next_item_state:dataitem_state:=IDLE;

begin
parcer_state_proc:process(clk_read,reset)
begin
	if reset='1' then
		current_data_state<=IDLE;
		current_parcer_state<=IDLE;
		current_subqueue_state<=IDLE;
		current_item_state<=IDLE;
	elsif rising_edge(clk_read) then
		current_data_state<=next_data_state;
		current_parcer_state<=next_parcer_state;
		current_subqueue_state<=next_subqueue_state;
		current_item_state<=next_item_state;
	end if;
end process parcer_state_proc;
packet_state_proc:process(clk_read)
begin
	if start_packet='1' then
		next_data_state<=PACKET;
	end if;
	if end_packet='1' then
		next_data_state<=IDLE;
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
			for i in 7 downto 0 loop
				queue_size:=queue_size*2;
				if data_in(i)='1' then
					queue_size:=queue_size+1;
				end if;
			end loop;
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
				for i in 7 downto 0 loop
					subqueue_size:=subqueue_size*2;
					if data_in(i)='1' then
						subqueue_size:=subqueue_size+1;
					end if;
				end loop;
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
	elsif not(current_parcer_state=QUEUE_BODY) then
		next_subqueue_state<=IDLE;
	end if;
end process parcer_subqueue;
parce_dataitems: process(isreading)
variable dataitem_cnt,data_words_number:integer:=0;
variable device_id:std_logic_vector(15 downto 0);
variable current_word:std_logic_vector(31 downto 0);
begin
	if(rising_edge(isreading))and (current_subqueue_state=SUBQUEUE)then
		if not(current_item_state=IDLE)then
			dataitem_cnt:=dataitem_cnt+1;
		end if;
		case current_item_state is
		when IDLE =>
			dataitem_cnt:=0;
			data_words_number:=0;
			for i in 7 downto 0 loop
				data_words_number:=data_words_number*2;
				if data_in(i)='1' then
					data_words_number:=data_words_number+1;
				end if;
			end loop;
			next_item_state<=ITEMHEADER;
		when ITEMHEADER =>
			if dataitem_cnt<2 then
				for i in 7 downto 0 loop
					data_words_number:=data_words_number*2;
					if data_in(i)='1' then
						data_words_number:=data_words_number+1;
					end if;
				end loop;
			else
				for i in 7 downto 0 loop
					device_id((3-dataitem_cnt)*8+i):=data_in(i);
				end loop;
				if dataitem_cnt=3 then
					deviceID<=device_id;
					next_item_state<=ITEMBODY;
				end if;
			end if;
		when ITEMBODY =>
			for i in 7 downto 0 loop
				current_word((3-(dataitem_cnt mod 4))*8+i):=data_in(i);
			end loop;
			if (dataitem_cnt mod 4)=3 then
				dataWORD<=current_word;
				out_data<='1';
			end if;
			if dataitem_cnt>=((data_words_number+1)*4)-1 then
				next_item_state<=IDLE;
			end if;
		end case;
	else 
		if falling_edge(isreading)then
			out_data<='0';
		end if;
		if not(current_subqueue_state=SUBQUEUE) then
			next_item_state<=IDLE;
		end if;
	end if;
end process parce_dataitems;
end Behavioral;
