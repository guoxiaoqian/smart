#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/type.h"
#include "core/index/SpacePartion/ReferenceTable.h"
#include "base/kernel/singleton.hpp"

namespace smart{

class KeyGen:public SSingleton<KeyGen>
{
private:
    ReferenceTable* p_table;
    TimeType periodLen;
public:
    KeyGen();
    void init();
    KeyType getKey(CoorType coorX,CoorType coorY,TimeType tup);
};

}
#endif // KEYGEN_H
