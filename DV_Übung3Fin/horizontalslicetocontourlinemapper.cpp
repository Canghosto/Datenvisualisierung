#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>
#include <iostream>
#include <math.h>
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


QVector3D HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float iz, float vertice1x,float vertices1y, float vertices2x,float vertices2y,float datavalue1, float datavalue2, float threshold , int component)
{
    QVector3D iso;
    float x = fmin(0,1);

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
                    list.append(isoCroosingBetweenTwoVertices(iz, x , y , x + 1 , y, dataValue1, dataValue2, threshold, component));
                }
                if(((threshold - dataValue2) <= (dataValue4 -dataValue2)) ||((threshold - dataValue4) <= (dataValue2 -dataValue4))){
                    list.append(isoCroosingBetweenTwoVertices(iz, x+1 , y , x + 1 , y+1, dataValue1, dataValue2, threshold, component));
                }
                if(((threshold - dataValue4) <= (dataValue3 -dataValue4)) ||((threshold - dataValue3) <= (dataValue4 -dataValue3))){
                   // list.append(isoCroosingBetweenTwoVertices(iz, x+1 , y , x + 1 , y+1, dataValue1, dataValue2, threshold, component));
                }
                if(((threshold - dataValue3) <= (dataValue1 -dataValue3)) ||((threshold - dataValue1) <= (dataValue3 -dataValue1))){
                    //list.append(isoCroosingBetweenTwoVertices(iz, x+1 , y , x + 1 , y+1, dataValue1, dataValue2, threshold, component));
                }
            }
        }
    }

    return list;

}

