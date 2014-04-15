#include "Config.h"

namespace smart{

Config::Config()
{
}

Config::Config(const char* fileName,SettingType type)
{
    init(fileName,type);
}

Config::~Config()
{
}

void Config::init(const char *fileName,SettingType type)
{
    SSetting::init(fileName,type);

    if(isEmpty())
    {        
        setValue("data","minCoorX","0");
        setValue("data","maxCoorX","100000");
        setValue("data","minCoorY","0");
        setValue("data","maxCoorY","100000");
        setValue("data","numOfObjects","1000000");
        setValue("data","codeType","0");
        setValue("data","distributionType","0");
        setValue("data","numOfHotspots","10");
        setValue("data","updateQueryRatio","100");


        setValue("update","maxUpdateTime","120");
        setValue("update","numOfUpdateRound","20");
        setValue("update","maxSpeedOfObjects","120");
        setValue("update","numOfSpeeds","5");

        setValue("query","queryType","0");
        setValue("query","rangeQuerySize","1000");
        setValue("query","knnK","100");
        setValue("query","queryPredictTime","0");

        setValue("thread","numOfUpdateThreads","1");
        setValue("thread","numOfQueryThreads","1");
        setValue("thread","numOfAssignThreads","1");
        setValue("thread","lenOfRequestBlock","100");
    }

    minCoorX = atoi(getValue("data","minCoorX").c_str());
    maxCoorX = atoi(getValue("data","maxCoorX").c_str());
    minCoorY = atoi(getValue("data","minCoorY").c_str());
    maxCoorY = atoi(getValue("data","maxCoorY").c_str());
    numOfObjects = atoi(getValue("data","numOfObjects").c_str());
    codeType = atoi(getValue("data","codeType").c_str());
    distributionType = atoi(getValue("data","distributionType").c_str());
    numOfHotspots = atoi(getValue("data","numOfHotspots").c_str());
    updateQueryRatio = atoi(getValue("data","updateQueryRatio").c_str());

    maxUpdateTime = atoi(getValue("update","maxUpdateTime").c_str());
    numOfUpdateRound = atoi(getValue("update","numOfUpdateRound").c_str());
    maxSpeedOfObjects = atoi(getValue("update","maxSpeedOfObjects").c_str());
    numOfSpeeds = atoi(getValue("update","numOfSpeeds").c_str());

    queryType = atoi(getValue("query","queryType").c_str());
    rangeQuerySize = atoi(getValue("query","rangeQuerySize").c_str());
    knnK = atoi(getValue("query","knnK").c_str());
    queryPredictTime = atoi(getValue("query","queryPredictTime").c_str());

    numOfUpdateThreads = atoi(getValue("thread","numOfUpdateThreads").c_str());
    numOfQueryThreads = atoi(getValue("thread","numOfQueryThreads").c_str());
    numOfAssignThreads = atoi(getValue("thread","numOfAssignThreads").c_str());
    lenOfRequestBlock = atoi(getValue("thread","lenOfRequestBlock").c_str());


    numOfUpdates = numOfObjects*numOfUpdateRound;
    numOfQueries = numOfUpdates/updateQueryRatio;

    print();
}

}
