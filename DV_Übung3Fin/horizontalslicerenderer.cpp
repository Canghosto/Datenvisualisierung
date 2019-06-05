#include "horizontalslicerenderer.h"
#include <QOpenGLTexture>
#include <iostream>

HorizontalSliceRenderer::HorizontalSliceRenderer()
: vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initializeOpenGLFunctions();

    initOpenGLShaders();

    initBoundingBoxGeometry();
}

HorizontalSliceRenderer::~HorizontalSliceRenderer()
{
    vertexBuffer.destroy();
}

void HorizontalSliceRenderer::initOpenGLShaders()
{
    //Uni: /informatik2/students/home/6adibell/Desktop/visualizationandgpucomputing-uebung_02_template
    //Home: C:/Users/Kemal/Desktop/visual new
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "hslice_vshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "hslice_fshader.glsl");
    shaderProgram.link();
}

void HorizontalSliceRenderer::initBoundingBoxGeometry()
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

void HorizontalSliceRenderer::setMapper(HorizontalSliceToImageMapper *mapper)
{
    m_mapper = mapper;
}

void HorizontalSliceRenderer::changeGeometry()
{

    // Vertices of a unit cube that represents the bounding box.
    const unsigned int numVertices = 4;
    float unitCubeVertices[numVertices][3] = {
    {0, 0, height/15}, {1, 0, height/15}, {0, 1, height/15}, {1, 1, height/15}};

    // Create vertex buffer and upload vertex data to buffer.
    vertexBuffer.create(); // make sure to destroy in destructor!
    vertexBuffer.bind();
    vertexBuffer.allocate(unitCubeVertices, numVertices * 3 * sizeof(float));
}

void HorizontalSliceRenderer::drawImage(QMatrix4x4 matrix)
{

    // Tell OpenGL to use the shader program of this class.
    shaderProgram.bind();

    // Bind and enable the vertex buffer.
    vertexBuffer.bind();
    shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, 3*sizeof(float));
    shaderProgram.enableAttributeArray("vertexPosition");

    shaderProgram.setUniformValue("mvpMatrix", matrix);

    QImage img = m_mapper->mapSliceToImage(height);
    QOpenGLTexture texture(QOpenGLTexture::Target2D);
    texture.create();
    texture.setWrapMode(QOpenGLTexture::ClampToEdge);
    texture.setData(img);

    const int textureUnit = 0; // select a texture unit
    texture.bind(textureUnit);


    shaderProgram.setUniformValue("texture", textureUnit);
    // Issue OpenGL draw commands.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(9);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

void HorizontalSliceRenderer::moveSlice(int z)
{
    height += z;
    if(height > 15)
    {
        height = 15;
    }
    else if(height < 0)
    {
        height = 0;
    }
    // Vertices of a unit cube that represents the bounding box.
    changeGeometry();
}
