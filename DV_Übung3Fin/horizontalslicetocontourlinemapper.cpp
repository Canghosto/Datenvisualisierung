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


QVector3D HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float iz, float vertices1x,float vertices1y, float vertices2x,float vertices2y, float threshold, int component)
{
    QVector3D iso;
    float dataValue1 = m_dataSource->getDataValue(iz,vertices1y,vertices1x,component);
    float dataValue2 = m_dataSource->getDataValue(iz,vertices2y,vertices2x,component);

    float lowerValue = fmin(dataValue1,dataValue2);
    float higherValue = fmax(dataValue1,dataValue2);

    float isoValue = (threshold - lowerValue)/(higherValue -lowerValue);

    if(vertices1x == vertices2x){
        iso = QVector3D(vertices1x/16,(vertices1y*(1-isoValue)+vertices2y*isoValue)/16,iz/16);
    }
    else if (vertices1y == vertices2y) {
        iso = QVector3D((vertices1x*(1-isoValue)+vertices2x*isoValue)/16,vertices2y/16,iz/16);
    };

    return iso;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{
    float threshold = 0.1;
    int component = 0;
    QVector<QVector3D> list;

    for(float y = 0; y < 15;y++)
    {
        for(float x = 0; x < 15;x++)
        {
            float dataValue1 = m_dataSource->getDataValue(iz,y,x,component);
            float dataValue2 = m_dataSource->getDataValue(iz,y,x+1,component);
            float dataValue3 = m_dataSource->getDataValue(iz,y+1,x,component);
            float dataValue4 = m_dataSource->getDataValue(iz,y+1,x+1,component);


            int marchingSquareCase = 0;

            if(dataValue1 > threshold){
                marchingSquareCase += 1;
            }
            if(dataValue2 > threshold){
                marchingSquareCase += 2;
            }
            if(dataValue4 >  threshold){
                marchingSquareCase += 4;
            }
            if(dataValue3 >  threshold){
                marchingSquareCase += 8;
            }

            switch (marchingSquareCase){
            case 0: case 15:
                break;
            case 1: case 14:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+1,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+1, threshold, component));
                break;
            case 2: case 13:
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y, x+1,y+1, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y, x,y, threshold, component));
                break;
            case 3: case 12:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+1 , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y, x+1,y+1 , threshold, component));
                break;
            case 4: case 11:
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y+1, x,y+1 , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y+1, x+1,y , threshold, component));
                break;
            case 5:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+1, x+1,y+1, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+1, x,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y, x+1,y+1, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y, x,y, threshold, component));
                break;
            case 6: case 9:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+1,y , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+1, x+1,y+1 , threshold, component));
                break;
            case 7: case 8:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+1, x+1,y+1 , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+1, x,y , threshold, component));
                break;
            case 10:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+1,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+1, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y+1, x+1,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+1, y+1, x,y+1, threshold, component));
                break;

            }




//            if((dataValue1 == dataValue2 == dataValue3 == dataValue4) ||
//                    (threshold < dataValue1 && threshold < dataValue2 && threshold < dataValue3 && threshold < dataValue4) ||
//                    (threshold > dataValue1 && threshold > dataValue2 && threshold > dataValue3 && threshold > dataValue4)){

//            }
//            else{
//                if(((threshold - dataValue1) <= (dataValue2 -dataValue1)) ||((threshold - dataValue2) <= (dataValue1 -dataValue2))){
//                    list.append(isoCroosingBetweenTwoVertices(iz, x , y , x + 1 , y, dataValue1, dataValue2, threshold, component));
//                }
//                if(((threshold - dataValue2) <= (dataValue4 -dataValue2)) ||((threshold - dataValue4) <= (dataValue2 -dataValue4))){
//                    list.append(isoCroosingBetweenTwoVertices(iz, x+1 , y , x + 1 , y+1, dataValue2, dataValue4, threshold, component));
//                }
//                if(((threshold - dataValue4) <= (dataValue3 -dataValue4)) ||((threshold - dataValue3) <= (dataValue4 -dataValue3))){
//                    list.append(isoCroosingBetweenTwoVertices(iz, x , y + 1 , x + 1 , y+1, dataValue4, dataValue3, threshold, component));
//                }
//                if(((threshold - dataValue3) <= (dataValue1 -dataValue3)) ||((threshold - dataValue1) <= (dataValue3 -dataValue1))){
//                    list.append(isoCroosingBetweenTwoVertices(iz, x , y , x, y+1, dataValue1, dataValue3, threshold, component));
//                }
//            }
        }
    }

    return list;

}

