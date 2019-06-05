#include "horizontalcontourlinesrenderer.h"
#include "horizontalslicetocontourlinemapper.h"
#include <QOpenGLTexture>
#include <iostream>


HorizontalContourLinesRenderer::HorizontalContourLinesRenderer()
: vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initializeOpenGLFunctions();

    initOpenGLShaders();

    initBoundingBoxGeometry();
}

HorizontalContourLinesRenderer::~HorizontalContourLinesRenderer()
{
    vertexBuffer.destroy();
}

void HorizontalContourLinesRenderer::setMapper(HorizontalSliceToContourLineMapper *mapper)
{
    m_mapper = mapper;
}

void HorizontalContourLinesRenderer::initOpenGLShaders()
{
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "hcslice_vshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "hcslice_fshader.glsl");
    shaderProgram.link();
}

void HorizontalContourLinesRenderer::initBoundingBoxGeometry()
{
    // Vertices of a unit cube that represents the bounding box.
    const unsigned int numVertices = 4;
    float unitCubeVertices[numVertices][3] = {
        {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}};

    // Create vertex buffer and upload vertex data to buffer.
    vertexBuffer.create(); // make sure to destroy in destructor!
    vertexBuffer.bind();
    vertexBuffer.allocate(unitCubeVertices, numVertices * 3 * sizeof(float));
}

void HorizontalContourLinesRenderer::drawContourLine(QMatrix4x4 matrix)
{

    // Tell OpenGL to use the shader program of this class.
    shaderProgram.bind();

    // Bind and enable the vertex buffer.
    vertexBuffer.bind();
    shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, 3*sizeof(float));
    shaderProgram.enableAttributeArray("vertexPosition");

    shaderProgram.setUniformValue("mvpMatrix", matrix);

    QVector<QVector3D> contour = m_mapper->mapSliceToContourLineSegments(0);
    vertexBuffer.allocate(contour.data(), contour.length()*sizeof (QVector3D));

    // Issue OpenGL draw commands.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3);
    glDrawArrays(GL_LINES, 0, contour.size());

}
