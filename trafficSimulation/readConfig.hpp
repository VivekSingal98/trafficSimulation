#ifndef readConfig_hpp
#define readConfig_hpp

#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "vehicle.hpp"

using namespace std;

void readConfigFile_RoadParam(ifstream& fin,map<string, float>& mapRoadParam);
void readConfigFile_DefaultParam(ifstream& fin,map<string,float>& mapDefaultParam);
void readConfigFile_VehicleParam(ifstream& fin, string carType,map<string, float>& mapVehicleParam);
void readConfigFile_Simulation(ifstream& fin,map<string, float>& mapVehicleParam,map<float,string>& signalFrame,vector<vehicle>& vehicleVector,map<string,float>& mapDefaultParam);
void initTraffic(string file,map<string, float>& mapRoadParam,map<string,float>& mapDefaultParam,vector<vehicle>& vehicleVector,map<float,string>& signalFrame);
void initMain(string file,float& timeBetweenEachFrame,float& imageLength,float& imageWidth,map<float,string>& signalFrame,float& gluOrtho2D_xSize,float& gluOrtho2D_ySize,int& lane);

#endif /* readConfig_hpp */
