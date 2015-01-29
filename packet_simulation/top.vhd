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
         end_packet : OUT  std_logic;
         debug_out : OUT  std_logic_vector(127 downto 0)
        );
    END COMPONENT;
    

   signal clock : std_logic := '0';

   signal data_valid : std_logic;
   signal data_out : std_logic_vector(7 downto 0);
   signal start_packet : std_logic;
   signal end_packet : std_logic;
   signal debug_out : std_logic_vector(127 downto 0);

   constant clock_period : time := 10 ns;
 
BEGIN
 
   uut: packet_simulation PORT MAP (
          clock => clock,
          data_valid => data_valid,
          data_out => data_out,
          start_packet => start_packet,
          end_packet => end_packet,
          debug_out => debug_out
        );

   clock_process :process
   begin
		clock <= '0';
		wait for clock_period/2;
		clock <= '1';
		wait for clock_period/2;
   end process;
 

   stim_proc: process
   begin		
      wait for 100 ns;	

      wait for clock_period*50;

      wait;
   end process;

END;
