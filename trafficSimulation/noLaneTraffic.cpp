#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "noLaneTraffic.hpp"
#include "constants_traffic.hpp"

namespace noLane {

vector<vehicle> vehicleBuffer;
vector<vehicle> vehiclesOnRoad;
int** mesh;
void drawTraffic_noLane()
{
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    for(int i=0;i<(int)vehiclesOnRoad.size();i++) {
      vehicle& v=vehiclesOnRoad[i];
      glLoadIdentity();// Reset the model-view matrix
      glTranslatef(v.xPos, v.yPos, 0.0f);
      glRotatef(v.angle,0.0f,0.0f,1.0f);
      if(v.type=="Auto"){
          glBegin(GL_POLYGON);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/2, v.width/2);
          glVertex2f(-v.length/2, -v.width/2);
          glVertex2f(v.length/2-0.2, -v.width/2);
          glVertex2f(v.length/2, -0.3);
          glVertex2f(v.length/2, 0.3);
          glVertex2f(v.length/2-0.2, v.width/2);                
          glEnd();

          glBegin(GL_POLYGON);
          glVertex2f(v.length/2, -0.3);
          glVertex2f(v.length/2+0.4, -0.2);
          glVertex2f(v.length/2+0.4, 0.2);
          glVertex2f(v.length/2, 0.3);
          glEnd();


      }
      else if(v.type=="bike"){
          glBegin(GL_POLYGON);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/2, v.width/8);
          glVertex2f(-v.length/2, -v.width/8);
          glVertex2f(-0.5, -v.width/4);
          glVertex2f(-0.5, v.width/4);                
          glEnd();

          glBegin(GL_POLYGON);
          glVertex2f(-0.5, -v.width/4);
                          
          glVertex2f(0, -v.width/2);
          glVertex2f(0.5,-v.width/4);
          glVertex2f(0.5,v.width/4);
          glVertex2f(0, v.width/2);
          glVertex2f(-0.5, v.width/4);
          glEnd();                

          glBegin(GL_POLYGON);
          glVertex2f(0.5, -v.width/4);
          glVertex2f(v.length/2,-v.width/8);                
          glVertex2f(v.length/2, v.width/8);
          glVertex2f(0.5,v.width/4);
          glEnd();
      }

      else if(v.type=="Car"){
          glBegin(GL_POLYGON);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/3,v.width/2);
          glVertex2f(-v.length/2, v.width/3);
          glVertex2f(-v.length/2, -v.width/3);
          glVertex2f(-v.length/3,-v.width/2);
          glVertex2f(v.length/3, -v.width/2);
          glVertex2f(v.length/2,-v.width/3);
          glVertex2f(v.length/2,v.width/3);
          glVertex2f(v.length/3, v.width/2);                
          glEnd();

      }

      else if(v.type=="Bus"){
          glBegin(GL_POLYGON);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/2.2,v.width/2);
          glVertex2f(-v.length/2, v.width/2.2);
          glVertex2f(-v.length/2, -v.width/2.2);
          glVertex2f(-v.length/2.2,-v.width/2);
          glVertex2f(v.length/2.2, -v.width/2);
          glVertex2f(v.length/2,-v.width/2.2);
          glVertex2f(v.length/2,v.width/2.2);
          glVertex2f(v.length/2.2, v.width/2);                
          glEnd();

      }

      else if(v.type=="Truck"){
          glBegin(GL_POLYGON);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/2,v.width/2);
          glVertex2f(-v.length/2, -v.width/2);
          glVertex2f(v.length/3, -v.width/2);
          glVertex2f(v.length/3, v.width/2);                
          glEnd();

          glBegin(GL_POLYGON);
          glVertex2f(v.length/3,-v.width/3);
          glVertex2f(v.length/2, -v.width/3);
          glVertex2f(v.length/2,v.width/3);
          glVertex2f(v.length/3,v.width/3);

          glEnd();

      }

      else{
          glBegin(GL_QUADS);
          glColor3f(v.color[0],v.color[1],v.color[2]);
          glVertex2f(-v.length/2, v.width/2);
          glVertex2f(v.length/2, v.width/2);
          glVertex2f(v.length/2, -v.width/2);
          glVertex2f(-v.length/2, -v.width/2);
          glEnd();                
      }
      glLoadIdentity();// Reset the model-view matrix
       glColor3f(1,1,1);
      glRasterPos2f( v.xPos , v.yPos);
      string ch=""+to_string((int)(v.speed));//+" : "+to_string((int)v.id);
      // string ch=to_string(v.id);
      int numofchar = (int)ch.length();
      for (int i = 0; i <= numofchar - 1; i++)
      {
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
      }
    }
}


void init_nolaneTraffic(string file) {
  initTraffic(file,mapRoadParam,mapDefaultParam,vehicleBuffer,signalFrame);
  // cout<<"step time"<<mapDefaultParam["stepTime"];
  mesh = createMatrix(mapRoadParam["Road_Width"],mapRoadParam["Road_Length"]);
  setMesh(mapRoadParam);
}

vehicle findVehicleFromId(int id) {
  for(int i=0;i<(int)vehiclesOnRoad.size();i++) {
    vehicle& v= vehiclesOnRoad[i];
    if(v.id==id) {
      return v;
    }
  }
  vehicle v(1,1,1,1,1,1,1,1);
  v.id=-1;
  return v;
}

vehicle  findFrontVehicle(vehicle& v) {
  float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
  float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
  float angle_rad=v.angle*M_PI/180;
  float lengthBox=abs(v.length*cos(angle_rad))+abs(v.width*sin(angle_rad));
  float widthBox=abs(v.length*sin(angle_rad))+abs(v.width*cos(angle_rad));

  int right_X=(int)ceil(trans_X+lengthBox/2);
  int up_Y=(int)floor(trans_Y-widthBox/2);
  int down_Y=(int)ceil(trans_Y+widthBox/2);
  
  float minDistance=2*mapRoadParam["Road_Length"];
  int minDistanceId=-1;
  for(int i=up_Y;i<down_Y;i++) {
    for(int j=right_X;j<(int)mapRoadParam["Road_Length"];j++)
        if(j<mapRoadParam["Road_Length"] && j>=0 && i<mapRoadParam["Road_Width"] && i>=0 && mesh[i][j]>-1) {
            vehicle v_tmp=findVehicleFromId(mesh[i][j]);
            if(j-right_X<minDistance && v_tmp.id!=v.id ) {
              minDistance=j-right_X;
              minDistanceId=mesh[i][j];
            }
        }
  }
  return findVehicleFromId(minDistanceId);
}

vehicle findBottomVehicle(vehicle& v) {
  float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
  float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
  float angle_rad=v.angle*M_PI/180;
  float lengthBox=abs(v.length*cos(angle_rad))+abs(v.width*sin(angle_rad));
  float widthBox=abs(v.length*sin(angle_rad))+abs(v.width*cos(angle_rad));

  int right_X=(int)ceil(trans_X+lengthBox/2);
  int down_Y=(int)ceil(trans_Y+widthBox/2);

  int vehicleId=-1;
  for(int i=down_Y;i<mapRoadParam["Road_Width"];i++) {
    for(int j=right_X-1;j>=0;j--) {
      vehicle v_tmp=findVehicleFromId(mesh[i][j]);
      if(mesh[i][j]>-1 && v_tmp.laneNo!=v.laneNo && (v_tmp.xPos+v_tmp.length/2)<=(v.xPos+v.length/2)){
        vehicleId=mesh[i][j];
        i=2*mapRoadParam["Road_Width"];
        break;
      }
    }
  }

  return findVehicleFromId(vehicleId);

}

vehicle findTopVehicle(vehicle& v) {
  float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
  float trans_Y=mapRoadParam["Road_Width"]/2-v.yPos;
  float angle_rad=v.angle*M_PI/180;
  float lengthBox=abs(v.length*cos(angle_rad))+abs(v.width*sin(angle_rad));
  float widthBox=abs(v.length*sin(angle_rad))+abs(v.width*cos(angle_rad));

  int right_X=(int)ceil(trans_X+lengthBox/2);
  int up_Y=(int)floor(trans_Y-widthBox/2);

  int vehicleId=-1;
  for(int i=up_Y-1;i>=0;i--) {
    for(int j=right_X-1;j>=0;j--) {
      vehicle v_tmp=findVehicleFromId(mesh[i][j]);
      if(mesh[i][j]>-1 && v_tmp.laneNo!=v.laneNo && (v_tmp.xPos+v_tmp.length/2)<=(v.xPos+v.length/2)){
        vehicleId=mesh[i][j];
        i=-2;
        break;
      }
    }
  }

  return findVehicleFromId(vehicleId);
}


float maxDistance_Line(int i) {
  float distance=mapRoadParam["Road_Length"];
  for(int j=0;j<mapRoadParam["Road_Length"];j++) {
    if(i<mapRoadParam["Road_Width"] && i>=0 && mesh[i][j]>-1) {
      distance=j;
      break;
    }
  }
  return distance;
}

void updateTraffic_noLane(int frameSim,bool isRed,bool printMatrixTerminal) {
    if(printMatrixTerminal && ceil(mapDefaultParam["stepTime"]*frameSim/1000)==mapDefaultParam["stepTime"]*frameSim/1000) {
        cout<<mapDefaultParam["stepTime"]*frameSim/1000<<endl;
        printMatrix(mesh,mapRoadParam["Road_Width"],mapRoadParam["Road_Length"]);
    }
    //updating vehicles position
    for(int i=0;i<(int)vehiclesOnRoad.size();i++) {
      vehicle& v =vehiclesOnRoad[i]; 
      vehicle vFront=findFrontVehicle(v);

      float accMod=abs(v.acceleration);
      float brakingDistance=v.speed*v.speed/(2*accMod)+brakingBeforeConstant; 
           
      float distance_from_redlight=mapRoadParam["Road_Signal"]-(v.xPos+v.length/2);
      bool accPos=true;

      if(abs(distance_from_redlight-brakingDistance)>redLightThreshold || !isRed) {
        accPos=true;
      }
      else {
        accPos=false;
      }
      float timeInSec=frameSim*mapDefaultParam["stepTime"]/1000; //current time
      if(abs(distance_from_redlight-brakingDistance)<redLightThreshold && 
              accPos && !isRed && signalFrame.upper_bound(timeInSec)!=signalFrame.end()) { //light is green but is going to red fast
              //finding time taken to pass the traffic light
              //s=ut+1/2*a*t2
          
              float timeToCrossRedLight=-v.speed/accMod+sqrt(v.speed*v.speed/(accMod*accMod)+2*distance_from_redlight/accMod);
              // float timeToCrossRedLight=0;
              // if(v.speed!=0) {
              //   timeToCrossRedLight=distance_from_redlight/v.speed;
              // }
              float timeToRedlight=(*signalFrame.upper_bound(timeInSec)).first -timeInSec;
    
              if(timeToCrossRedLight>=timeToRedlight || abs(timeToCrossRedLight-timeToRedlight)<=timeToCrossRedLightThreshold) {
             
                accPos=false;
              }
            }
      if(vFront.id!=-1 && accPos) {
        brakingDistance=(v.speed-vFront.speed)*(v.speed-vFront.speed)/(2*accMod)+brakingBeforeConstant;           
        if(v.speed<vFront.speed) {
          brakingDistance = 0;
        }
        float distanceFront=vFront.xPos-vFront.length/2-(v.xPos+v.length/2+v.gap);

        if(distanceFront<=brakingDistance) {
          accPos=false;
        }
        else {
          accPos=true;
        }
        // if(v.id==16) {
        //   cout<<"BreakingDistance "<<brakingDistance<<" distanceFront "<<distanceFront<<" accMode "<<accPos<<endl;
        // }
      }
      if(accPos) {
        v.acceleration=accMod;
      }
      else {
        v.acceleration=-accMod; 
      }
   
      v.speed = v.speed + v.acceleration*(float)(mapDefaultParam["stepTime"])/1000;
      if(v.speed>mapDefaultParam["Default_MaxSpeed"]) {
        v.speed=mapDefaultParam["Default_MaxSpeed"];
      }
      if(v.speed<0) {
         v.speed=0;
      }
      if(vFront.id!=-1) {
        float distanceFront=vFront.xPos-vFront.length/2-(v.xPos+v.length/2+v.gap);
        if(distanceFront<distanceFrontThreshold && v.speed>vFront.speed) {
          v.speed=vFront.speed;
        }
      }
      //handle case when redlight becomes red and braking distance is grater than physical distance or car changes lane and braking distance is more
      //emergency breaking
      if(isRed && abs(distance_from_redlight)<redLightThreshold1) {
        v.speed=0;
      }

      //handling vehicle at odd angle in middle of lane
      if(v.angle!=0) {
        v.speed=0;
      }
     
      float newX=v.xPos+v.speed*(float)(mapDefaultParam["stepTime"])/1000;
      setZeroMeshVehicle(v,mesh);
      v.xPos=newX;
      //check if vehicle has driven out of window
      if(checkVehicleInMesh(v,mesh)==false) {
          vehiclesOnRoad.erase(vehiclesOnRoad.begin()+i);
          i--;
      }
      else {
          fillMeshVehicle(v,mesh);
      }
  }

  //adding vehicled from vehicle buffer to vehiclesOnRoad
  for(int i=0;i<(int)vehicleBuffer.size();i++) {
    vehicle& v=vehicleBuffer[i];
    
    if(v.inTime>frameSim*mapDefaultParam["stepTime"]/1000) {
        continue;
    }
    v.xPos=-mapRoadParam["Road_Length"]/2-v.length/2+1;
    
    //choosing the lane with last vehicle farthest away
    float maxDist=0; 
    // int widthNum=0;
    /*for(int i=0;i<mapRoadParam["Road_Width"];i++) {
        if(i+v.width>mapRoadParam["Road_Width"]) {
          break;
        }
        float minDistance=mapRoadParam["Road_Length"];
        for(int k=0;k<v.width;k++) {
          if(minDistance>maxDistance_Line(k+i)) {
            minDistance=maxDistance_Line(k+i);
          }
        }
        if(maxDist<minDistance) {
          widthNum=i;
          maxDist=minDistance;
        }
    }*/

    for(int i=0;i<mapRoadParam["Num_Lanes"];i++) {
      int widthNumi=mapRoadParam["Lane_Width"]*i + mapRoadParam["Lane_Width"]/2-v.width/2;
      if(widthNumi+v.width>mapRoadParam["Road_Width"]) {
          break;
      }
      float minDistance=mapRoadParam["Road_Length"];
      for(int k=0;k<v.width;k++) {
        if(minDistance>maxDistance_Line(k+widthNumi)) {
          minDistance=maxDistance_Line(k+widthNumi);
        }
      }
      if(maxDist<minDistance) {
        // widthNum=widthNumi;
        v.laneNo=i;
        maxDist=minDistance;
      }
    }    
    if(maxDist<=1) { //no available space
      continue;
    }
    // cout<<widthNum<<endl;
    v.yPos=mapRoadParam["Road_Width"]/2-mapRoadParam["Lane_Width"]*v.laneNo - mapRoadParam["Lane_Width"]/2;
    // cout<<v.yPos<<endl;
    vehicle vFront=findFrontVehicle(v);
    float distanceFront_current=vFront.xPos-vFront.length/2-(v.xPos+v.length/2+v.gap);
    if(v.id!=-1 && distanceFront_current<0) {
      continue;   //the lane in which it is trying to get will be occupied by some other vehicle
    }

    fillMeshVehicle(v,mesh);
    vehiclesOnRoad.push_back(v);
    vehicleBuffer.erase(vehicleBuffer.begin()+i);
    i--;
  }

}

void updateOvertake_noLane(float currentTime){ 
  for(int i=0;i<(int)vehiclesOnRoad.size();i++) {
    vehicle& v= vehiclesOnRoad[i];
    if(currentTime-v.lastLaneChangedTime<v.laneChangeFrequency) {
      continue;   //changed lane recently
    }
    if(v.speed==0 && (v.type=="Auto"||v.type=="bike"||v.type=="Car") && v.angle==0  && !v.midLane && findFrontVehicle(v).id!=-1 && findFrontVehicle(v).xPos<=mapRoadParam["Road_Signal"]) {
      //find front vehicle

      vehicle vFront=findFrontVehicle(v);
      if(vFront.id==-1) {
        continue;
      }

      vehicle vBottom=findBottomVehicle(v);
      vehicle vTop=findTopVehicle(v);

      setZeroMeshVehicle(v,mesh);
      if(vBottom.id==-1 && v.laneNo<mapRoadParam["Num_Lanes"]-1 && !checkFilled(v.xPos,v.yPos-mapRoadParam["Lane_Width"]/2
        ,v,mesh)) {
        setZeroMeshVehicle(v,mesh);
        v.angle=315;
        v.yPos=v.yPos-mapRoadParam["Lane_Width"]/2;
        v.midLane = true;
        // v.laneNo=v.laneNo+0.5;
        v.lastLaneChangedTime=currentTime;
      }
      else if(vTop.id==-1 && v.laneNo>0 && !checkFilled(v.xPos,v.yPos+mapRoadParam["Lane_Width"]/2
        ,v,mesh)) {
        setZeroMeshVehicle(v,mesh);
        v.angle=45;
        // v.laneNo=v.laneNo-0.5;
        v.midLane=true;
        v.yPos=v.yPos+mapRoadParam["Lane_Width"]/2;
        v.lastLaneChangedTime=currentTime;
      }
      else {
        float d_bottom=-1;
        float d_bottom_angle=-1;
        float d_top=-1;
        float d_top_angle=-1;
        if(vBottom.id>-1) {
          d_bottom=sqrt(pow(((vFront.xPos-vFront.length/2)-(vBottom.xPos+vBottom.length/2)),2)
                    +pow(((vFront.yPos-vFront.width/2)-(vBottom.yPos+vBottom.width/2)),2) );
          d_bottom_angle=((vFront.yPos-vFront.width/2)-(vBottom.yPos+vBottom.width/2))/((vFront.xPos-vFront.length/2)-(vBottom.xPos+vBottom.length/2));
          d_bottom_angle=atan(d_bottom_angle)*180/M_PI+270;
        }
        if(vTop.id>-1) {
          d_top=sqrt(pow(((vFront.xPos-vFront.length/2)-(vTop.xPos+vTop.length/2)),2)
                    +pow(((vFront.yPos+vFront.width/2)-(vTop.yPos-vTop.width/2)),2) );
          d_top_angle=((vFront.yPos+vFront.width/2)-(vTop.yPos-vTop.width/2))/((vFront.xPos-vFront.length/2)-(vTop.xPos+vTop.length/2));
          d_top_angle=atan(d_top_angle)*180/M_PI+90;
        }

        if(d_bottom!=-1 || d_top!=-1) {
          if(d_bottom>=d_top && d_bottom>=v.width && vBottom.laneNo!=vFront.laneNo ) {
            float tmp_yPos=v.yPos-mapRoadParam["Lane_Width"]/2;
            float tmp_xPos=max(((vFront.xPos-vFront.length/2)+(vBottom.xPos+vBottom.length/2))/2,v.xPos);
            if(!checkFilled(tmp_xPos,tmp_yPos,v,mesh) && d_bottom_angle>270) {
              setZeroMeshVehicle(v,mesh);
              v.yPos=tmp_yPos;
              v.xPos=tmp_xPos;
              v.angle=d_bottom_angle;
              v.midLane=true;
              v.lastLaneChangedTime=currentTime;
            }
          }
          else if(d_top>=d_bottom &&  d_top>=v.width && vTop.laneNo!=vFront.laneNo){
            float tmp_yPos=v.yPos+mapRoadParam["Lane_Width"]/2;
            float tmp_xPos=max(((vFront.xPos-vFront.length/2)+(vTop.xPos+vTop.length/2))/2,v.xPos);
            if(!checkFilled(tmp_xPos,tmp_yPos,v,mesh) && d_top_angle<90) {
              setZeroMeshVehicle(v,mesh);
              v.yPos=tmp_yPos;
              v.xPos=tmp_xPos;
              v.angle=d_top_angle;
              v.midLane=true;
              v.lastLaneChangedTime=currentTime;
            }
          }
        }

      }
      fillMeshVehicle(v,mesh);
    }
  
    else if(v.speed==0 && (v.type=="Auto"||v.type=="bike"||v.type=="Car") && v.angle!=0) {
      float prev_angle=v.angle;
      setZeroMeshVehicle(v,mesh);
      v.angle=0;
      
      if(checkFilled(v.xPos+3,v.yPos,v,mesh)) {
        setZeroMeshVehicle(v,mesh);
        v.angle=prev_angle;
      }
      else {
        setZeroMeshVehicle(v,mesh);
        v.lastLaneChangedTime=currentTime;
        fillMeshVehicle(v,mesh);
        continue;
      }

      //changing lane
      
      if(v.angle>180 ) {
        if(!checkFilled(v.xPos,v.yPos-mapRoadParam["Lane_Width"]/2,v,mesh)){
          if(v.id==2) {
          }
          setZeroMeshVehicle(v,mesh);
          v.yPos=v.yPos-mapRoadParam["Lane_Width"]/2;
          v.angle = 0;
          v.laneNo = v.laneNo + 1;
          fillMeshVehicle(v,mesh);
          v.lastLaneChangedTime=currentTime;
          continue;
        }
        else if(!checkFilled(v.xPos+v.length,v.yPos-mapRoadParam["Lane_Width"]/2,v,mesh)){
          setZeroMeshVehicle(v,mesh);
          v.xPos=v.xPos+v.length/2;
          v.yPos=v.yPos-mapRoadParam["Lane_Width"]/2;
          v.angle = 0;
          v.laneNo = v.laneNo + 1;
          fillMeshVehicle(v,mesh);
          v.lastLaneChangedTime=currentTime;
          continue;
        }
        else {
          vehicle vFront=findFrontVehicle(v);
          vehicle vBottom=findBottomVehicle(v);
          // if(v.id==2) {
          //   cout<<"vFront  "<<vFront.id<<" vBottom.id "<<vBottom.id<<endl;
          // }
          float d_bottom_angle=((vFront.yPos-vFront.width/2)-(vBottom.yPos+vBottom.width/2))/((vFront.xPos-vFront.length/2)-(vBottom.xPos+vBottom.length/2));
          d_bottom_angle=atan(d_bottom_angle)*180/M_PI+270;
          if(vFront.laneNo!=vBottom.laneNo && d_bottom_angle > 270 && vBottom.id!=-1){
            v.angle=d_bottom_angle;
          }
          fillMeshVehicle(v,mesh);
          continue;
        }
      }
      else {
        if(!checkFilled(v.xPos,v.yPos+mapRoadParam["Lane_Width"]/2,v,mesh)){
          setZeroMeshVehicle(v,mesh);
          v.yPos=v.yPos+mapRoadParam["Lane_Width"]/2;
          v.angle = 0;
          v.laneNo = v.laneNo -1;
          fillMeshVehicle(v,mesh);
          v.lastLaneChangedTime=currentTime;
          continue;
        }      
        else if(!checkFilled(v.xPos+v.length,v.yPos+mapRoadParam["Lane_Width"]/2,v,mesh)){
          setZeroMeshVehicle(v,mesh);
          v.xPos=v.xPos+v.length/2;
          v.yPos=v.yPos+mapRoadParam["Lane_Width"]/2;
          v.angle = 0;
          v.laneNo = v.laneNo -1;
          fillMeshVehicle(v,mesh);
          v.lastLaneChangedTime=currentTime;
          continue;
        }
        else {
          vehicle vFront=findFrontVehicle(v);
          vehicle vTop=findTopVehicle(v);
          float d_top_angle=((vFront.yPos+vFront.width/2)-(vTop.yPos-vTop.width/2))/((vFront.xPos-vFront.length/2)-(vTop.xPos+vTop.length/2));
          d_top_angle=atan(d_top_angle)*180/M_PI+90;
          if(vFront.laneNo!=vTop.laneNo && d_top_angle < 90 && vTop.id!=-1){
            v.angle=d_top_angle;
          }
          fillMeshVehicle(v,mesh);
          continue;
        }  
      }
      fillMeshVehicle(v,mesh);
    }
  }

}

} //namespace ending

