----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:36:01 01/09/2015 
-- Design Name: 
-- Module Name:    packet_simulation - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use std.textio.all;
use ieee.std_logic_textio.all;
-- use work.io_utils.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

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
variable N : STD_LOGIC_VECTOR (7 downto 0);
variable goodnumber: boolean;
variable counter: integer;
begin
if rising_edge(clock)then
	if not endfile(source)then
		--counter:=counter+1;
		hread(L,N,goodnumber);
		if not goodnumber then
			readline(source,L);
			hread(L,N,goodnumber);
			--counter:=0;
			data_valid<='0';
		else
			--if(counter>1)then
				data_valid<='1';
				data_out<=N;
			--else
			--	data_valid<='0';
			--end if;
		end if;
	else
		data_valid<='0';
	end if;
end if;
end process reading;
end Behavioral;

