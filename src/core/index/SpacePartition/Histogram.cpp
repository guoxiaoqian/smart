#include "Histogram.h"
#include "core/index/SpacePartition/HistoCell.h"
#include "core/index/SpacePartition/ReferencePoint.h"
#include "core/index/SpacePartition/DenstyRegion.h"
#include "core/request/UpdateRequest.h"
#include "core/center/Config.h"

namespace smart{

int Histogram::colNum = 20;
int Histogram::rowNum = 20;
//用来判断cell与region是否密度相似
int Histogram::similarParam = 0;
//用来去噪
int Histogram::noiseParam = 0;

Histogram::Histogram()
{
    p_gram = NULL;
}

Histogram::~Histogram()
{
    delete p_gram;
}

void Histogram::init()
{
    Config* p_config = Config::getObject();
    Rect rect(p_config->minCoorX,p_config->minCoorY,p_config->maxCoorX,p_config->maxCoorY);
    p_gram = new Grid<HistoCell>(0,rect,rowNum,colNum);
    //取平均每个CELL中对象数量的十分之一作为相似参数
    similarParam = (int)((float)p_config->numOfObjects/(rowNum*colNum)/10);
    //取CELL数的百分之一作为噪点参数
    noiseParam = (rowNum*colNum)/100;
}

vector<ReferencePoint> Histogram::getReferencePoints(vector<ReferencePoint> &oldPoints)
{
    vector<ReferencePoint> result;

    //region growing
    vector<DenstyRegion> regions = getRegions(oldPoints);

    //计算每个region的中心和密度
    //创建参考点并添加到结果集
    vector<DenstyRegion>::iterator it;
    ReferencePoint rp;
    Point center;
    int i;
    for(i=0,it=regions.begin();it!=regions.end();++it,++i)
    {
        center = it->getCenter();
        rp.init(i,center);
        rp.setDensty(it->getDensty());
        result.push_back(rp);
    }

    //清理统计图表
    p_gram->clear();

    return result;
}

vector<DenstyRegion> Histogram::getRegions(vector<ReferencePoint> &oldPoints)
{
    vector<DenstyRegion> result;
    vector<ReferencePoint>::iterator it;
    int regionCount = 0;
    for(it= oldPoints.begin();it!=oldPoints.end();++it)
    {
        HistoCell* p_cell = p_gram->getCell(*it);
        if(!p_cell->isMarked())
        {
            DenstyRegion region(regionCount);
            region.addCell(p_cell);
            growRegion(p_cell,region);
            ++regionCount;
            result.push_back(region);
        }
    }
    //查找剩余未标记的Cell
    Grid<HistoCell>::RowIterator it_row;
    Grid<HistoCell>::ColIterator it_col;
    for(it_row = p_gram->getRowBegin();it_row!=p_gram->getRowEnd();++it_row)
    {
        for(it_col = it_row->begin();it_col!=it_row->end();++it_col)
        {
            if(!it_col->isMarked())
            {
                DenstyRegion region(regionCount);
                region.addCell(&(*it_col));
                growRegion(&(*it_col),region);
                ++regionCount;
                result.push_back(region);
            }
        }
    }

    //对结果集去噪
    discardNoises(result);

    return result;
}

void Histogram::growRegion(HistoCell *p_cell, DenstyRegion &region)
{
    vector<HistoCell*> cells = p_gram->getNeighborCells(p_cell->getID());
    HistoCell* p_tempCell;
    for(unsigned int i=0;i<cells.size();++i)
    {
        p_tempCell = cells.at(i);
        if(!p_tempCell->isMarked() && (region.isEmpty() || region.isSimilar(p_tempCell)))
        {
            region.addCell(p_tempCell);
            growRegion(p_tempCell,region);
        }
    }
}

void Histogram::discardNoises(vector<DenstyRegion> &regions)
{
    //根据噪点值找出噪点并删除或者合并
    for(vector<DenstyRegion>::iterator it = regions.begin();it!= regions.end();++it)
    {
        if(it->getCellNum() < noiseParam)
            it = regions.erase(it);
    }
}

void Histogram::update(UpdateRequest *p_update)
{
    Point point(p_update->posX,p_update->posY);
    HistoCell* p_cell = p_gram->getCell(point);
    p_cell->AddObject(point);
}

}
