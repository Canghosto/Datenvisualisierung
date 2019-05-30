#include "flowdatasource.h"
#include <QImage>
#include <QColor>

#ifndef HORIZONTALSLICETOIMAGEMAPPER_H
#define HORIZONTALSLICETOIMAGEMAPPER_H


class HorizontalSliceToImageMapper
{
public:
    HorizontalSliceToImageMapper();
    ~HorizontalSliceToImageMapper();
    void setDataSource(FlowDataSource *dataSource);
    QImage mapSliceToImage(int iz);

private:
    FlowDataSource *m_dataSource;
};
#endif // HORIZONTALSLICETOIMAGEMAPPER_H
