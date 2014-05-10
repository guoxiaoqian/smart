#ifndef ST2BTREE_H
#define ST2BTREE_H

#include "core/index/ST2BTree/BPlus_tree.h"
#include "base/kernel/singleton.hpp"
#include "core/request/UpdateRequest.h"

namespace smart{

class TimeRange
{
public:
    TimeType minTime;
    TimeType maxTime;
    TimeType timeLen;

    void init(TimeType _minTime,TimeType _timeLen)
    {
        minTime = _minTime;
        timeLen = _timeLen;
        maxTime = minTime + timeLen;
    }
    bool coverTime(TimeType time)
    {
        return minTime <= time && maxTime > time;
    }
    void increase()
    {
        minTime = maxTime;
        maxTime = maxTime+timeLen;
    }
};

class SubBtree:public CBPlusTree
{
public:
    TimeRange timeRange;
    void init(TimeType _minTime,TimeType _timeLen)
    {
        timeRange.init(_minTime,_timeLen);
    }
    void updateTree()
    {
        //清空子树
        clear();
        //时间段更新
        timeRange.increase();
    }
    TimeType getRefTime()
    {
        return timeRange.maxTime;
    }
};

class ST2BTree:public SSingleton<ST2BTree>
{
private:
    bool valid;
    SubBtree* p_leftTree;
    SubBtree* p_rightTree;
//    SubBtree* p_oldTree;
//    SubBtree* p_newTree;
public:
    ST2BTree();
    ~ST2BTree();
    void init();
    void rotate();
    bool isValid(){return valid;}
    ReturnType update(KeyType key,UpdateRequest* p_update);
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
