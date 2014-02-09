#ifndef STRUCT_H
#define STRUCT_H

typedef int CoorType;
typedef int SpeedType;
typedef int TimeType;
typedef int IDType;

struct UpdateType
{
    IDType oid;
    TimeType issueTime;
    CoorType posX;
    CoorType posY;
    SpeedType velX;
    SpeedType velY;
};

struct RangeQueryType
{
    IDType oid;
    TimeType issueTime;
    CoorType minX;
    CoorType minY;
    CoorType maxX;
    CoorType maxY;
    TimeType preTime;
};

struct KNNQueryType
{
    IDType oid;
    TimeType issueTime;
    CoorType posX;
    CoorType posY;
    int knnK;
    TimeType preTime;
};

#endif

