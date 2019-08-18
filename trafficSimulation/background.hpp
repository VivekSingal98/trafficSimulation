#ifndef background_hpp
#define background_hpp

#include <stdio.h>
#include <GL/glut.h>
#include <map>

using namespace std;

void redLight(bool light,float timInSec,map<float,string>& signalFrame);
void drawRoad(int lane);
void initBackground(string file);
void drawBackground(bool isRed,float timInSec,map<float,string>& signalFrame,int lane);

#endif /* background_hpp */
