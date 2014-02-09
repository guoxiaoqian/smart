#include "generator.h"
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QDir>

Generator::Generator()
{
    // 当前目录的INI文件
    QString filename("config.ini");
    if (!QFile::exists(filename))
    {
        WriteSettings();
    }
    ReadSettings();

    speed = new int[num_speed];						//有num_speed种速度，将最大速度均匀分割
    for(int i=0;i<num_speed;i++)
        speed[i] = (float)maxv * (i+1) / num_speed;
}

void Generator::WriteSettings()
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

void Generator::ReadSettings()
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
    int uq_ratio = num_object*num_round / num_query;

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
            if(u_count%uq_ratio == 0)
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
                if(u_count%uq_ratio == 0)
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
    int uq_ratio = num_object*num_round / num_query;

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
                if(u_count%uq_ratio == 0)
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
                if(u_count%uq_ratio == 0)
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

