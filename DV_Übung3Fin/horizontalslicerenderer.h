#include "horizontalslicetoimagemapper.h"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#ifndef HORIZONTALSLICERENDERER_H
#define HORIZONTALSLICERENDERER_H
class HorizontalSliceRenderer : protected QOpenGLFunctions
{
public:
    HorizontalSliceRenderer();
    virtual ~HorizontalSliceRenderer();
    void setMapper(HorizontalSliceToImageMapper *mapper);
    void changeGeometry(float z);
    void drawImage(QMatrix4x4 matrix);
    void moveSlice(int z);
    float height = 0;
private:
    void initOpenGLShaders();
    void initBoundingBoxGeometry();

    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    HorizontalSliceToImageMapper *m_mapper;
};
#endif // HORIZONTALSLICERENDERER_H
