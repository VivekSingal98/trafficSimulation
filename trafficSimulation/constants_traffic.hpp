#ifndef constants_traffic__h
#define constants_traffic_h
#include <map>
#include<vector>

using namespace std;


static float redLightThreshold=1;
static float redLightThreshold1=0.1;
static float brakingBeforeConstant=0.5;
static float distanceFrontThreshold=0;
static float timeToCrossRedLightThreshold=0.5;   //in seconds
static map<string, float> mapRoadParam;
static map<string,float> mapDefaultParam;
static map<float,string> signalFrame;


#endif /* constants_traffic_h */
