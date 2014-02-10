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
