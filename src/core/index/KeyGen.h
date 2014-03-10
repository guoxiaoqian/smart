#ifndef KEYGEN_H
#define KEYGEN_H

#include "core/center/Singleton.h"

class KeyGen:public Singleton<KeyGen>
{
public:
    KeyGen();
};

#endif // KEYGEN_H
