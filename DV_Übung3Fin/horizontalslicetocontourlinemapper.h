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
    QVector3D  isoCroosingBetweenTwoVertices(float iz, float vertice1,float vertices2, float threshold);
    QVector<QVector3D> mapSliceToContourLineSegments(int iz);

private:
    FlowDataSource *m_dataSource;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
