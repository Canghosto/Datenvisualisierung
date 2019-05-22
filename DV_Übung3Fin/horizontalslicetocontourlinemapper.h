#ifndef HORIZONTALSLICETOCONTOURLINEMAPPER_H
#define HORIZONTALSLICETOCONTOURLINEMAPPER_H

#include <QVector3D>
#include "flowdatasource.h"

class HorizontalSliceToContourLineMapper{
public:
    HorizontalSliceToContourLineMapper();
    ~HorizontalSliceToContourLineMapper();
    void setDataSource(FlowDataSource *dataSource);
    QVector mapSliceToCountourLineSegments(int iz);
};
#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
