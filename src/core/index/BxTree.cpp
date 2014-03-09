#include "BxTree.h"

BxTree* BxTree::p_bxtree = 0;

BxTree::BxTree()
{
    p_bxtree = this;
}

BxTree *BxTree::getBxTree()
{
    return p_bxtree;
}
