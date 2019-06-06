#include "flowdatasource.h"
#include <QImage>
#include <QColor>

#ifndef HORIZONTALSLICETOCONTOURLINEMAPPER_H
#define HORIZONTALSLICETOCONTOURLINEMAPPER_H


class HorizontalSliceToContourLineMapper
{
public:
    HorizontalSliceToContourLineMapper();
    ~HorizontalSliceToContourLineMapper();
    void setDataSource(FlowDataSource *dataSource);
    QVector3D  isoCroosingBetweenTwoVertices(int iz, int vertices1x,int vertices1y, int vertices2x,int vertices2y ,float threshold, int component);
    QVector<QVector3D> mapSliceToContourLineSegments(int iz);

private:
    FlowDataSource *m_dataSource;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
