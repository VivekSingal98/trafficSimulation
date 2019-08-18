#ifndef laneTraffic_hpp
#define laneTraffic_hpp

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

void drawTraffic();
void init_laneTraffic(string file);
void updateTraffic(int frameSim,bool printMatrixTerminal,bool isRed);
map<bool,float> checkSpace(vehicle& v,int lane,int ** mesh,bool isRed);
void updateOvertake(bool isRed,float currTime);

#endif /* laneTraffic_hpp */