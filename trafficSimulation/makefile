CXX = g++-8
CXXFLAGS = -Wall -g  -Iinclude
LIBS= -L/usr/local/Cellar/freeglut/3.0.0/lib -framework OpenGL -lglut 
INCLUDE=-I/usr/local/include
simulation: main.o background.o utility.o readConfig.o vehicle.o constants_main.hpp constants_traffic.hpp mesh.o laneTraffic.o noLaneTraffic.o
	$(CXX) $(CXXFLAGS)  -o simulation main.o background.o utility.o readConfig.o vehicle.o mesh.o laneTraffic.o noLaneTraffic.o $(LIBS)
main.o: main.cpp background.hpp readConfig.hpp vehicle.hpp utility.hpp constants_main.hpp
	$(CXX) $(CXXFLAGS)  $(INCLUDE) -c main.cpp $(LIBS)
laneTraffic.o: laneTraffic.cpp laneTraffic.hpp readConfig.hpp vehicle.hpp utility.hpp constants_traffic.hpp mesh.hpp
	$(CXX) $(CXXFLAGS)  $(INCLUDE) -c laneTraffic.cpp $(LIBS)
noLaneTraffic.o: noLaneTraffic.cpp noLaneTraffic.hpp readConfig.hpp vehicle.hpp utility.hpp constants_traffic.hpp mesh.hpp
	$(CXX) $(CXXFLAGS)  $(INCLUDE) -c noLaneTraffic.cpp $(LIBS)
background.o: background.cpp readConfig.hpp background.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c background.cpp  $(LIBS)
utility.o: utility.cpp utility.hpp
	$(CXX) $(CXXFLAGS) -c utility.cpp
readConfig.o: readConfig.cpp readConfig.hpp vehicle.hpp
	$(CXX) $(CXXFLAGS) -c readConfig.cpp	
mesh.o: mesh.cpp mesh.hpp vehicle.hpp
	$(CXX) $(CXXFLAGS) -c mesh.cpp	
vehicle.o: vehicle.cpp vehicle.hpp 
	$(CXX) $(CXXFLAGS) -c vehicle.cpp

clean: 
	-rm -f main *.o core *.core