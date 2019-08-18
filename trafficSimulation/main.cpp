#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
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
#include "background.hpp"
#include "constants_main.hpp"
#include "utility.hpp"
#include "vehicle.hpp"
#include "laneTraffic.hpp"
#include "noLaneTraffic.hpp"

using namespace std;

int lane=1;

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-gluOrtho2D_xSize,gluOrtho2D_xSize,-gluOrtho2D_ySize-2*trafficLightradius-trafficLightYpos,
      gluOrtho2D_ySize+2*trafficLightradius+trafficLightYpos);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  //backgroung
  drawBackground(isRed,frameSim*timeBetweenEachFrame/1000,signalFrame,lane);

  updateTraffic(frameSim,isRed,printMatrixOnTerminal);
  // drawTraffic();
  updateOvertake(isRed,frameSim*timeBetweenEachFrame/1000);
  drawTraffic();
  glFlush();  // Render now
}

void display_nolane() {
  glClear(GL_COLOR_BUFFER_BIT);
  //background
  drawBackground(isRed,frameSim*timeBetweenEachFrame/1000, signalFrame, lane);
  noLane::updateTraffic_noLane(frameSim,isRed,printMatrixOnTerminal);
  // drawTraffic();
  noLane::updateOvertake_noLane(frameSim*timeBetweenEachFrame/1000);
  noLane::drawTraffic_noLane();
  glFlush();  // Render now
} 

void Timer(int value) {
    frameSim++;
    //changing signal if it is to be changed
    if(signalFrame.find(frameSim*timeBetweenEachFrame/1000)!=signalFrame.end()) {
        if(signalFrame[frameSim*timeBetweenEachFrame/1000]=="RED") {
            isRed=true;
        }
        else {
            isRed=false;
        }
    }
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(timeBetweenEachFrame, Timer, 0); // next Timer call milliseconds later
}


int main(int argc, char **argv)
{
    initMain(argv[1],timeBetweenEachFrame,imageLength,imageWidth,signalFrame,gluOrtho2D_xSize,gluOrtho2D_ySize,lane);
    initBackground(argv[1]);

    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);
    imageWidth=(gluOrtho2D_ySize+2*trafficLightradius+trafficLightYpos)/gluOrtho2D_ySize*imageWidth;
    glutInitWindowSize(imageLength,imageWidth);
    glutCreateWindow("Traffic simulation");
    init();
    if(lane==1) {
      init_laneTraffic(argv[1]);
      glutDisplayFunc(display);
    }
    else {
      noLane::init_nolaneTraffic(argv[1]);
      glutDisplayFunc(display_nolane);
    }
    frameSim=-1;
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}
