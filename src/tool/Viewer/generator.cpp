#include "generator.h"
#include <QDir>
#include <QDebug>


Generator::Generator()
{
    p_config = Config::getConfig();
    //data
    region_xmin = p_config->region_xmin;
    region_xmax = p_config->region_xmax;
    region_ymin = p_config->region_ymin;
    region_ymax = p_config->region_ymax;
    num_object = p_config->num_object;
    code_type = p_config->code_type;
    distribution_type = p_config->distribution_type;
    num_hotspot = p_config->num_hotspot;
    update_query_ratio = p_config->update_query_ratio;
    //update
    round_time = p_config->round_time;
    num_round = p_config->num_round;
    maxv = p_config->maxv;
    num_speed = p_config->num_speed;
    //query
    query_type = p_config->query_type;
    query_width = p_config->query_width;
    num_knn = p_config->num_knn;
    num_query = p_config->num_query;

    speed = new int[num_speed];						//有num_speed种速度，将最大速度均匀分割
    for(int i=0;i<num_speed;i++)
        speed[i] = (float)maxv * (i+1) / num_speed;
}



FILE* Generator::open_file(char* filename)
{
    FILE * fp=NULL;
    if(code_type== CODE_ASCII)
        fp=fopen(filename,"w");
    else
        fp=fopen(filename,"wb");
    return fp;
}

void Generator::print(FILE * fp, UpdateType &update)
{
    if(code_type == CODE_BINARY)
        fwrite(&update,sizeof(UpdateType),1,fp);
    else
        fprintf(fp, "%d %d %d %d %d %d\n", update.oid,update.issueTime,update.posX,update.posY,update.velX, update.velY);
}

void Generator::print(FILE *fp, KNNQueryType &query)
{
    if(code_type == CODE_BINARY)
        fwrite(&query,sizeof(KNNQueryType),1,fp);
    else
        fprintf(fp,"%d %d %d %d %d %d\n",query.oid,query.issueTime,query.posX,query.posY,query.knnK,query.preTime);

}

void Generator::print(FILE *fp, RangeQueryType &query)
{
    if(code_type == CODE_BINARY)
        fwrite(&query,sizeof(RangeQueryType),1,fp);
    else
        fprintf(fp,"%d %d %d %d %d %d %d\n",query.oid,query.issueTime,query.minX,query.minY,query.maxX,query.maxY,query.preTime);
}

void Generator::Start()
{
    if(distribution_type == DISTRIBUTION_GAUSSIAN)
        gen_gaussian();
    else
        gen_uniform();
}

void Generator::gen_uniform()
{
    printf("Generation start...\n");
    FILE * fp=NULL;
    FILE * fp_query = NULL;
    char * filename = new char[100];
    char * dir = new char[100];
    sprintf(dir, "../../../data/uniform/%dK",num_object/1000);
    QDir q_dir;
    q_dir.mkpath(QString(dir));

    UpdateType * data = new UpdateType[num_object];
    sprintf(filename, "%s/init.dat", dir);
    fp = open_file(filename);
    for(int k=0;k<num_object;k++)
    {
        data[k].oid = k;
        data[k].issueTime = (float)k/num_object*round_time;
        data[k].posX= rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin;
        data[k].posY = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin;
        float v = speed[rand_number::rand_int() % num_speed];
        float theta = rand_number::rand_float();
        data[k].velX = v * cos(theta);
        data[k].velY = v * sin(theta);
        print(fp,data[k]);
    }
    fclose(fp);

    sprintf(filename,"%s/update.dat", dir);
    fp = open_file(filename);
    sprintf(filename,"%s/query.dat",dir);
    fp_query = open_file(filename);
    delete []filename;
    delete []dir;

    int u_count = 0;
    int q_count = 0;
    float tnow = 0;

  if(query_type == QUERY_RANGE)
  {

    RangeQueryType tmp_query;

    for(int k=0;k<num_round;k++)
    {
        for(int i=0;i<num_object;i++)
        {
            tnow = (float)i/num_object * round_time + k * round_time;
            data[i].posX = data[i].posX + data[i].velX * (tnow - data[i].issueTime);
            data[i].posY = data[i].posY + data[i].posY * (tnow - data[i].issueTime);
            if(data[i].posX>=region_xmax||data[i].posX<=region_xmin||data[i].posY>=region_ymax||data[i].posY<=region_ymin)
            {
                data[i].posX = rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin;
                data[i].posY = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin;
                float v = speed[rand_number::rand_int() % num_speed];
                float theta = rand_number::rand_float();
                data[i].velX = v * cos(theta);
                data[i].velY = v * sin(theta);
            }
            data[i].issueTime = tnow;
            print(fp,data[i]);
            u_count++;
            if(u_count%update_query_ratio == 0)
            {
                tmp_query.oid=q_count%num_object;
                tmp_query.issueTime=tnow;
                tmp_query.maxX = rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin+query_width/2;
                tmp_query.minX = tmp_query.maxX-query_width;
                tmp_query.maxY = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin+query_width/2;
                tmp_query.minY = tmp_query.maxY-query_width;
                tmp_query.preTime = 0;
                print(fp_query,tmp_query);
                q_count++;
            }
        }
    }
  }
  else
  {
        KNNQueryType tmp_query;

        for(int k=0;k<num_round;k++)
        {
            for(int i=0;i<num_object;i++)
            {
                tnow = (float)i/num_object * round_time + k * round_time;
                data[i].posX = data[i].posX + data[i].velX * (tnow - data[i].issueTime);
                data[i].posY = data[i].posY + data[i].posY * (tnow - data[i].issueTime);
                if(data[i].posX>=region_xmax||data[i].posX<=region_xmin||data[i].posY>=region_ymax||data[i].posY<=region_ymin)
                {
                    data[i].posX = rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin;
                    data[i].posY = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin;
                    float v = speed[rand_number::rand_int() % num_speed];
                    float theta = rand_number::rand_float();
                    data[i].velX = v * cos(theta);
                    data[i].velY = v * sin(theta);
                }
                data[i].issueTime = tnow;
                print(fp,data[i]);
                u_count++;
                if(u_count%update_query_ratio == 0)
                {
                    tmp_query.oid=q_count%num_object;
                    tmp_query.issueTime=tnow;
                    tmp_query.posX = rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin;
                    tmp_query.posY = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin;
                    tmp_query.knnK = num_knn;
                    tmp_query.preTime = 0;
                    print(fp_query,tmp_query);
                    q_count++;
                }
            }
        }

  }


    fclose(fp);
    fclose(fp_query);
    printf("Generation Done!\n");
}

struct Point
{
    int x;
    int y;
};

void Generator::gen_gaussian()
{
    printf("Generation start...\n");
    FILE * fp = NULL;
    FILE * fp_query = NULL;
    char * filename = new char[100];
    char * dir = new char[100];
    sprintf(dir, "../../../data/guassian/%d/%dK", num_hotspot, num_object/1000);
    QDir q_dir;
    q_dir.mkpath(QString(dir));

    Point * hotspot = new Point[num_hotspot];
    for(int i=0;i<num_hotspot; i++)
    {
        hotspot[i].x = rand_number::rand_pos_float() * (region_xmax-region_xmin)+region_xmin;
        hotspot[i].y = rand_number::rand_pos_float() * (region_ymax-region_ymin)+region_ymin;
    }

    UpdateType * data = new UpdateType[num_object];

    sprintf(filename, "%s/init.dat", dir);
    fp = open_file(filename);

    for(int k=0;k<num_object;k++)
    {
        data[k].oid = k;
        int spotno = rand_number::rand_int() % num_hotspot;

        do
        {
            data[k].posX = hotspot[spotno].x + rand_number::rand_gaussian() * (region_xmax-region_xmin) / num_hotspot;
            data[k].posY = hotspot[spotno].y + rand_number::rand_gaussian() * (region_ymax-region_ymin) / num_hotspot;
        }while(data[k].posX <region_xmin || data[k].posX>region_xmax || data[k].posY<region_ymin || data[k].posY>region_ymax);

        float v = speed[rand_number::rand_int() % num_speed];
        float theta = rand_number::rand_float();
        data[k].velX = v * cos(theta);
        data[k].velY = v * sin(theta);

        data[k].issueTime = (float)k/num_object * round_time;
        print(fp,data[k]);
    }
    fclose(fp);

    sprintf(filename,"%s/update.dat", dir);
    fp = open_file(filename);
    sprintf(filename, "%s/query.dat", dir);
    fp_query = open_file(filename);
    delete [] filename;
    delete [] dir;

    int u_count = 0;
    int q_count = 0;
    float tnow = 0;

    if(query_type == QUERY_RANGE)
    {

        RangeQueryType tmp_query;

        for(int k=0;k<num_round;k++)
        {
            for(int i=0;i<num_object;i++)
            {
                tnow = (float)i/num_object * round_time + k * round_time;
                int spotno = rand_number::rand_int() % num_hotspot;

                do
                {
                    data[i].posX = hotspot[spotno].x + rand_number::rand_gaussian() * (region_xmax-region_xmin) / num_hotspot;
                    data[i].posY = hotspot[spotno].y + rand_number::rand_gaussian() * (region_ymax-region_ymin) / num_hotspot;
                }while(data[i].posX<region_xmin || data[i].posX>region_xmax || data[i].posY<region_ymin || data[i].posY>region_ymax);

                float v = speed[rand_number::rand_int() % num_speed];
                float theta = rand_number::rand_float();
                data[k].velX = v * cos(theta);
                data[k].velY = v * sin(theta);
                data[i].issueTime = tnow;
                print(fp,data[i]);
                u_count++;
                //生成查询
                if(u_count%update_query_ratio == 0)
                {
                    tmp_query.oid=q_count%num_object;
                    int spotno = rand_number::rand_int() % num_hotspot;
                    tmp_query.maxX = hotspot[spotno].x + rand_number::rand_gaussian() * (region_xmax-region_xmin) / num_hotspot+query_width/2;
                    tmp_query.minX = tmp_query.maxX-query_width;
                    tmp_query.maxY = hotspot[spotno].y + rand_number::rand_gaussian() * (region_ymax-region_ymin) / num_hotspot+query_width/2;
                    tmp_query.minY = tmp_query.maxY-query_width;
                    tmp_query.issueTime=tnow;
                    tmp_query.preTime=0;
                    print(fp_query,tmp_query);
                    q_count++;
                }
            }
        }
    }
    else
    {
        KNNQueryType tmp_query;

        for(int k=0;k<num_round;k++)
        {
            for(int i=0;i<num_object;i++)
            {
                tnow = (float)i/num_object * round_time + k * round_time;
                int spotno = rand_number::rand_int() % num_hotspot;

                do
                {
                    data[i].posX = hotspot[spotno].x + rand_number::rand_gaussian() * (region_xmax-region_xmin) / num_hotspot;
                    data[i].posY = hotspot[spotno].y + rand_number::rand_gaussian() * (region_ymax-region_ymin) / num_hotspot;
                }while(data[i].posX<region_xmin || data[i].posX>region_xmax || data[i].posY<region_ymin || data[i].posY>region_ymax);

                float v = speed[rand_number::rand_int() % num_speed];
                float theta = rand_number::rand_float();
                data[k].velX = v * cos(theta);
                data[k].velY = v * sin(theta);
                data[i].issueTime = tnow;
                print(fp,data[i]);
                u_count++;
                //生成查询
                if(u_count%update_query_ratio == 0)
                {
                    tmp_query.oid=q_count%num_object;
                    int spotno = rand_number::rand_int() % num_hotspot;
                    tmp_query.posX = hotspot[spotno].x + rand_number::rand_gaussian() * (region_xmax-region_xmin) / num_hotspot;
                    tmp_query.posY = hotspot[spotno].y + rand_number::rand_gaussian() * (region_ymax-region_ymin) / num_hotspot;
                    tmp_query.knnK = num_knn;
                    tmp_query.issueTime=tnow;
                    tmp_query.preTime=0;
                    print(fp_query,tmp_query);
                    q_count++;
                }
            }
        }
    }

    fclose(fp);
    fclose(fp_query);
    printf("Generation Done!\n");
}

