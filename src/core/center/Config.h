#ifndef CONFIG_H
#define CONFIG_H

#include "base/setting/setting.h"

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

class Config:public SSetting
{
private:
    static Config* p_config;
public:
    int numOfObjects;
    int numOfUpdates;
    int maxUpdateTime;     //timestamp
    int maxSpeedOfObjects; //km/h
    int updateDistribution;
    int numOfHotSpots;

    int numOfQueries;
    int queryType;
    int rangeQuerySize;     //m
    int knnK;
    int queryPredictTime;
    int queryDistribution;

public:
    Config();
    Config(const char *fileName,SettingType type = SETTING_INI);
    ~Config();
    void init(const char *fileName,SettingType type = SETTING_INI);
    static Config* getConfig();
};

#endif // CONFIG_H
