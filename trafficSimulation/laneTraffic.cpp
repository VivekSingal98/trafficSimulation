#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "laneTraffic.hpp"
#include "constants_traffic.hpp"

vector<vector<vehicle>> vehiclesOnLane;
vector<vehicle> vehicleBuffer;

int** mesh;


void drawTraffic()
{
    glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
    for(int i=0;i<(int)mapRoadParam["Num_Lanes"];i++) {
        for(int j=0;j<(int)vehiclesOnLane[i].size();j++) {
            vehicle& v=vehiclesOnLane[i][j];
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
            string ch=""+to_string((int)v.speed);//+" : "+to_string((int)v.id);
            // string ch=to_string(v.id);
            int numofchar = (int)ch.length();
            for (int i = 0; i <= numofchar - 1; i++)
            {
               glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
            }
        }
    }
}

void init_laneTraffic(string file) {
  initTraffic(file,mapRoadParam,mapDefaultParam,vehicleBuffer,signalFrame);
  for(int i=0;i<(int)mapRoadParam["Num_Lanes"];i++) {
        vehiclesOnLane.push_back(*(new vector<vehicle>()));
  }
  mesh = createMatrix(mapRoadParam["Road_Width"],mapRoadParam["Road_Length"]);
  setMesh(mapRoadParam);
}

void updateTraffic(int frameSim, bool isRed, bool printMatrixTerminal) {
    
    if(printMatrixTerminal && ceil(mapDefaultParam["stepTime"]*frameSim/1000)==mapDefaultParam["stepTime"]*frameSim/1000) {
        cout<<mapDefaultParam["stepTime"]*frameSim/1000<<endl;
        printMatrix(mesh,mapRoadParam["Road_Width"],mapRoadParam["Road_Length"]);
    }

    //add vehicles in buffer to vehicles on lane
    vector<int> check;
    for(int i=0;i<(int)vehicleBuffer.size();i++) {
        
        vehicle& v=vehicleBuffer[i];
        //check if v has entered yet
        if(v.inTime>frameSim*mapDefaultParam["stepTime"]/1000) {
            continue;
        }
        v.xPos=-mapRoadParam["Road_Length"]/2-v.length/2;
        bool noentry=true;
        int laneNo=0;
        
        //choosing the lane with last vehicle farthest away
        float maxDist=0.0001f; 
        for(int i=0;i<mapRoadParam["Num_Lanes"];i++) {
            float lastVehicleLane_xpos;
            if(vehiclesOnLane[i].size()>0) {
                lastVehicleLane_xpos=vehiclesOnLane[i][vehiclesOnLane[i].size()-1].xPos - vehiclesOnLane[i][vehiclesOnLane[i].size()-1].length/2 - v.gap;
            }
            else{
                lastVehicleLane_xpos = mapRoadParam["Road_Length"]/2;  
            }
            if(maxDist<lastVehicleLane_xpos+mapRoadParam["Road_Length"]/2 && !(find(check.begin(), check.end(), laneNo) != check.end())) {
                // if(v.id==2 || v.id==5) {
                //   cout<<"id "<<v.id<<" lane number "<<i<<" on frame "<<frameSim<<endl;
                //   cout<<"maxDist "<<maxDist<<" and lane diatance "<<lastVehicleLane_xpos+mapRoadParam["Road_Length"]/2<<endl;
                // }
                noentry=false;
                laneNo=i;
                maxDist=lastVehicleLane_xpos+mapRoadParam["Road_Length"]/2;
            }
        }
        if(noentry==true ) {
            break; //road entrance is full
        }
        check.push_back(laneNo);

        v.laneNo=laneNo;
        v.yPos=mapRoadParam["Road_Width"]/2-mapRoadParam["Lane_Width"]*laneNo - mapRoadParam["Lane_Width"]/2;
        v.laneId=(int)vehiclesOnLane[laneNo].size();
        vehiclesOnLane[laneNo].push_back(v);
        //fillMeshVehicle(v);
        vehicleBuffer.erase(vehicleBuffer.begin()+i);
        i--;

    }

    //moving vehicles forward and updating mesh
    for(int i=0;i<mapRoadParam["Num_Lanes"];i++) {
        for(int j=0;j<(int)vehiclesOnLane[i].size();j++) {
            vehicle& v=vehiclesOnLane[i][j];
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

            if(j!=0 && accPos) {
              brakingDistance=(v.speed*v.speed-vehiclesOnLane[i][j-1].speed*vehiclesOnLane[i][j-1].speed)/(2*accMod)+brakingBeforeConstant;           
              if(v.speed<vehiclesOnLane[i][j-1].speed) {
                brakingDistance = 0;
              } 
              float distanceFront=vehiclesOnLane[i][j-1].xPos-vehiclesOnLane[i][j-1].length/2-(v.xPos+v.length/2+v.gap);
              if(distanceFront<=brakingDistance) {
                accPos=false;
              }
              else {
                accPos=true;
              }
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
            if(j!=0) {
              float distanceFront=vehiclesOnLane[i][j-1].xPos-vehiclesOnLane[i][j-1].length/2-(v.xPos+v.length/2+v.gap);
              if(distanceFront<distanceFrontThreshold && v.speed>vehiclesOnLane[i][j-1].speed) {
                  v.speed=vehiclesOnLane[i][j-1].speed;
                  // cout << "here\n" ;
              }
            }
            //handle case when redlight becomes red and braking distance is grater than physical distance or car changes lane and braking distance is more
            //emergency breaking
            if(isRed && abs(distance_from_redlight)<redLightThreshold1) {
              v.speed=0;
            }

            float newX=v.xPos+v.speed*(float)(mapDefaultParam["stepTime"])/1000;
            setZeroMeshVehicle(v,mesh);
            v.xPos=newX;
            //check if vehicle has driven out of window
            if(checkVehicleInMesh(v,mesh)==false) {
                vehiclesOnLane[i].erase(vehiclesOnLane[i].begin()+j);
                j--;
            }
            else {
                fillMeshVehicle(v,mesh);
            }
        }
    }
}

map<bool,float> checkSpace(vehicle& v,int lane,int ** mesh,bool isRed){
    float trans_X=v.xPos+mapRoadParam["Road_Length"]/2;
    int left_X=(int)floor(trans_X-v.length/2);
    int right_X=(int)ceil(trans_X+v.length/2+v.gap);
    map<bool, float> temp;
    // float accMod=abs(v.acceleration);
    // float brakingDistance=v.speed*v.speed/(2*accMod)+brakingBeforeConstant;            
    for(int k=left_X;k<right_X;k++){
        if(mesh[lane*((int)mapRoadParam["Lane_Width"]) + ((int)mapRoadParam["Lane_Width"])/2][k]>-1){
            temp[false] = 0;
            return temp;
        }
    }
    int i=-1;
    for(i=vehiclesOnLane[lane].size()-1;i>=0;i--){
        if(vehiclesOnLane[lane][i].xPos-vehiclesOnLane[lane][i].length/2-(v.xPos+v.length/2+v.gap)>=0){
            break;
        }
    }

    // float distance_from_redlight=mapRoadParam["Road_Signal"]-(v.xPos+v.length/2);
    // if(abs(distance_from_redlight)<redLightThreshold1 && isRed) {
    //   temp[false] = 0;

    //   return temp;
    // }

    if(i==-1) { //first car in the lane
        if(vehiclesOnLane[lane].size()==0){
          temp[true]=mapRoadParam["Road_Length"]/2-(v.xPos+v.length/2); 
        }
        else{
            float brakingDistance=(vehiclesOnLane[lane][0].speed - v.speed)*(v.speed+vehiclesOnLane[lane][0].speed)/(2*abs(vehiclesOnLane[lane][0].acceleration))+brakingBeforeConstant;           
            if(v.speed>vehiclesOnLane[lane][0].speed) {
                brakingDistance = 0;
            } 
            float distanceFront= (v.xPos-v.length/2)-(vehiclesOnLane[lane][0].xPos+vehiclesOnLane[lane][0].length/2+vehiclesOnLane[lane][0].gap);
            if(distanceFront<=brakingDistance) {
                temp[false] = 0;
            }
            else{
                temp[true] = mapRoadParam["Road_Length"]/2-(v.xPos+v.length/2);
            }
        }   
    }
    else {
        float brakingDistance=(v.speed-vehiclesOnLane[lane][i].speed)*(v.speed+vehiclesOnLane[lane][i].speed)/(2*abs(v.acceleration))+brakingBeforeConstant;           
        if(v.speed<vehiclesOnLane[lane][i].speed) {
            brakingDistance = 0;
        } 
        float distanceFront=vehiclesOnLane[lane][i].xPos-vehiclesOnLane[lane][i].length/2-(v.xPos+v.length/2+v.gap);
        if(distanceFront<=brakingDistance) {
            temp[false] = 0;
            return temp; 
        }

        if((int)vehiclesOnLane[lane].size()-1>i){
            brakingDistance=(vehiclesOnLane[lane][i+1].speed - v.speed)*(v.speed+vehiclesOnLane[lane][i+1].speed)/(2*abs(vehiclesOnLane[lane][i+1].acceleration))+brakingBeforeConstant;           
            if(v.speed>vehiclesOnLane[lane][i+1].speed) {
                brakingDistance = 0;
            } 
            distanceFront= (v.xPos-v.length/2)-(vehiclesOnLane[lane][i+1].xPos+vehiclesOnLane[lane][i+1].length/2+vehiclesOnLane[lane][i+1].gap);
            if(distanceFront<=brakingDistance) {
                temp[false] = 0;
                return temp;
            }
        }

        temp[true] = vehiclesOnLane[lane][i].xPos-vehiclesOnLane[lane][i].length/2- v.gap-(v.xPos+v.length/2);
        
    }
    return temp;
}


void updateOvertake(bool isRed, float currentTime){

    for(int i=0;i<mapRoadParam["Num_Lanes"];i++) {
        for(int j=1;j<(int)vehiclesOnLane[i].size();j++) {
            vehicle& v=vehiclesOnLane[i][j];
            if(currentTime-v.lastLaneChangedTime<v.laneChangeFrequency){
              continue;   //changed lane recently
            }
            int left;int right;
            if(i>0){
                left=i-1;
            }
            else{
                left = -1;
            }
            if(i<mapRoadParam["Num_Lanes"]-1){
                right = i+1;
            }
            else{
                right = -1;
            }

            float maxDist = vehiclesOnLane[i][j-1].xPos - vehiclesOnLane[i][j-1].length/2 - v.gap - (v.xPos+v.length/2); 
            bool laneChange = false;
            int changeTo = 0;

            if(left!=-1){
                map<bool,float> temp = checkSpace(v,left,mesh,isRed);
                if(temp.find(true)!=temp.end() && maxDist< temp[true]){
                    laneChange = true;
                    maxDist = temp[true];
                    changeTo = left;
                }

            }
            if(right!=-1){
                map<bool,float> temp = checkSpace(v,right,mesh,isRed);
                if(temp.find(true)!=temp.end() && maxDist< temp[true]){
                    laneChange = true;
                    maxDist = temp[true];
                    changeTo = right;
                }

            }

            if(!laneChange){
                continue;
            }
            // cout<<v.id<<" changed lane"<<endl;
            v.lastLaneChangedTime=currentTime;
            setZeroMeshVehicle(v,mesh);
     
            if(changeTo>i){
                v.yPos= v.yPos - mapRoadParam["Lane_Width"]/2 ;
                v.angle = 135.0f;
            }
            else{
                v.yPos = v.yPos + mapRoadParam["Lane_Width"]/2;
                v.angle = 45.0f;
            }


            drawTraffic();
            usleep(mapDefaultParam["stepTime"]*900);
            v.angle = 0;
            v.laneNo=changeTo;
          
            if(changeTo>i){
                v.yPos= v.yPos - mapRoadParam["Lane_Width"]/2;
            }
            else{
                v.yPos = v.yPos + mapRoadParam["Lane_Width"]/2;
            }
            
            int k;
            for(k=vehiclesOnLane[changeTo].size()-1;k>=0;k--){
                if(vehiclesOnLane[changeTo][k].xPos-vehiclesOnLane[changeTo][k].length/2-(v.xPos+v.length/2)>=0){
                    break;
                }
            }
            //cout << "id:" << v.id << endl;
            vehiclesOnLane[changeTo].insert(vehiclesOnLane[changeTo].begin()+k+1,v);

            //cout << "id:" << v.id << endl;
            //check if vehicle has driven out of window
            fillMeshVehicle(v,mesh);
            // cout << "id:" << v.id << " from:" << i << " to:" << changeTo << " time "<<currentTime<<endl;
            vehiclesOnLane[i].erase(vehiclesOnLane[i].begin()+j);
            j--;
            //cout << "id:" << v.id << endl;
            
            
        }
    }
}