#ifndef REFERENCEPOINT_H
#define REFERENCEPOINT_H

#include "core/store/Grid.h"
namespace smart{
class ReferencePoint : public Point
{
public:
    IDType referencePointID;
    Grid * p_grid;
public:
    ReferencePoint();
    void init(IDType id,Point& point,Rect &rect);
    bool isValid();
    Grid* getGrid(){return p_grid;}
};
}
#endif // REFERENCEPOINT_H
