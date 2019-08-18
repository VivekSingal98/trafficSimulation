#ifndef constants_main_h
#define constants_main_h
#include <map>
#include<vector>

using namespace std;

static bool isRed=true;   //tells if refLIght is on or not
static int frameSim=-1;   //tells frame number
static float timeBetweenEachFrame=1; //in ms
static float imageLength=720;  //size of image in pixels
static float imageWidth=450;
static float gluOrtho2D_xSize=15;
static float gluOrtho2D_ySize=15;
static bool printMatrixOnTerminal=true;
static float trafficLightradius=2;
static float trafficLightYpos=1;
static map<float,string> signalFrame;

#endif /* constants_main_h */