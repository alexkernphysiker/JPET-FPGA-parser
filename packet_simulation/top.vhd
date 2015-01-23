--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:19:58 01/09/2015
-- Design Name:   
-- Module Name:   /media/sf_fpga/packet_simulation/top.vhd
-- Project Name:  packet_simulation
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: packet_simulation
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY top IS
END top;
 
ARCHITECTURE behavior OF top IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
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
    

   --Inputs
   signal clock : std_logic := '0';

 	--Outputs
   signal data_valid : std_logic;
   signal data_out : std_logic_vector(7 downto 0);
   signal start_packet : std_logic;
   signal end_packet : std_logic;
   signal debug_out : std_logic_vector(127 downto 0);

   -- Clock period definitions
   constant clock_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: packet_simulation PORT MAP (
          clock => clock,
          data_valid => data_valid,
          data_out => data_out,
          start_packet => start_packet,
          end_packet => end_packet,
          debug_out => debug_out
        );

   -- Clock process definitions
   clock_process :process
   begin
		clock <= '0';
		wait for clock_period/2;
		clock <= '1';
		wait for clock_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clock_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
