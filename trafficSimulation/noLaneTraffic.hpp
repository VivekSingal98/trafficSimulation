#ifndef noLaneTraffic_hpp
#define noLaneTraffic_hpp

#include <GL/glut.h>
#include<iostream>//for strlen
#include<string>
#include <fstream>
#include <sstream>
#include <cmath>
#include<algorithm>
#include<map>
#include <unistd.h>
#include "readConfig.hpp"
#include "utility.hpp"
#include "vehicle.hpp"
#include "mesh.hpp"

using namespace std;

namespace noLane {
void init_nolaneTraffic(string file);
vehicle findVehicleFromId(int id);
vehicle  findFrontVehicle(vehicle& v);
float maxDistance_Line(int i) ;
void updateTraffic_noLane(int frameSim,bool isRed,bool printMatrixTerminal) ;
void drawTraffic_noLane();
void updateOvertake_noLane(float currTime);
}
#endif /* noLaneTraffic_hpp */