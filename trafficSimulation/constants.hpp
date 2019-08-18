#ifndef constants_h
#define constants_h
#include <map>
#include<vector>

using namespace std;


static bool isRed=true;
static int frameSim=-1;
static float redLightThreshold=1;
static float redLightThreshold1=0.3;
static float brakingBeforeConstant=0.1;
static float distanceFrontThreshold=0;

static map<string, float> mapVehicleParam;
static map<string, float> mapRoadParam;
static map<string,float> mapDefaultParam;
static map<float,string> signalFrame;
static map<float,float> mapPass;

#endif /* constants_h */
