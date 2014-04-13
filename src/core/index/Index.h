#ifndef INDEX_H
#define INDEX_H

namespace core {

class Index
{
public:
    Index();
    virtual ~Index(){}
    virtual void init() = 0;
};

}

#endif // INDEX_H
