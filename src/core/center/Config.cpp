#include "Config.h"

Config* Config::p_config = NULL;

Config::Config()
{
}

Config::Config(const char* fileName, SettingType type)
{
    init(fileName,type);
}

Config::~Config()
{
}

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

void Config::init(const char *fileName, SettingType type)
{
    SSetting::init(fileName,type);

    if(isEmpty())
    {
        setValue("update","numOfObjects","1000000");
        setValue("update","numOfUpdates","200000");
        setValue("update","maxUpdateTime","120");
        setValue("update","maxSpeedOfObjects","30");
        setValue("update","updateDistribution","0");
        setValue("update","numOfHotspots","10");

        setValue("query","numOfQueries","200");
        setValue("query","queryType","0");
        setValue("query","rangeQuerySize","1000");
        setValue("query","knnK","100");
        setValue("query","queryPredictTime","0");
        setValue("query","queryDistribution","0");
    }

    numOfObjects = atoi(getValue("update","numOfObjects").c_str());
    numOfUpdates = atoi(getValue("update","numOfUpdates").c_str());
    maxUpdateTime = atoi(getValue("update","maxUpdateTime").c_str());
    maxSpeedOfObjects = atoi(getValue("update","maxSpeedOfObjects").c_str());
    updateDistribution = atoi(getValue("update","updateDistribution").c_str());
    numOfHotSpots = atoi(getValue("update","numOfHotspots").c_str());

    numOfQueries = atoi(getValue("query","numOfQueries").c_str());
    queryType = atoi(getValue("query","queryType").c_str());
    rangeQuerySize = atoi(getValue("query","rangeQuerySize").c_str());
    knnK = atoi(getValue("query","knnK").c_str());
    queryPredictTime = atoi(getValue("query","queryPredictTime").c_str());
    queryDistribution = atoi(getValue("query","queryDistribution").c_str());

    p_config = this;
}

Config *Config::getConfig()
{
    return p_config;
}
