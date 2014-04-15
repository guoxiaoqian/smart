#ifndef INDEX_H
#define INDEX_H

namespace smart {

class Index
{
public:
    Index();
    virtual ~Index(){}
    virtual void init() = 0;
};

}

#endif // INDEX_H
