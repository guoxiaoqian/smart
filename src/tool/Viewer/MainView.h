#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>
#include <QPoint>
#include "Config.h"

class MainView : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint* points;
    int numOfPoints;
    Config* p_config;
    int regionMinX;
    int regionMinY;
    int regionMaxX;
    int regionMaxY;
public:
    explicit MainView(QObject *parent = 0);
    ~MainView();

    void paintEvent(QPaintEvent *event);

    void drawObjects(QPainter& painter);
    void drawGrids(QPainter& painter);

    void readObjects(QString &fileName);

    void readObjectsBinary(QString &fileName);

    inline int transCoorX(int x);
    inline int transCoorY(int y);
    inline void transCoorPoint(QPoint& point);
    
signals:
    
public slots:
    
};

#endif // MAINVIEW_H
