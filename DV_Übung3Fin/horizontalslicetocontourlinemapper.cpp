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

float HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices(float verticesOne, float verticesTwo, float threshold)
{
    float isoVertice;
    if(verticesOne > verticesTwo){
        isoVertice = verticesOne -((verticesOne - verticesTwo)/2);
    }
    else{
        isoVertice = verticesTwo -((verticesTwo - verticesOne)/2);
    }
    return isoVertice;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{
    float threshold = 0;
    QVector<QVector3D> list;
    QVector3D *data = list.data();

    for(int y = 0; y < 15;y++)
    {
        for(int x = 0; x < 15;x++)
        {
            float dataSource = m_dataSource->getDataValue(iz,y,x,0);
            float dataSource2 = m_dataSource->getDataValue(iz,y+1,x,0);
            float dataSource3 = m_dataSource->getDataValue(iz,y,x+1,0);
            float dataSource4 = m_dataSource->getDataValue(iz,y+1,x+1,0);
            if(dataSource){

            }
            list.append(isoCroosingBetweenTwoVertices(dataSource, dataSource2, threshold));


            //data[x][y] = isoCroosingBetweenTwoVertices();
        }
    }
    return list;
}


