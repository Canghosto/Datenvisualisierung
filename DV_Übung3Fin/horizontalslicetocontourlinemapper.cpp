#include "horizontalslicetocontourlinemapper.h"

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

void HorizontalSliceToContourLineMapper::isoCroosingBetweenTwoVertices()
{

}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(int iz)
{
//    QVector<QVector3D> list;
//    QVector3D *data = list.data();

//    for(int y = 0; y < 16;y++)
//    {
//        for(int x = 0; x < 16;x++)
//        {
//            //Transformation in Rot oder Blau
//            float threshold = m_dataSource->getDataValue(iz,y,x,0); //Komponente 0 soll verwendet werden -> ic = 0
//            if(threshold > 0)
//            {

//                QColor color(0,0,0);
//                //data[x] = color;

//            }

//        }
//    }
//    return list;
}


