#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/type.h"
#include "core/index/ReferenceTable.h"
#include "base/kernel/singleton.hpp"

namespace core{

class KeyGen:public base::SSingleton<KeyGen>
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
