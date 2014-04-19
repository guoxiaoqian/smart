#ifndef TYPE_H
#define TYPE_H

namespace smart{

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
    RETURN_SUCCESS = 1,
    RETURN_BADPARAM
};

enum SignalType
{
    SIGNAL_START,
    SIGNAL_STOP
};

}//namespace smart

#endif // TYPE_H
