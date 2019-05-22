#include "datavolumeboundingboxrenderer.h"


DataVolumeBoundingBoxRenderer::DataVolumeBoundingBoxRenderer()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initializeOpenGLFunctions();

    initOpenGLShaders();

    initBoundingBoxGeometry();
}


DataVolumeBoundingBoxRenderer::~DataVolumeBoundingBoxRenderer()
{
    vertexBuffer.destroy();
}


void DataVolumeBoundingBoxRenderer::drawBoundingBox(QMatrix4x4 mvpMatrix)
{
    // Tell OpenGL to use the shader program of this class.
    shaderProgram.bind();

    // Bind and enable the vertex buffer.
    vertexBuffer.bind();
    shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, 3*sizeof(float));
    shaderProgram.enableAttributeArray("vertexPosition");

    // Set the model-view-projection matrix as a uniform value.
    shaderProgram.setUniformValue("mvpMatrix", mvpMatrix);

    // Issue OpenGL draw commands.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glDrawArrays(GL_LINE_STRIP, 0, 16);
}


void DataVolumeBoundingBoxRenderer::initOpenGLShaders()
{
    //Uni: /informatik2/students/home/6adibell/Desktop/visualizationandgpucomputing-uebung_02_template
    //Home: C:/Users/Kemal/Desktop/visual new
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "/informatik2/students/home/4bagdas/Schreibtisch/visual new/bbox_vshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "/informatik2/students/home/4bagdas/Schreibtisch/visual new/bbox_fshader.glsl");
    shaderProgram.link();
}


void DataVolumeBoundingBoxRenderer::initBoundingBoxGeometry()
{
    // Vertices of a unit cube that represents the bounding box.
    const unsigned int numVertices = 16;
    float unitCubeVertices[numVertices][3] = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 0}, {0, 0, 1}, {1, 0, 1}, {1, 0, 0},
        {1, 0, 1}, {1, 1, 1}, {1, 1, 0}, {1, 1, 1},
        {0, 1, 1}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1}};

    // Create vertex buffer and upload vertex data to buffer.
    vertexBuffer.create(); // make sure to destroy in destructor!
    vertexBuffer.bind();
    vertexBuffer.allocate(unitCubeVertices, numVertices * 3 * sizeof(float));
}
