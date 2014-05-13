#ifndef CONFIG_H
#define CONFIG_H

#include "base/setting/setting.h"
#include "base/kernel/singleton.hpp"

namespace smart {

enum DistributionType
{
    DISTRIBUTION_UNIFORM = 0,
    DISTRIBUTION_GAUSSIAN = 1
};
enum QueryType
{
    QUERY_RANGE = 0,
    QUERY_KNN   = 1
};

enum CodeType
{
    CODE_ASCII  = 0,
    CODE_BINARY = 1
};

enum IndexType
{
    INDEX_ST2BTREE = 0,
    INDEX_ST2GRID  = 1,
    INDEX_PGRID    = 2
};

class Config:public SSingleton<Config>,public SSetting
{
public:
    //data
    int minCoorX;
    int maxCoorX;
    int minCoorY;
    int maxCoorY;
    int numOfObjects;
    int codeType;
    int distributionType;
    int numOfHotspots;
    int updateQueryRatio;

    //update
    int maxUpdateTime;     //timestamp
    int numOfUpdateRound;
    int maxSpeedOfObjects; //km/h
    int numOfSpeeds;
    //query
    int queryType;
    int rangeQuerySize;     //m
    int knnK;
    int queryPredictTime;
    //thread
    int numOfUpdateThreads;
    int numOfQueryThreads;
    int numOfAssignThreads;
    int lenOfRequestBlock;

    //index
    int indexType;

    //more
    int numOfUpdates;
    int numOfQueries;


public:
    Config();
    Config(const char *fileName,SettingType type = SETTING_INI);
    ~Config();
    void init(const char *fileName,SettingType type = SETTING_INI);
};

}

#endif // CONFIG_H
