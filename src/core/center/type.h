#ifndef TYPE_H
#define TYPE_H

typedef int CoorType;
typedef int SpeedType;
typedef int TimeType;
typedef int IDType;
enum RequestType{REQUEST_UPDATE,REQUEST_RANGE_QUERY,REQUEST_KNN_QUERY};

//struct UpdateType
//{
//    IDType oid;
//    CoorType x;
//    CoorType y;
//    SpeedType vx;
//    SpeedType vy;
//    TimeType time;
//};

//struct RangeQueryType
//{
//    IDType	qid;
//    CoorType minX;
//    CoorType minY;
//    CoorType maxX;
//    CoorType maxY;
//    TimeType time;
//};

//struct KNNQueryType
//{
//    IDType qid;
//    CoorType x;
//    CoorType y;
//    TimeType time;
//};

#endif // TYPE_H
