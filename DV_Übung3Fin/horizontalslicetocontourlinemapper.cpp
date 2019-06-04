#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>
#include <iostream>

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


QVector3D HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float iz, float vertice1,float vertices2, float threshold)
{
//    QVector3D iso(0,0,0);

//    return iso ;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{

    float threshold = 0.3;
    int component = 0;
    QVector<QVector3D> list;

    for(float y = 0; y < 16;y++)
    {
        for(float x = 0; x < 16;x++)
        {
            float dataValue1 = m_dataSource->getDataValue(iz,y,x,component);
            float dataValue2 = m_dataSource->getDataValue(iz,y,x+1,component);
            float dataValue3 = m_dataSource->getDataValue(iz,y+1,x,component);
            float dataValue4 = m_dataSource->getDataValue(iz,y+1,x+1,component);
            if((dataValue1 == dataValue2 == dataValue3 == dataValue4) ||
                    (threshold < dataValue1 && threshold < dataValue2 && threshold < dataValue3 && threshold < dataValue4) ||
                    (threshold > dataValue1 && threshold > dataValue2 && threshold > dataValue3 && threshold > dataValue4)){

            }
            else if((dataValue1 > threshold > dataValue2) || (dataValue1 < threshold < dataValue2)){
//                list.append(isoCroosingBetweenTwoVertices(iz, y,x, threshold));
                   list.append(QVector3D(x,y,iz));
            }
        }
    }

    std::cout << list.first().x();
    return list;

}

