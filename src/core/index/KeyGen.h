#ifndef KEYGEN_H
#define KEYGEN_H

class KeyGen
{
private:
    static KeyGen* p_keyGen;
public:
    KeyGen();
    static KeyGen* getKeyGen();
};

#endif // KEYGEN_H
