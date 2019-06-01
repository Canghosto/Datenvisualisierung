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
    float isoCroosingBetweenTwoVertices(float higher, float lower);
    QVector<QVector3D> mapSliceToContourLineSegments(int iz);

private:
    QVector3D *data;
    FlowDataSource *m_dataSource;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
