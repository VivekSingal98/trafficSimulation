Traffic Simulator

Hello, we have tried to simulate Indian Road traffic
Make Sure you have OpenGL, GLUT installed in your machine. Specify its library and include folder in the makefile
When you are ready, Compile the code by typing make in terminal. 
Now, you are all set. run the simulation by ./simulation config-filename in terminal. 
Change the config file to specify simulation parameters. 
Vehicles shows velocity on it.
We have inclosed sample config files, their video output and terminal output. In terminal output -1 denotes place is empty and non zero number denotes vehicles id.

config.ini file format->

# Comment starts with #

# 1. Define Road Parameters

Road_Param
Road_Id = 1
Road_Length = 30              #should be an integer
Num_Lanes = 2                 #should be an integer
Lane_Width = 4                #should be an integer
Road_Signal = 0
Lane = 0                     # lane = 0 means no lane but a single wide road
END #end Road parameters with END

# 2. Define default params for all vehicle types
Default_Param
Default_MaxSpeed = 10        # Max Speed per second 
Default_Acceleration = 2     # Increase in speed per second. Should not be 0
Default_Gap = 1              # Gap that vehicle maintains in its front 
stepTime = 10                # time between two frames 
imageLength = 720            # image length in pixels
Default_LaneChangeFrequency = 0 #lane change allowed after _ seconds
END

# 3. Define params for specific vehicle types
Vehicle_Type = Car           # A new vehicle class will start with a type field
Length = 4
Width = 2
Speed = 3
Gap = 1
LaneChangeFrequency = 3 
END

Vehicle_Type = bike        # The first character will be used as the symbol for printing
Length = 2
Width = 1
Speed = 7
Gap = 1
END

Vehicle_Type = Bus
Length = 4
Width = 3
Speed = 1
Gap = 1
END

Vehicle_Type = Truck
Length = 4
Width = 4
Speed = 1
Gap = 1
END
# Definitions over
START   #start the simulation

Signal RED 0      # Make the signal RED 0 is the time after which signal should be red

# Send vehicles with given types on the road (one per second)
Bus 0 0 1 1      # specify what vehicle enters then its color(r,g,b) then time after which it comes in seconds
Car 1 0 0 2
bike 0 1 0 3

Pass 10      # pause the simulation for 10 seconds

Car 0 0 1 1      # specify what vehicle enters then its color(r,g,b) then time after which it comes in seconds
Car 1 0 0 2
bike 0 1 0 3

Signal GREEN 0 


END            # End the simulation vehicles
