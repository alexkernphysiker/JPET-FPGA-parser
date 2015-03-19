LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
ENTITY top IS
END top;
 
ARCHITECTURE behavior OF top IS 
 
    COMPONENT packet_simulation
    PORT(
         clock : IN  std_logic;
         data_valid : OUT  std_logic;
         data_out : OUT  std_logic_vector(7 downto 0);
         start_packet : OUT  std_logic;
         end_packet : OUT  std_logic
        );
    END COMPONENT;
    component parser
	 Port ( 
	        clk_read : in  STD_LOGIC;
           clk_parse : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           start_packet : in  STD_LOGIC;
           end_packet : in  STD_LOGIC;
           data_valid : in  STD_LOGIC;
			  data_in : in STD_LOGIC_VECTOR(7 downto 0)
			);
	 end component;

   signal clock : std_logic:='0';
   signal clock_parse : std_logic:='0';
   signal reset : std_logic:='0';
   signal data_valid : std_logic:='0';
   signal start_packet : std_logic;
   signal end_packet : std_logic;
   signal data_bus : std_logic_vector(7 downto 0);

   constant clock_period : time := 10 ns;
   constant clock_parser_period : time := 10 ns;
BEGIN
 
   uut: packet_simulation PORT MAP (
          clock => clock,
          data_valid => data_valid,
          data_out => data_bus,
          start_packet => start_packet,
          end_packet => end_packet
        );
   parse:parser port map (
          clk_read => clock,
          clk_parse => clock_parse,
			 reset => reset,
          start_packet => start_packet,
          end_packet => end_packet,
          data_valid => data_valid,
          data_in => data_bus
	);

   clock_process :process
   begin
		clock <= '0';
		wait for clock_period/2;
		clock <= '1';
		wait for clock_period/2;
   end process;
	
   clock_parser_process :process
   begin
		clock_parse <= '0';
		wait for clock_parser_period/2;
		clock_parse <= '1';
		wait for clock_parser_period/2;
   end process;
 

   stim_proc: process
   begin		
      wait;
   end process;

END;
