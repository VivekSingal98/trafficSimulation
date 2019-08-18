#ifndef mesh_hpp
#define mesh_hpp


#include<string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include "vehicle.hpp"

using namespace std;

void setMesh(map<string, float>& mapRoadParam1);
bool checkFilled(float xpos,float ypos,vehicle& v,int ** mesh);
bool checkFilled1(float xpos,float ypos,vehicle& v,int ** mesh);
void setZeroMeshVehicle(vehicle& v,int ** mesh);
void fillMeshVehicle(vehicle& v,int ** mesh);
bool checkVehicleInMesh(vehicle& v,int ** mesh);

#endif /* background_hpp */