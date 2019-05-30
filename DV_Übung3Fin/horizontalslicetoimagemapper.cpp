#include "horizontalslicetoimagemapper.h"

HorizontalSliceToImageMapper::HorizontalSliceToImageMapper()
{

}

HorizontalSliceToImageMapper::~HorizontalSliceToImageMapper()
{

}

void HorizontalSliceToImageMapper::setDataSource(FlowDataSource *dataSource)
{
    m_dataSource = dataSource;
}

QImage HorizontalSliceToImageMapper::mapSliceToImage(int iz)
{
    QImage outputImage(16,16,QImage::Format_RGB32);
    for(int y = 0; y < 16;y++)
    {
        for(int x = 0; x < 16;x++)
        {
            //Transformation in Rot oder Blau
            float dataValue = m_dataSource->getDataValue(iz,y,x,0); //Komponente 0 soll verwendet werden -> ic = 0
            if(dataValue > 0)
            {
                int redValue = static_cast<int>(3*dataValue*255);
                QColor color(redValue,0,0);
                outputImage.setPixelColor(x,y,color);
            }
            else if (dataValue < 0)
            {
                int blueValue = static_cast<int>(((dataValue*(-1)))*255*3);
                QColor color(0,0,blueValue);
                outputImage.setPixelColor(x,y,color);
            }
            else
            {
                QColor color(0,0,0);
                outputImage.setPixelColor(x,y,color);
            }

        }
    }
    return outputImage;
}
