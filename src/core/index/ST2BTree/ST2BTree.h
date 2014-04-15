#ifndef ST2BTREE_H
#define ST2BTREE_H

#include "base/kernel/singleton.hpp"
#include "core/index/ST2BTree/BPlus_tree.h"

namespace smart{

class ST2BTree:public SSingleton<ST2BTree>,public CBPlusTree
{
public:
    ST2BTree();
    ~ST2BTree();
    //继承的B+树接口
//  bool insert(KeyType key, const DataType& data);
//	bool remove(KeyType key);
//	bool update(KeyType oldKey, KeyType newKey);
//	// 定值查询，compareOperator可以是LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)
//	vector<DataType> select(KeyType compareKey, int compareOpeartor);
//	// 范围查询，BETWEEN
//	vector<DataType> select(KeyType smallKey, KeyType largeKey);
//	bool search(KeyType key); // 查找是否存在
//	void clear();             // 清空
//	void print()const;        // 打印树关键字
//	void printData()const;    // 打印数据

};

}

#endif // ST2BTREE_H
