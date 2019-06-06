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


QVector3D HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float iz, float vertice1x,float vertices1y, float vertices2x,float vertices2y, float threshold, int component)
{
    QVector3D iso;

    return iso ;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{

    float threshold = 0.1;
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
            else{
                if(((threshold - dataValue1) <= (dataValue2 -dataValue1)) ||((threshold - dataValue2) <= (dataValue1 -dataValue2))){
                    list.append(isoCroosingBetweenTwoVertices(iz, x , y , x + 1 , y, threshold, component));

                }
            }
        }
    }

    return list;

}

