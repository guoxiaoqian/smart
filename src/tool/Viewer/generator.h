#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "struct.h"
#include "rand.h"
#include "Config.h"

class Generator
{
private:
    Config* p_config;
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
    int num_query;
private:
    int * speed;
    int * tup;
public:
    Generator();

private:
    void WriteSettings();
    void ReadSettings();

    void gen_uniform();
    void gen_gaussian();
    FILE* open_file(char* filename);
    void print(FILE * fp, UpdateType &update);
    void print(FILE* fp, RangeQueryType &query);
    void print(FILE* fp, KNNQueryType &query);
public:
    void Start();
};

#endif // GENERATOR_H
