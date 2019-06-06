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


QVector3D HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(int iz, int vertices1x,int vertices1y, int vertices2x,int vertices2y, float threshold, int component)
{
    float max = m_dataSource->getHighest();
    float transform = 100/max;

    QVector3D iso;
    float dataValue1 = m_dataSource->getDataValue(iz,vertices1y,vertices1x,component);
    float dataValue2 = m_dataSource->getDataValue(iz,vertices2y,vertices2x,component);

    dataValue1 = dataValue1 * transform;
    dataValue2 = dataValue2 * transform;
    if(dataValue1 < 0){
        dataValue1 = dataValue1 * (-1);
    }
    if(dataValue2 < 0){
        dataValue2 = dataValue2 * (-1);
    }

    float lowerValue = fmin(dataValue1,dataValue2);
    float higherValue = fmax(dataValue1,dataValue2);

    float fiz = iz;
    float fvertices1x = vertices1x;
    float fvertices2x = vertices2x;
    float fvertices1y = vertices1y;
    float fvertices2y = vertices2y;
    float isoValue = (threshold - lowerValue)/(higherValue -lowerValue);

    if((dataValue1 == lowerValue)){
    }
    else {
        fvertices1x = vertices2x;
        fvertices2x = vertices1x;
        fvertices1y = vertices2y;
        fvertices2y = vertices1y;
    }


    if(vertices1x == vertices2x){
        iso = QVector3D(fvertices1x/15,(fvertices1y*(1-isoValue)+fvertices2y*isoValue)/15,fiz/15);
    }
    else if (vertices1y == vertices2y) {
        iso = QVector3D((fvertices1x*(1-isoValue)+fvertices2x*isoValue)/15,fvertices1y/15,fiz/15);
    };

    return iso;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{
    //between [-100,100]
    float threshold = 20;
    float max = m_dataSource->getHighest();
    float transform = 100/max;
    int component = 0;
    float steps= 1;
    QVector<QVector3D> list;

    for(float y = 0; y < 15;y = y + steps)
    {
        for(float x = 0; x < 15;x= x + steps)
        {

            float dataValue1 = m_dataSource->getDataValue(iz,y,x,component);
            float dataValue2 = m_dataSource->getDataValue(iz,y,x+steps,component);
            float dataValue3 = m_dataSource->getDataValue(iz,y+steps,x,component);
            float dataValue4 = m_dataSource->getDataValue(iz,y+steps,x+steps,component);

            dataValue1 = dataValue1 * transform;
            dataValue2 = dataValue2 * transform;
            dataValue3 = dataValue3 * transform;
            dataValue4 = dataValue4 * transform;


            int marchingSquareCase = 0;

            if(dataValue1 > threshold || (dataValue1* -1) > threshold){
                marchingSquareCase += 1;
            }
            if(dataValue2 > threshold || (dataValue2* -1) > threshold){
                marchingSquareCase += 2;
            }
            if(dataValue4 > threshold || (dataValue4* -1) > threshold){
                marchingSquareCase += 4;
            }
            if(dataValue3 > threshold || (dataValue3* -1) > threshold){
                marchingSquareCase += 8;
            }


            switch (marchingSquareCase){
            case 0: case 15:
                break;
            case 1: case 14:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+steps,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+steps, threshold, component));
                break;
            case 2: case 13:
                list.append(isoCroosingBetweenTwoVertices(iz,x+steps, y, x+steps,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+steps,y, threshold, component));
                break;
            case 3: case 12:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+steps , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+steps, y, x+steps,y+steps , threshold, component));
                break;
            case 4: case 11:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+steps, x+steps,y+steps , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+steps, y, x+steps,y+ steps, threshold, component));
                break;
            case 5:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+steps, x+steps,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+steps, y, x+steps,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+steps,y, threshold, component));
                break;
            case 6: case 9:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+steps,y , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+steps, x+steps,y+steps , threshold, component));
                break;
            case 7: case 8:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+steps, x+steps,y+steps , threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+steps , threshold, component));
                break;
            case 10:
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x+steps,y, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y, x,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x+steps, y, x+steps,y+steps, threshold, component));
                list.append(isoCroosingBetweenTwoVertices(iz,x, y+steps, x+steps,y+steps, threshold, component));
                break;

            }
        }
    }
    return list;

}

