This README describes the other files contained within the scenario folder.

The configuration file (simulation_config.txt) describes the simulation used to generate the data within this folder. 
Values with a -1 are not useful for defining this simulation, but may be used for others. 
Generally locations are given as x, y, z relative to the center of the simulation 
and headings are in radians where 0 means in the positive x direction and pi/2 would be in the positive y direction.
Units are in seconds, meters, meters per second, or hertz.

The configuration file is formated thusly: 



Remaining files, which begin with "ULDL_Channel_Response", are the traces of the channel response between a given eNb and UE (this pair is defined in the title of each trace file). These files are obtained by ...(description of quadriga process, this should include whatever settings you need to recreate them in quadriga)





UE Antennas: dipole 
Antenna Type: dipole 
Scenario: FB_UMa_NLOS 



