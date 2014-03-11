#ifndef KEYGEN_H
#define KEYGEN_H

#include "base/kernel/singleton.hpp"

class KeyGen:public SSingleton<KeyGen>
{
public:
    KeyGen();
};

#endif // KEYGEN_H
