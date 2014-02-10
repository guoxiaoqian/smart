#include "MainView.h"
#include <QFile>
#include <QTextStream>

MainView::MainView(QObject *parent)
{
    points = NULL;
    numOfPoints = 0;
    p_config = Config::getConfig();
    regionMinX = p_config->region_xmin;
    regionMaxX = p_config->region_xmax;
    regionMinY = p_config->region_ymin;
    regionMaxY = p_config->region_ymax;

}

void MainView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this->viewport());
    painter.setPen(Qt::blue);
    drawObjects(painter);
    drawGrids(painter);
}

void MainView::drawObjects(QPainter &painter)
{
    if(points)
        painter.drawPoints(points,numOfPoints);
}

void MainView::drawGrids(QPainter &painter)
{
}

void MainView::readObjects(QString &fileName)
{
    if(p_config->code_type == CODE_BINARY)
        return readObjectsBinary(fileName);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    numOfPoints = p_config->num_object;
    points = new QPoint[numOfPoints];
    int oid;
    int issueTime;
    int posX;
    int posY;
    int velX;
    int velY;

    QTextStream in(&file);
    int i = 0;
    while (!in.atEnd())
    {
        in>>oid;
        in>>issueTime;
        in>>posX;
        in>>posY;
        in>>velX;
        in>>velY;

        points[i].setX(posX);
        points[i].setY(posY);
        ++i;
    }
}

void MainView::readObjectsBinary(QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    numOfPoints = p_config->num_object;
    points = new QPoint[numOfPoints];
    int oid;
    int issueTime;
    int posX;
    int posY;
    int velX;
    int velY;

    QDataStream in(&file);
    int i = 0;
    while (!in.atEnd())
    {
        in>>oid;
        in>>issueTime;
        in>>posX;
        in>>posY;
        in>>velX;
        in>>velY;

        points[i].setX(transCoorX(posX));
        points[i].setY(transCoorY(posY));
        ++i;
    }
}

int MainView::transCoorX(int x)
{
    return (float)(x-regionMinX)/(regionMaxX-regionMinX)*rect().width();
}

int MainView::transCoorY(int y)
{
    return (float)(regionMaxY-y)/(regionMaxY-regionMinY)*rect().height();
}

void MainView::transCoorPoint(QPoint &point)
{
    point.setX(transCoorX(point.x()));
    point.setY(transCoorY(point.y()));
}
