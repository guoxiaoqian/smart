#ifndef BXTREE_H
#define BXTREE_H

class BxTree
{
private:
    static BxTree* p_bxtree;
public:
    BxTree();
    static BxTree* getBxTree();
};

#endif // BXTREE_H
