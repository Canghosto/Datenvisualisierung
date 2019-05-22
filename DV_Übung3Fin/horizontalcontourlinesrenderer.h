#include "horizontalslicetocontourlinemapper.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#ifndef HORIZONTALCONTOURLINESRENDERER_H
#define HORIZONTALCONTOURLINESRENDERER_H


class HorizontalContourLinesRenderer
{
public:
    HorizontalContourLinesRenderer();
    void setMapper(HorizontalSliceToContourLineMapper *mapper);
    void changeGeometry(float z);
    void drawImage(QMatrix4x4 matrix);
private:
    void initOpenGLShaders();
    void initBoundingBoxGeometry();

    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    HorizontalSliceToContourLineMapper *m_mapper;
};

#endif // HORIZONTALCONTOURLINESRENDERER_H
