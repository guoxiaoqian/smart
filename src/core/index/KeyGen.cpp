#include "KeyGen.h"

KeyGen* KeyGen::p_keyGen = 0;

KeyGen::KeyGen()
{
    p_keyGen = this;
}

KeyGen *KeyGen::getKeyGen()
{
    return p_keyGen;
}
