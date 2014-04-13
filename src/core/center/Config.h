#ifndef CONFIG_H
#define CONFIG_H

#include "base/setting/setting.h"
#include "base/kernel/singleton.hpp"

namespace core {

enum DistributionType
{
    DISTRIBUTION_UNIFORM = 0,
    DISTRIBUTION_GAUSSIAN = 1
};
enum QueryType
{
    QUERY_RANGE = 0,
    QUERY_KNN = 1
};

enum CodeType
{
    CODE_ASCII = 0,
    CODE_BINARY = 1
};


class Config:public base::SSingleton<Config>,public base::SSetting
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

    //more
    int numOfUpdates;
    int numOfQueries;


public:
    Config();
    Config(const char *fileName,base::SettingType type = base::SETTING_INI);
    ~Config();
    void init(const char *fileName,base::SettingType type = base::SETTING_INI);
};

}

#endif // CONFIG_H
