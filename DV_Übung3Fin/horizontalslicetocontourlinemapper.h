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
    void mapSliceToContourLineSegments(int iz);

private:
    FlowDataSource *m_dataSource;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
