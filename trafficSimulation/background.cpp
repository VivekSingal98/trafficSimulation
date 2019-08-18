#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <GL/glut.h>
#include<string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include "background.hpp"
#include "readConfig.hpp"

using namespace std;

static map<string, float> mapRoadParam;


void initBackground(string file) {
    
    mapRoadParam["Road_Length"]=30;
    mapRoadParam["Road_Signal"]=0;
    mapRoadParam["Road_Width"]=5;

    ifstream fin;
    fin.open(file);
    if(!fin.is_open()) {
        cout<<"file not opened";
    }
    string line;
    while (getline(fin,line) ) {
        istringstream iss(line);
        string word;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="Road_Param") {
            readConfigFile_RoadParam(fin,mapRoadParam);
            break;
        }
        
    }
    
    fin.close();
}

void redLight(bool light,float timeInSec,map<float,string>& signalFrame)//draw the text for score and game over
{

    if(light){
        glColor3f(1,0,0);
    }
    else{
       glColor3f(0,1,0);
    }

    float radius=2;
    float xpos=mapRoadParam["Road_Signal"];
    float ypos=mapRoadParam["Road_Width"]/2 + radius+1;
    
    glLoadIdentity();// Reset the model-view matrix
    glTranslatef(xpos, ypos, 0.0f);
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2 * M_PI; i += M_PI / 20) 
          glVertex2f(cos(i) * radius, sin(i) * radius);
    glEnd();
    
    string ch = "";
    if(signalFrame.upper_bound(timeInSec)!=signalFrame.end()) {
        ch = to_string((int)(*signalFrame.upper_bound(timeInSec)).first - (int)timeInSec) + " sec"; 
    }
    else{
        ch = ch + "-- sec";
    }

    int numofchar = (int)ch.length();
    glLoadIdentity ();

    glColor3f(0,0,0);
    glRasterPos2f( xpos -radius/2, ypos);
    for (int i = 0; i <= numofchar - 1; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
    }

}

void drawRoad(int lane)
{
   /* if(lane==0) {
      glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    glLoadIdentity();               // Reset the model-view matrix
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
    float xPos=mapRoadParam["Road_Length"]/2.0;
    float yPos=mapRoadParam["Road_Width"]/2.0;
    glVertex2f(-xPos, yPos);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos, -yPos);
    glVertex2f(-xPos, -yPos);
    glEnd();
    glPushAttrib(GL_ENABLE_BIT); // glPushAttrib is done to return everything to normal after drawing
    glColor3f(0,0,0);
    glLineStipple(5, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-xPos,0);
    glVertex2f(xPos,0);
    glEnd();
    glPopAttrib();
    return;
    }*/
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    glLoadIdentity();               // Reset the model-view matrix
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0.5);
    float xPos=mapRoadParam["Road_Length"]/2.0;
    float yPos=mapRoadParam["Road_Width"]/2.0;
    glVertex2f(-xPos, yPos);
    glVertex2f(xPos, yPos);
    glVertex2f(xPos, -yPos);
    glVertex2f(-xPos, -yPos);
    glEnd();
    glPushAttrib(GL_ENABLE_BIT); // glPushAttrib is done to return everything to normal after drawing
    
    glLineStipple(5, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(5);
    for(int i=1;i<(int)mapRoadParam["Num_Lanes"];i++){
        glBegin(GL_LINES);
        glColor3f(1,1,1);
        glVertex2f(-xPos,yPos-i*mapRoadParam["Lane_Width"]);
        glVertex2f(xPos,yPos-i*mapRoadParam["Lane_Width"]);
        glEnd();
    }
    glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex2f(mapRoadParam["Road_Signal"],mapRoadParam["Road_Width"]/2);
    glVertex2f(mapRoadParam["Road_Signal"],-mapRoadParam["Road_Width"]/2);
    glEnd();

    glPopAttrib();
}

void drawBackground(bool isRed,float timeInSec,map<float,string>& signalFrame,int lane) {
  drawRoad(lane);
  redLight(isRed,timeInSec,signalFrame);
}
