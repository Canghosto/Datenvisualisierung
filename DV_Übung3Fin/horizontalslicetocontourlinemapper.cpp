#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>

HorizontalSliceToContourLineMapper::HorizontalSliceToContourLineMapper()
{

}

HorizontalSliceToContourLineMapper::~HorizontalSliceToContourLineMapper()
{

}

void HorizontalSliceToContourLineMapper::setDataSource(FlowDataSource *dataSource)
{
    m_dataSource = dataSource;
}

float HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float higher, float lower)
{

    return 0;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{
    float threshold = 0;
    QVector<QVector3D> list(100);
    data = list.data();
    for(int y = 0; y < 15;y++)
    {
        for(int x = 0; x < 15;x++)
        {
            float dataSource = m_dataSource->getDataValue(iz,y,x,0);
//            float dataSource1 = m_dataSource->getDataValue(iz,y,x,0);
//            float dataSource2 = m_dataSource->getDataValue(iz,y,x,0);
//            float dataSource3 = m_dataSource->getDataValue(iz,y,x,0);
//            if(dataSource < threshold < dataSource1){
//                ;
//            }
        }
    }
    return list;
}
