uniform mat4 mvpMatrix;
attribute vec4 vertexPosition;

void main()
{
    // Calculate vertex position in screen space.
    gl_Position = mvpMatrix * vertexPosition;
}
