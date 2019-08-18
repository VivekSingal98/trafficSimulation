#ifndef vehicle_h
#define vehicle_h

#include <string>

class vehicle {
public:
    std::string type;
    float length;
    float width;
    float speed;
    float acceleration;
    int* color;
    float xPos;
    float yPos;
    float inTime;
    int laneNo;
    int laneId;
    int id;
    float angle;
    float gap;
    float laneChangeFrequency;
    float lastLaneChangedTime;
    bool midLane;
    vehicle(float len,float wid,float spee, int col1,int col2,int col3,float tim,float gap_behind);
    void updatePos();
};

#endif /* vehicle_h */
