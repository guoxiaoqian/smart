#include "Config.h"
#include <QDebug>
#include <QSettings>
#include <QFile>

Config* Config::p_config = NULL;

Config::Config()
{
    // 当前目录的INI文件
    QString filename("config.ini");
    if (!QFile::exists(filename))
    {
        WriteSettings();
    }
    ReadSettings();
}


void Config::WriteSettings()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("region");
    settings.setValue("region_xmin",0);
    settings.setValue("region_xmax",100000);
    settings.setValue("region_ymin",0);
    settings.setValue("region_ymax",100000);
    settings.endGroup();
    settings.beginGroup("data");
    settings.setValue("num_object",1000000);
    settings.setValue("code_type",0);
    settings.setValue("distribution_type",0);
    settings.endGroup();
    settings.beginGroup("update");
    settings.setValue("maxv",120);
    settings.setValue("num_round",20);
    settings.setValue("round_time",120);
    settings.setValue("num_speed",5);
    settings.setValue("num_hotspot",10);

    settings.endGroup();
    settings.beginGroup("query");
    settings.setValue("query_type",0);
    settings.setValue("num_query",200000);
    settings.setValue("query_width",1000);
    settings.setValue("num_knn",100);
    settings.endGroup();
}

void Config::ReadSettings()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    //region
    region_xmin=settings.value("region/region_xmin").toInt();
    region_xmax=settings.value("region/region_xmax").toInt();
    region_ymin=settings.value("region/region_ymin").toInt();
    region_ymax=settings.value("region/region_ymax").toInt();
    //data
    num_object=settings.value("data/num_object").toInt();
    code_type=settings.value("data/code_type").toInt();
    distribution_type=settings.value("data/distribution_type").toInt();
    //update
    maxv=settings.value("update/maxv").toInt();
    num_round=settings.value("update/num_round").toInt();
    round_time=settings.value("update/round_time").toInt();
    num_speed=settings.value("update/num_speed").toInt();
    num_hotspot=settings.value("update/num_hotspot").toInt();
    //query
    query_type=settings.value("query/query_type").toInt();
    num_query=settings.value("query/num_query").toInt();
    query_width=settings.value("query/query_width").toInt();
    num_knn = settings.value("query/num_knn").toInt();
}

Config *Config::getConfig()
{
    if(p_config == NULL)
        p_config = new Config;
    return p_config;
}
