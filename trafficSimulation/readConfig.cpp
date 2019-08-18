#include "readConfig.hpp"

using namespace std;

void readConfigFile_RoadParam(ifstream& fin,map<string, float>& mapRoadParam){
    string line;
    while(getline(fin,line)) {
        istringstream iss(line);
        if(line.size()<=1) {
            continue;
        }
        string word;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="END"){
            break;
        }
        string tmp;
        iss>>tmp; //= sign
        iss >> tmp;
        if(tmp!="") {
            mapRoadParam[word]=stof(tmp);
        }
    }
    mapRoadParam["Road_Width"]=mapRoadParam["Num_Lanes"]*mapRoadParam["Lane_Width"];
}

void readConfigFile_DefaultParam(ifstream& fin,map<string,float>& mapDefaultParam){
    string line;
    while(getline(fin,line)) {
        istringstream iss(line);
        if(line.size()<=1) {
            continue;
        }
        string word;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="END"){
            break;
        }
        string tmp;
        iss>>tmp; //= sign
        iss >> tmp;
        if(tmp!="") {
            mapDefaultParam[word]=stof(tmp);
        }
    }
}

void readConfigFile_VehicleParam(ifstream& fin, string carType,map<string, float>& mapVehicleParam) {
    string line;
    while(getline(fin,line)) {
        istringstream iss(line);
        if(line.size()<=1) {
            continue;
        }
        string word;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="END"){
            break;
        }
        string tmp;
        iss>>tmp; //= sign
        iss >> tmp;
        if(tmp!="") {
            string param=carType;
            param.append(word);
            mapVehicleParam[param]=stof(tmp);
            // if(word=="Width") {
            //   mapVehicleParam[param]=stof(tmp)+1;
            // }
        }
    }
}

void readConfigFile_Simulation(ifstream& fin,map<string, float>& mapVehicleParam,map<float,string>& signalFrame,vector<vehicle>& vehicleVector,map<string,float>& mapDefaultParam){
    string line;
    float incomingTime=0;
    float timeTmp=0;
    int vehicleId=0;
    while(getline(fin,line)) {
        istringstream iss(line);
        if(line.length()<=1) {
            continue;
        }
        string word;
        string tmp;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="END"){
            break;
        }
        if(word=="Signal") {
            iss >> tmp;
            string tmp2;
            iss >>tmp2;
            timeTmp=stof(tmp2)+incomingTime;
            signalFrame[timeTmp]=tmp;
        }
        else if(word=="Pass") {
            iss>>tmp;
            incomingTime=timeTmp + stof(tmp);
        }
        else {
          //  cout<<line<<endl;//<<" size "<<line.length()<<endl;
            int col1=0,col2=0,col3=0;
            iss>>tmp;
            if(tmp!="") {
                col1=stoi(tmp);
            }
            iss>>tmp;
            if(tmp!="") {
                col2=stoi(tmp);
            }
            iss>>tmp;
            if(tmp!="") {
                col3=stoi(tmp);
            }
            iss>>tmp;
            if(tmp!="") {
                timeTmp=stof(tmp)+incomingTime;
            }
            if(mapVehicleParam.find(word+"Gap")==mapVehicleParam.end()){
               mapVehicleParam[word+"Gap"] =mapDefaultParam["Default_Gap"];
            }

            if(mapVehicleParam.find(word+"LaneChangeFrequency")==mapVehicleParam.end()){
               mapVehicleParam[word+"LaneChangeFrequency"] =mapDefaultParam["Default_LaneChangeFrequency"];
            }

            vehicle v(mapVehicleParam[word+"Length"], mapVehicleParam[word+"Width"],
                      mapVehicleParam[word+"Speed"],col1,col2,col3,timeTmp,mapVehicleParam[word+"Gap"]);
            v.laneChangeFrequency=mapVehicleParam[word+"LaneChangeFrequency"];
            if(mapVehicleParam.find(word+"Acceleration")==mapVehicleParam.end()){
                v.acceleration = mapDefaultParam["Default_Acceleration"];
            }
            else{
                v.acceleration = mapVehicleParam[word+"Acceleration"];
            }
            v.type = word;
            v.id=vehicleId;
            vehicleId++;
            mapVehicleParam["max_id"]=vehicleId;
            vehicleVector.push_back(v);
           
        }
    }
}


void initTraffic(string file, map<string, float>& mapRoadParam,map<string,float>& mapDefaultParam,vector<vehicle>& vehicleVector,map<float,string>& signalFrame) {
    map<string, float> mapVehicleParam;

    mapRoadParam["Road_Length"]=30;
    mapRoadParam["Road_Signal"]=0;
    mapRoadParam["Road_Width"]=5;
    mapDefaultParam["Default_MaxSpeed"]=1;
    mapDefaultParam["Default_Acceleration"]=1;
    
    ifstream fin;
    fin.open(file);
    if(!fin.is_open()) {
        cout<<"file not opened";
    }
    string line;
    while (getline(fin,line) ) {
        istringstream iss(line);
        if(line.size()<=1) {
          continue;
        }
        string word;
        iss >>word;
        if(word[0]=='#') {
            continue;
        }
        if(word=="Road_Param") {
            readConfigFile_RoadParam(fin,mapRoadParam);
        }
        else if(word=="Default_Param") {
            readConfigFile_DefaultParam(fin, mapDefaultParam);
        }
        else if(word=="Vehicle_Type") {
            string tmp;
            iss>>tmp;
            iss>>tmp;
            readConfigFile_VehicleParam(fin,tmp,mapVehicleParam);
        }
        else if(word=="START") {
            readConfigFile_Simulation(fin,mapVehicleParam,signalFrame,vehicleVector,mapDefaultParam);
        }
    }
    
    fin.close();
}

void initMain(string file,float& timeBetweenEachFrame,float& imageLength,float& imageWidth,map<float,string>& signalFrame,float& gluOrtho2D_xSize,float& gluOrtho2D_ySize,int& lane) {
  map<string, float> mapRoadParam;
  map<string,float> mapDefaultParam;
  map<string, float> mapVehicleParam;
  vector<vehicle> vehicleVector;

  mapRoadParam["Road_Length"]=30;
  mapRoadParam["Road_Signal"]=0;
  mapRoadParam["Road_Width"]=5;
  mapRoadParam["Lane_Width"]=0;
  mapDefaultParam["Default_MaxSpeed"]=1;
  mapDefaultParam["Default_Acceleration"]=1;
  
  ifstream fin;
  fin.open(file);
  if(!fin.is_open()) {
      cout<<"file not opened";
  }
  string line;
  while (getline(fin,line) ) {
      istringstream iss(line);
      if(line.size()<=1) {
        continue;
      }
      string word;
      iss >>word;
      if(word[0]=='#') {
        continue;
      }
      if(word=="Road_Param") {
        readConfigFile_RoadParam(fin,mapRoadParam);
      }
      else if(word=="Default_Param") {
        readConfigFile_DefaultParam(fin, mapDefaultParam);
      }
      else if(word=="START") {
        readConfigFile_Simulation(fin,mapVehicleParam,signalFrame,vehicleVector,mapDefaultParam);
      }
  }
    
  fin.close();
  timeBetweenEachFrame=mapDefaultParam["stepTime"];
  imageLength=mapDefaultParam["imageLength"];
  float windowRatio=mapRoadParam["Road_Width"]/mapRoadParam["Road_Length"];
  imageWidth=imageLength*windowRatio; 
  gluOrtho2D_xSize=mapRoadParam["Road_Length"]/2.0;
  gluOrtho2D_ySize=mapRoadParam["Road_Width"]/2.0;
  lane=(int)mapRoadParam["Lane"];
}