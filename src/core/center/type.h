#ifndef TYPE_H
#define TYPE_H

namespace core{

typedef int CoorType;
typedef int SpeedType;
typedef int TimeType;
typedef int IDType;
typedef int PeriodType;
typedef int KeyType;
enum RequestType
{
    REQUEST_UPDATE,
    REQUEST_RANGE_QUERY,
    REQUEST_KNN_QUERY
};

enum ReturnType
{
    RETURN_FAIL = 0,
    RETURN_SUCCESS = 1
};

enum SignalType
{
    SIGNAL_START,
    SIGNAL_STOP
};

}//namespace core

#endif // TYPE_H
