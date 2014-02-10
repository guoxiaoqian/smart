#ifndef CONFIG_H
#define CONFIG_H

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
    static Config* p_config;
public:
    //region
    int region_xmin;
    int region_xmax;
    int region_ymin;
    int region_ymax;
    //data
    int num_object;
    int code_type;
    int distribution_type;
    //update
    int maxv;
    int num_round;
    int round_time;
    int num_speed;
    int num_hotspot;
    //query
    int query_type;
    int num_query;
    int query_width;
    int num_knn;
public:
    Config();
    void WriteSettings();
    void ReadSettings();
    static Config* getConfig();
};

#endif // CONFIG_H
