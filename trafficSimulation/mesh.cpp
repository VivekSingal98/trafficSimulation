#include "mesh.hpp"

static map<string, float> mapRoadParam;

void setMesh(map<string, float>& mapRoadParam1) {
  mapRoadParam = mapRoadParam1;
}

bool checkFilled(float xpos,float ypos,vehicle& v,int ** mesh) {
    setZeroMeshVehicle(v,mesh); //deleting v's position on mesh

    float trans_X=xpos+mapRoadParam["Road_Length"]/2;
    float trans_Y=mapRoadParam["Road_Width"]/2-ypos;
    int left_X=(int)floor(trans_X-v.length/2);
    int right_X=(int)ceil(trans_X+v.length/2);
    int up_Y=(int)floor(trans_Y-v.width/2);
    int down_Y=(int)ceil(trans_Y+v.width/2);
    if(up_Y<0 || down_Y>mapRoadParam["Road_Width"]) {
      fillMeshVehicle(v,mesh);
      return true; //vehicle is going out of box
    }
    for(int i=up_Y;i<down_Y;i++) {
        for(int j=left_X;j<right_X;j++) {
            if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0 && mesh[i][j]>-1) {
                fillMeshVehicle(v,mesh);
                return true; //position already occupied by another vehicle
            }
        }
    }
    fillMeshVehicle(v,mesh); //filling v's position again
    return false;
}
bool checkFilled1(float xpos,float ypos,vehicle& v,int ** mesh) {

    float trans_X=xpos+mapRoadParam["Road_Length"]/2;
    float trans_Y=mapRoadParam["Road_Width"]/2-ypos;
    int left_X=(int)floor(trans_X-v.length/2);
    int right_X=(int)ceil(trans_X+v.length/2);
    int up_Y=(int)floor(trans_Y-v.width/2);
    int down_Y=(int)ceil(trans_Y+v.width/2);
    for(int i=up_Y;i<down_Y;i++){
        for(int j=left_X;j<right_X;j++) {
            if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0 && mesh[i][j]>-1) {
                return true; //position already occupied by another vehicle
            }
        }
    }
    return false;
}

void setZeroMeshVehicle(vehicle& v,int ** mesh) {
    float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
    float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
    float angle_rad=v.angle*M_PI/180;
    float lengthBox=abs(v.length*cos(angle_rad))+abs(v.width*sin(angle_rad));
    float widthBox=abs(v.length*sin(angle_rad))+abs(v.width*cos(angle_rad));

    int left_X=(int)floor(trans_X-lengthBox/2);
    int right_X=(int)ceil(trans_X+lengthBox/2);
    int up_Y=(int)floor(trans_Y-widthBox/2);
    int down_Y=(int)ceil(trans_Y+widthBox/2);
    
    for(int i=up_Y;i<down_Y;i++) {
        for(int j=left_X;j<right_X;j++) {
            if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0) {
                mesh[i][j]=-1;
            }
        }
    }
    
}

void fillMeshVehicle(vehicle& v,int ** mesh) {
    float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
    float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
    float angle_rad=v.angle*M_PI/180;
    float lengthBox=abs(v.length*cos(angle_rad))+abs(v.width*sin(angle_rad));
    float widthBox=abs(v.length*sin(angle_rad))+abs(v.width*cos(angle_rad));

    int left_X=(int)floor(trans_X-lengthBox/2);
    int right_X=(int)ceil(trans_X+lengthBox/2);
    int up_Y=(int)floor(trans_Y-widthBox/2);
    int down_Y=(int)ceil(trans_Y+widthBox/2);
    
    for(int i=up_Y;i<down_Y;i++) {
        for(int j=left_X;j<right_X;j++) {
            if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0) {
                mesh[i][j]=v.id;
            }
        }
    }
        
}

bool checkVehicleInMesh(vehicle& v,int ** mesh) {
    float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
    float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
    int left_X=(int)floor(trans_X-v.length/2);
    int right_X=(int)ceil(trans_X+v.length/2);
    int up_Y=(int)floor(trans_Y-v.width/2);
    int down_Y=(int)ceil(trans_Y+v.width/2);
    
    for(int i=up_Y;i<down_Y;i++) {
        for(int j=left_X;j<right_X;j++) {
            if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0) {
                return true;
            }
        }
    }
    return false;
}

