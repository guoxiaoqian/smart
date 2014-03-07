#ifndef TYPE_H
#define TYPE_H

typedef int CoorType;
typedef int SpeedType;
typedef int TimeType;
typedef int IDType;
typedef int PeriodType;
enum RequestType
{
    REQUEST_UPDATE,
    REQUEST_RANGE_QUERY,
    REQUEST_KNN_QUERY
};

enum ReturnType
{
    RETURN_SUCCESS = 0,
    RETURN_ERROR = 1,
    RETURN_FAIL
};

enum SignalType
{
    SIGNAL_START,
    SIGNAL_STOP
};

#endif // TYPE_H
