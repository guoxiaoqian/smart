#ifndef CONFIG_H
#define CONFIG_H
#include <QString>

enum CodeType
{
    CODE_ASCII = 0,
    CODE_BINARY = 1
};

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

class Config
{
private:
    QString fileName;
    static Config* p_config;
public:
    //data
    int region_xmin;
    int region_xmax;
    int region_ymin;
    int region_ymax;
    int num_object;
    int code_type;
    int distribution_type;
    int num_hotspot;
    int update_query_ratio;

    //update
    int round_time;
    int num_round;
    int maxv;
    int num_speed;
    //query
    int query_type;
    int query_width;
    int num_knn;
    int query_pre_time;

    //more
    int num_update;
    int num_query;
public:
    Config();
    void WriteSettings();
    void ReadSettings();
    static Config* getConfig();
};

#endif // CONFIG_H
