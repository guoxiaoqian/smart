#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/type.h"
#include "core/index/SpacePartition/ReferenceTable.h"
#include "base/kernel/singleton.hpp"

namespace smart{

class KeyGen:public SSingleton<KeyGen>
{
private:
    ReferenceTables* p_tables;
    TimeType periodLen;
public:
    KeyGen();
    void init();
    KeyType getKey(Point point, TimeType tup);
};

}
#endif // KEYGEN_H
