#include "ST2BTree.h"
#include "core/center/Config.h"

namespace smart{

ST2BTree::ST2BTree()
{
    valid = false;
    p_leftTree = NULL;
    p_rightTree = NULL;
}

ST2BTree::~ST2BTree()
{
}

void ST2BTree::init()
{
    valid = true;
    Config* p_config = Config::getObject();
    TimeType timeLen = p_config->maxUpdateTime;
    p_leftTree = new SubBtree();
    p_rightTree = new SubBtree();
    p_leftTree->init(0,timeLen);
    p_rightTree->init(timeLen,timeLen);
}

void ST2BTree::rotate()
{
    p_leftTree->updateTree();
    p_rightTree->updateTree();

}

ReturnType ST2BTree::update(KeyType key, UpdateRequest *p_update)
{
}

}
