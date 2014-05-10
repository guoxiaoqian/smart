#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/type.h"
#include "core/index/ST2BTree/ReferenceTable.h"
#include "base/kernel/singleton.hpp"
#include "core/request/UpdateRequest.h"

namespace smart{

class KeyGen:public SSingleton<KeyGen>
{
private:
    ReferenceTables* p_tables;
    TimeType periodLen;
public:
    KeyGen();
    void init();
    KeyType getKey(UpdateRequest *p_update);
};

}
#endif // KEYGEN_H
