#include "Config.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

Config* Config::p_config = NULL;

Config::Config()
{
    //PATH:smart/src/config.ini
    fileName = QString("../../config.ini");
    if (!QFile::exists(fileName))
    {
        WriteSettings();
    }
    ReadSettings();
}


void Config::WriteSettings()
{
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup("data");
    settings.setValue("minCoorX",0);
    settings.setValue("maxCoorX",100000);
    settings.setValue("minCoorY",0);
    settings.setValue("maxCoorY",100000);
    settings.setValue("numOfObjects",1000000);
    settings.setValue("codeType",0);
    settings.setValue("distributionType",0);
    settings.setValue("numOfHotspots",10);
    settings.setValue("updateQueryRatio",100);
    settings.endGroup();

    settings.beginGroup("update");
    settings.setValue("maxUpdateTime",120);
    settings.setValue("numOfUpdateRound",20);
    settings.setValue("maxSpeedOfObjects",120);
    settings.setValue("numOfSpeeds",5);
    settings.endGroup();

    settings.beginGroup("query");
    settings.setValue("queryType",0);
    settings.setValue("rangeQuerySize",1000);
    settings.setValue("knnK",100);
    settings.setValue("queryPredictTime",0);
    settings.endGroup();

    settings.beginGroup("thread");
    settings.setValue("numOfUpdateThreads",1);
    settings.setValue("numOfQueryThreads",1);
    settings.setValue("numOfAssignThreads",1);
    settings.setValue("lenOfRequestBlock",100);
    settings.endGroup();
}

void Config::ReadSettings()
{
    QSettings settings(fileName, QSettings::IniFormat);
    //data
    region_xmin=settings.value("data/minCoorX").toInt();
    region_xmax=settings.value("data/maxCoorX").toInt();
    region_ymin=settings.value("data/minCoorY").toInt();
    region_ymax=settings.value("data/maxCoorY").toInt();
    num_object=settings.value("data/numOfObjects").toInt();
    code_type=settings.value("data/codeType").toInt();
    distribution_type=settings.value("data/distributionType").toInt();
    num_hotspot=settings.value("data/numOfHotspots").toInt();
    update_query_ratio = settings.value("data/updateQueryRatio").toInt();
    //update
    round_time=settings.value("update/maxUpdateTime").toInt();
    num_round=settings.value("update/numOfUpdateRound").toInt();
    maxv=settings.value("update/maxSpeedOfObjects").toInt();
    num_speed=settings.value("update/numOfSpeeds").toInt();
    //query
    query_type=settings.value("query/queryType").toInt();
    query_width=settings.value("query/rangeQuerySize").toInt();
    num_knn = settings.value("query/knnK").toInt();
    query_pre_time = settings.value("query/queryPredictTime").toInt();

    //more
    num_update = num_object*num_round;
    num_query = num_update*update_query_ratio;
}

Config *Config::getConfig()
{
    if(p_config == NULL)
        p_config = new Config;
    return p_config;
}
