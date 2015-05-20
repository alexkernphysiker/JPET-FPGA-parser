library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
entity TDC_parser is
	port(
		in_data:in std_logic;
		dataWORD:in std_logic_vector(31 downto 0);
		channel_offset:in std_logic_vector(15 downto 0);
	   eventID: in std_logic_vector(31 downto 0);
		triggerID: in std_logic_vector(31 downto 0);
		out_data: out std_logic;
		time_isrising:out std_logic;
		time_channel: out std_logic_vector(15 downto 0);
		time_epoch: out std_logic_vector(27 downto 0);
		time_fine: out std_logic_vector(9 downto 0);
		time_coasser:out std_logic_vector(10 downto 0)
	);
end TDC_parser;

architecture Behavioral of TDC_parser is
signal saved_channel_offset: std_logic_vector(15 downto 0);
signal saved_eventID: std_logic_vector(31 downto 0);
signal saved_triggerID: std_logic_vector(31 downto 0);
signal reset:std_logic:='0';
signal parse:std_logic:='0';
type tdc_state is(IDLE,HEADER_READ,EPOCH_READ);
signal current_tdc_state,next_tdc_state:tdc_state:=IDLE;
begin
state_change:process(reset,in_data)begin
	if rising_edge(reset)then
		current_tdc_state<=IDLE;
	elsif falling_edge(in_data)then
		current_tdc_state<=next_tdc_state;
	end if;
end process state_change;
trigger_change_check:process(in_data)begin
	if(not(saved_eventID=eventID))or
		(not(saved_triggerID=triggerID))or
		(not(saved_channel_offset=channel_offset))then
		reset<='1';
	end if;
	if(reset='1')and(current_tdc_state=IDLE)then
		saved_eventID<=eventID;
		saved_triggerID<=triggerID;
		saved_channel_offset<=channel_offset;
		reset<='0';
	end if;
	if rising_edge(in_data) then
		parse<='1';
	end if;
	if falling_edge(in_data) then
		parse<='0';
	end if;
end process trigger_change_check;
state_machine:process(parse)begin
	if rising_edge(parse) then
		case current_tdc_state is
		when IDLE => 
			if(dataWORD(31)='0')and(dataWORD(30)='0')and(dataWORD(29)='1')then
				next_tdc_state<=HEADER_READ;
			end if;
		when HEADER_READ => 
			if(dataWORD(31)='0')and(dataWORD(30)='1')and(dataWORD(29)='1')then
				next_tdc_state<=EPOCH_READ;
			end if;
		when EPOCH_READ => 
			if(dataWORD(31)='0')and(dataWORD(30)='0')and(dataWORD(29)='1')then
				next_tdc_state<=HEADER_READ;
			end if;
		end case;
		if(dataWORD(31)='0')and(dataWORD(30)='0')and(dataWORD(29)='1')then
		--TODO: decode TDC header data word
		elsif(dataWORD(31)='0')and(dataWORD(30)='1')and(dataWORD(29)='1')then
		--TODO: decode epoch data word
		elsif(dataWORD(31)='1')and(current_tdc_state=EPOCH_READ)then
		--ToDo: decode finetime data word
		end if;
	end if;
end process state_machine;
end Behavioral;
