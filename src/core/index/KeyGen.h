#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/type.h"
#include "core/index/SpacePartition/ReferenceTable.h"
#include "base/kernel/singleton.hpp"

namespace smart{

class KeyGen:public SSingleton<KeyGen>
{
private:
    ReferenceTable* p_table;
    TimeType periodLen;
public:
    KeyGen();
    void init(ReferenceTable *_p_table);
    void setReferenceTable(ReferenceTable *_p_table);
    KeyType getKey(Point point, TimeType tup);
};

}
#endif // KEYGEN_H
